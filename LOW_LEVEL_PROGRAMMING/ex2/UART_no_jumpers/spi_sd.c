#include "efm32gg.h"
#include "uart_setup.h"
#include "spi_sd.h"
#include "em_uart.h"
#include "microsd.h"

void wait_ms(uint32_t ms)
{
	volatile uint32_t timeout = ms * 14000;
	if (timeout)
	{
		timeout--;
	}
}

void wait_us(uint32_t us)
{
	volatile uint32_t timeout = 14*us;
	if (timeout)
	{
		timeout--;
	}
}

void go_manual(void)
{
	/* MANUAL pin control */
	MICROSD_USART-> ROUTE &= ~ (TXPEN(1) | CLKPEN(1) | CSPEN(1) | RXPEN(1)); /* clear pin override */
}

void go_normal(void)
{
	MICROSD_USART->ROUTE |= TXPEN(1) | CLKPEN(1) | RXPEN(1);
} 

void dummy_clock(int cycles)
{
	go_manual();

	OUT_HIGH(MICROSD_PORT, MICROSD_CS); /* CS high */
	OUT_HIGH(MICROSD_PORT, MICROSD_DI); /* DI high */

	manual_clock(cycles);

	go_normal();
}

void manual_clock(int cycles)
{
	/* clk 75 times, around 100kHz, period ~10us.*/
	for (int i = 0; i < cycles; ++i)
	{
		OUT_HIGH(MICROSD_PORT, MICROSD_CLK);
		wait_us(5);
		OUT_LOW(MICROSD_PORT, MICROSD_CLK);
		wait_us(5);
	}
}

uint8_t send_cmd(uint8_t cmd, uint32_t arg)
{
	OUT_LOW(MICROSD_PORT, MICROSD_CS);

	manual_send(0x40 | cmd);

	manual_send((uint8_t)arg);
	manual_send((uint8_t)arg);
	manual_send((uint8_t)arg);
	manual_send((uint8_t)arg);

	manual_send(0x95);	/* CRC check */

	uint8_t response;
	uint32_t retryCycles = 10;
	do {
		response = manual_read(); 	/* get response */
	} while ((response == 0xFF) && --retryCycles);
			

	OUT_HIGH(MICROSD_PORT, MICROSD_CS);		/* CS high */

	return response;
}

void manual_send(uint8_t data)
{
	uint8_t send_bit;
	for (int i = 7; i >= 0; --i)
	{
		send_bit = 0x01 & (data >> i); /* get bit */
		if (send_bit)
		{
			OUT_HIGH(MICROSD_PORT, MICROSD_DI);
		} else {
			OUT_LOW(MICROSD_PORT, MICROSD_DI);
		}
		manual_clock(1);
	}
}

uint8_t manual_read()
{
	uint8_t received_byte = 0;
	for (int i = 7; i >= 0; ++i)
	{
		received_byte |= ((MICROSD_PORT->DIN & MICROSD_DO) >> MICROSD_DO) << i;
		manual_clock(1);
	}
	return received_byte;
}


uint8_t test_bench()
{
	power_sequence();

	return send_cmd(CMD0,0);
}

void power_sequence(void)
{
	wait_ms(1);

	dummy_clock(74);
}