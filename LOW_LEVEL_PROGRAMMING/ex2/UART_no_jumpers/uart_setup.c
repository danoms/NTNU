#include "efm32gg.h"
#include "per_typedef.h"
#include "global_var.h"
#include "per_const.h"

#include "em_uart.h"
#include "em_gpio.h"
#include "gpio.h"
#include "uart.h"
#include "cmu.h"
#include "uart_setup.h"

void UART1_RS232(void) {

	UART_TypeDef *UART = UART1;

	uart_cfg_t *uart;
	uart_cfg_t uart1 = uartInitDef;
	uart = &uart1;

	// *CMU_HFPERCLKEN0 |= CMU_GPIO;	/* enable GPIO clock */
	enableCMU(CMU_GPIO, true);
	enableCMU(CMU_UART1, true);

	setupGPIO_conf(GPIO_PB, 10, INPUTPULLFILTER, 0);
	setupGPIO_conf(GPIO_PB, 9, PUSHPULL, 1);

	// *CMU_HFPERCLKEN0 |= CMU_UART1; /* enable clock for UART1 */


	UART->CMD = RXDIS(1) | TXDIS(1) | CLEARRX(1) | CLEARTX(1);

	UART->ROUTE |= RXPEN(1) | TXPEN(1) | LOCATION(2); 

	
	UART->CLKDIV |= calculate_clkdiv(uart); /* 90,25 */

	UART->IEN |= RXDATAV(1) | RXUF(1) | TXC(0) | TXBL(0);/* enable interrupts */

	UART->CMD |= RXEN(1) | TXEN(1) | MASTERDIS(0); /* enable receiving */
}

void BC_USART2_SPI(void) {
	UART_TypeDef *UART = USART2; /* use USART2 for SPI BC access */

	/*-------------------SpiBcInit------------------------------*/
	/* pins */
	enableCMU(CMU_GPIO, true);
	enableCMU(CMU_USART2, true);

	setupGPIO_conf(GPIO_PC, 2, PUSHPULL, 0); /* TX */
	setupGPIO_conf(GPIO_PC, 3, PUSHPULL, 0); /* RX */
	setupGPIO_conf(GPIO_PC, 4, PUSHPULL, 0); /* CLK */
	setupGPIO_conf(GPIO_PC, 5, PUSHPULL, 1); /* CS */

	/*-------------------Register config------------------------------*/

	/*usart settings  */
	uart_cfg_t *uart;
	uart_cfg_t uart1 = uartInitDef;
	uart = &uart1;

	uart->refFreq = 14000000;
	uart->baudrate = 200000;

	UART->CTRL |= SYNC(1) | CLOCKPOL(IDLELOW) | CLKPHA(SAMPLELEADING) | MSBF(0);

	UART->CLKDIV = sync_clkdiv(uart);//| (USART2->CLKDIV & ~0x1FFFC0UL);

	UART->ROUTE |= RXPEN(1) | TXPEN(1) | CLKPEN(1);
	UART->CMD |= MASTEREN(1) | RXEN(1) | TXEN(1);
}

void MICROSD_USART_SPI(void)
{
	UART_TypeDef *UART = USART0;
	/*-------------------microSD SPI------------------------------*/
	/* pins */
	enableCMU(CMU_GPIO, true);
	enableCMU(CMU_USART0, true);

	setupGPIO_conf(MICROSD_PORT, MICROSD_DI, PUSHPULL, 0); /* TX - MOSI - DI */
	setupGPIO_conf(MICROSD_PORT, MICROSD_DO, INPUTPULL, 1); /* RX - MISO - DO */
	setupGPIO_conf(MICROSD_PORT, MICROSD_CLK, PUSHPULL, 0); /* CLK */
	setupGPIO_conf(MICROSD_PORT, MICROSD_CS, PUSHPULL, 1); /* CS */

	/*-------------------Register config------------------------------*/
	/*usart settings  */
	uart_cfg_t *uart;
	uart_cfg_t uart1 = uartInitDef;
	uart = &uart1;

	uart->refFreq = 14000000;
	uart->baudrate = MICROSD_LOW_FREQ;

	UART->CTRL |= SYNC(1) | CLOCKPOL(IDLELOW) | CLKPHA(SAMPLELEADING) | MSBF(1) | AUTOTX(0) | AUTOCS(0) | LOOPBK(0);

	UART->CLKDIV = sync_clkdiv(uart)| (USART0->CLKDIV & ~0x1FFFC0UL);

	UART->ROUTE |= RXPEN(1) | TXPEN(1) | CLKPEN(1) | CSPEN(0) | LOCATION(1);
	UART->CMD |= MASTEREN(1) | RXEN(1) | TXEN(1);
}

void UART_init(UART_ALL_TypeDef *system, UART_TypeDef *device)
{
	*system = UART_INIT;
	system->addr = device;
}