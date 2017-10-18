#include <stdint.h>

#include "uart.h"
#include "uart_setup.h"

#include "efm32gg.h"
#include "global_var.h"
#include "per_typedef.h"

#include "em_gpio.h"
#include "em_uart.h"

uint8_t allOkMsg[] = "BC works!\n";
uint32_t allOkMsgLen = sizeof(allOkMsg) - 1;

uint8_t errorMsg[] = "Something went wrong! BC not working! But no msg then! ? ?\n";
uint32_t errorMsgLen = sizeof(errorMsg) - 1;

uint16_t bcMagicDefault = 0xEF32;

/* functions */
void setupUART( void ) { 
	UART_init(RS232, UART1);
	UART_init(MICROSD_SPI, USART0);

	UART1_RS232();
	BC_USART2_SPI();
	MICROSD_USART_SPI();

	check_BC_SPI();
}

void check_BC_SPI(void)
{
	uint16_t bcMagic; /* 0xEF32*/

	bcMagic = SpiRegisterRead(USART2,BC_MAGIC);
	if (bcMagic == bcMagicDefault)
	{
		putData(allOkMsg, allOkMsgLen, RS232);
	} else {
		putData(errorMsg, errorMsgLen, RS232);
	}
}

void putData(uint8_t *data, uint32_t length, UART_ALL_TypeDef *UART)
{
	uint32_t i = 0;
	/* fill data pointer [0:length-1] to txbuffer*/
	while (i < length)
	{
		UART->txBuf.data[UART->txBuf.wdI] = *(data + i);
		UART->txBuf.wdI = (UART->txBuf.wdI + 1) % BUFFERSIZE;
		i++;
	}

	UART->txBuf.bytesPending += length;
	UART->addr->IEN |= TXBL(1);
}

uint32_t getData(uint8_t *data, uint32_t dataLength, UART_ALL_TypeDef *UART)
{
	uint32_t i = 0;

	if (dataLength == 0)
	{
		dataLength = UART->rxBuf.bytesPending;
	}

	/* copy from rxBuf to temp buffer*/
	while(i < dataLength)
	{
		*(data + i) = UART->rxBuf.data[UART->rxBuf.rdI];
		UART->rxBuf.rdI = (UART->rxBuf.rdI + 1) % BUFFERSIZE;
		i++;
	}
	UART->rxBuf.bytesPending -= dataLength;
	return dataLength;
}

uint32_t calculate_clkdiv(uart_cfg_t *uart) {
	uint32_t clkdiv;

	clkdiv  = 32 * uart->refFreq + (uart->oversample * uart->baudrate) / 2;
    clkdiv /= (uart->oversample * uart->baudrate);
    clkdiv -= 32;
    clkdiv *= 8;
    clkdiv &= ~(0x60UL);

    return clkdiv;
}

uint32_t sync_clkdiv(uart_cfg_t *uart) {
	uint32_t clkdiv;
	clkdiv = (uart->refFreq - 1) / (2 * uart->baudrate);
	clkdiv = clkdiv  << 8;
	clkdiv &= 0x1FFFC0UL;
	// putData((char*)clkdiv, 4);
	return clkdiv;
}

static uint16_t SpiBcAccess(UART_TypeDef *UART, uint8_t addr, uint8_t rw, uint16_t data)
{
	uint16_t tmp; 

	/* Enable cs*/
	CLEAR(GPIO_PC->DOUT, 5);

	/* Write SPI address MSB */
	my_USART_Tx(UART, (addr & 0x3) | rw << 3);
	/* ignore data read back*/
	my_USART_Rx(UART);

	/* write SPI address LSB*/
	my_USART_Tx(UART,data & 0xFF);

	tmp = (uint16_t) my_USART_Rx(UART);

	/* SPI data MSB */
	my_USART_Tx(UART, data >> 8);
	tmp |= (uint16_t) my_USART_Rx(UART) << 8;

	/* Disable CS */
	SET(GPIO_PC->DOUT, 5);
	return tmp;
}

volatile uint16_t *lastAddr;

uint16_t SpiRegisterRead(UART_TypeDef *UART, volatile uint16_t *addr) 
{
	uint16_t data;

	if (addr != lastAddr)
	{
		SpiBcAccess(UART, 0x00, 0, 0xFFFF & ((uint32_t) addr)); /* LSBs of address */
		SpiBcAccess(UART, 0x01, 0, 0xFF & ((uint32_t) addr >> 16)); /* MSBs of address */
		SpiBcAccess(UART, 0x02, 0, (0x0C000000 & (uint32_t) addr) >> 26); /* chip select*/
	}
	/* read twice */
	data = SpiBcAccess(UART, 0x03, 1, 0);
	data = SpiBcAccess(UART, 0x03, 1, 0);

	lastAddr = addr;
	return data;
}

void SpiRegisterWrite(UART_TypeDef *UART, volatile uint16_t *addr, uint16_t data) 
{
	if (addr != lastAddr)
	{
		SpiBcAccess(UART, 0x00, 0, 0xFFFF & ((uint32_t) addr)); /* LSBs of address */
		SpiBcAccess(UART, 0x01, 0, 0xFF & ((uint32_t) addr >> 16)); /* MSBs of address */
		SpiBcAccess(UART, 0x02, 0, (0x0C000000 & (uint32_t) addr) >> 26); /* chip select*/
	}
	SpiBcAccess(UART, 0x03, 0, data); /* Data*/
	lastAddr = addr;
}

void my_USART_Tx(UART_TypeDef *UART, uint8_t data)
{
	/* check that transmit buffer is empty */
	while (!(UART->STATUS & STATUS_TXBL));
	UART->TXDATA = (uint32_t) data;
}

uint8_t my_USART_Rx(UART_TypeDef *UART) 
{
	while (!(UART->STATUS & STATUS_RXDATAV));
	// uint8_t temp = *USART2_RXDATA;
	return (uint8_t) UART->RXDATA;
	// putData(&temp,1);
	// return temp;
}