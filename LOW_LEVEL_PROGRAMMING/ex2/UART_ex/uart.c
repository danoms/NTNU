#include <stdint.h>

#include "efm32gg.h"
#include "global_var.h"
#include "per_typedef.h"

/* comand register */
#define RXPEN(x) 		(x << 0)
#define TXPEN(x) 		(x << 1)
#define LOCATION(x) 	(x << 8)
#define RXEN(x) 		(x << 0)
#define TXEN(x) 		(x << 2)
#define MASTERDIS(x) 	(x << 5)
#define TXDIS(x) 		(x << 3)
#define RXDIS(x) 		(x << 1)
#define CLEARRX(x) 		(x << 11)
#define CLEARTX(x) 		(x << 10)

/* interrupts */
#define RXDATAV(x) 		(x << 2)
#define TXC(x) 			(x << 0)
#define TXBL(x) 		(x << 1)
#define RXUF(x) 		(x << 5)

void UART1_setup(void);

void setupUART( void ) { 
	UART1_setup();
}

void UART1_setup(void) {
	uart_cfg_t *uart;
	uart_cfg_t uart1 = uartInitDef;
	uart = &uart1;

	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO;	/* enable GPIO clock */

	*GPIO_PB_MODEH = 0x00000340; /* pin10 INPUTPULLFILTER, pin9 pushpull */
	*GPIO_PB_DOUT = 0x0200; /* pin9 high*/

	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_UART1; /* enable clock for UART1 */

	*UART1_CMD = RXDIS(1) | TXDIS(1) | CLEARRX(1) | CLEARTX(1);

	*UART1_ROUTE |= RXPEN(1) | TXPEN(1) | LOCATION(2); 

	uint32_t clkdiv;

	clkdiv  = 32 * uart->refFreq + (uart->oversample * uart->baudrate) / 2;
    clkdiv /= (uart->oversample * uart->baudrate);
    clkdiv -= 32;
    clkdiv *= 8;

	
	clkdiv &= ~(0x60UL);
	*UART1_CLKDIV |= clkdiv; /* 90,25 */

	*UART1_IEN |= RXDATAV(1) | RXUF(1) | TXC(1) | TXBL(1);/* enable interrupts */

	*UART1_CMD |= RXEN(1) | TXEN(0) | MASTERDIS(0); /* enable receiving */
}