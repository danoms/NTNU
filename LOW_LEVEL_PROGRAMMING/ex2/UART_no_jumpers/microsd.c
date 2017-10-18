#include "efm32gg.h"
#include "microsd.h"
#include "em_uart.h"
#include "uart.h"
#include "global_var.h"
#include "errors.h"
#include "uart_setup.h"
#include "spi_sd.h"

static uint32_t xfersPrMsec = MICROSD_LOW_FREQ / 8000;

uint8_t WaitReady(void)
{
	uint8_t res;
	uint32_t retryCount;

	/* wait for ready*/
	retryCount = 500 * xfersPrMsec;
	do 
	{
		res = MICROSD_XferSpi(0xff);
	} while ((res != 0xFF) && --retryCount);

	return res;
} 

uint8_t MICROSD_XferSpi(uint8_t data)
{
	// uint32_t timeout = xfersPrMsec * 10;
	// if (timeout)
	// {
	// 	timeout--;
	// }

	return spi_transfer(MICROSD_USART, data); 	/* USART0 */
}

uint8_t spi_transfer(UART_TypeDef *uart, uint8_t data)
{
	uint8_t temp;
	while(!(uart->STATUS & STATUS_TXBL)); /* TX buffer is empty */
	uart->TXDATA = (uint32_t)data;
	while(!(uart->STATUS & STATUS_TXC)); /* transfer completed */
	temp = (uint8_t)uart->RXDATA;
	// if (temp != 0xff)
	// {
	// 	putData(&temp,1 ,RS232);
	// }
	
	return temp;
}



int MICROSD_Select(void)
{
	OUT_LOW(MICROSD_PORT, MICROSD_CS);

	if (warmup(MICROSD_USART, 500) != 0xFF)
	{
		MICROSD_Deselect();
		return MICROSD_SELECT_ERROR;
	}
	return 0;
}

void MICROSD_Deselect(void)
{
	OUT_HIGH(MICROSD_PORT, MICROSD_CS);
	MICROSD_XferSpi(0xff);
}

uint8_t MICROSD_SendCmd(uint8_t cmd, uint32_t arg)
{
	uint8_t n, res;
	uint32_t retryCount;

	/* select card and wait for ready! */
	// MICROSD_Deselect();
	// if (MICROSD_Select() == MICROSD_SELECT_ERROR)
	// {
	// 	return MICROSD_SELECT_ERROR;
	// }
	// MICROSD_Select();
	// SET(GPIO_PE->DOUTCLR, 4);
	
	MICROSD_XferSpi(0xff);
	/* Send command packet */
	uint8_t package = 0x40 | cmd;
	MICROSD_XferSpi(package);			/* STart + Command index */
	package = (uint8_t)(arg >> 24);
	MICROSD_XferSpi(package);	/* Argument[31..24] */
	package = (uint8_t)(arg >> 16);
	MICROSD_XferSpi(package); 	/* Argument[26..16] */
	package = (uint8_t)(arg >> 8);
	MICROSD_XferSpi(package);	/* Argument[15..8] */
	package = (uint8_t)(arg);
	MICROSD_XferSpi(package); 		/* Argument [7..0] */
	n = 0x01; 								/* Dummy CRC + Stop */
	if (cmd == CMD0)
	{
		n = 0x95;
	}
	package = n;
	MICROSD_XferSpi(package);

	/* Receive response */
	retryCount = 10; 	/* wait for valid response in 10 attempts */
	do
	{
		res = MICROSD_XferSpi(0xff);
	} while ((res & 0x80) && --retryCount);

	// if (retryCount == 0)
	// {
	// 	return NO_RESPONSE_ERROR;
	// }
	return res; 	/* return response value */
}

uint8_t microsdOk[] = "MICROSD OK!!\n";
uint32_t microsdOklen = sizeof(microsdOk) - 1;

uint8_t microsdErr[] = "MICROSD ERROR!\n";
uint32_t microsdErrlen = sizeof(microsdErr) - 1;


/* Test microSD card */
uint8_t powerUp(void)
{

	 if (WaitReady() != 0xFF)
	  {
	  	return WAIT_ERROR;
	  } ;

	  uint8_t res;
	  uint32_t retryCount = 5;

	  do {
	  	res = MICROSD_SendCmd(CMD0, 0);
	  }	while((res == NO_RESPONSE_ERROR) && --retryCount);

	  

	  return res;
}






uint8_t single_write(UART_TypeDef *uart, uint8_t data)
{
	while(!(uart->STATUS & STATUS_TXBL));
	uart->TXDATA = (uint32_t)data;
	return 0;
}

uint8_t single_read(UART_TypeDef *uart)
{
	while(!(uart->STATUS & STATUS_TXC));
	return (uint8_t)uart->RXDATA;
}


uint8_t spi_transfer2(UART_TypeDef *uart, uint8_t data)
{
	single_write(uart, data);
	return single_read(uart);
}

uint8_t my_ready(UART_TypeDef *uart, uint32_t retry)
{

	uint8_t temps = 0xFF;
	power_sequence();
	OUT_LOW(MICROSD_PORT, MICROSD_CS);
	 // while(temps == 0xFF){
	
	 	temps =  MICROSD_SendCmd(CMD0,0);
	 	putData(&temps, 1, RS232);
	 // }
	 	
	 	return temps;



}

uint8_t warmup(UART_TypeDef *uart, uint32_t retry)
{
	uint8_t res;
	uint32_t retryCount = retry;

	// single_write(uart, 0xff);
	do {
		res = spi_transfer2(uart, 0xff);
	} while ((res != 0xff) && --retryCount);

	return res;
}