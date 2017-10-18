#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "global_var.h"
// #include "sample_note_A.h" 
  

#define PIN(x) 			(1 << x)
#define N_minus_1(x) 	(x << 4)

#define TXEN(x) 		(x << 2)
#define TXC(x) 			(x << 0)
#define TXBL(x) 		(x << 1)

/* status*/
#define RXDATAV_MASK 	(1 << 7)
#define TXBL_MASK 		(1 << 6)
/*
 * TIMER1 interrupt handler 
 */

int counter = 5;
int i = 0;
uint8_t buffer[6];
int size = 5;

void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
	GPIO->IFC = GPIO->IF;
	counter = 5;
	// *UART1_IEN |= TXC(1) | TXBL(1);
	// LEDS = BUTTONS << 8;
	// LEDS = 0xF000;
}

void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
	GPIO->IFC = GPIO->IF;
	// LEDS = BUTTONS << 8;
	// LEDS = BUTTONS << 8;
	// LEDS = 0xF000;
}

void __attribute__ ((interrupt)) UART1_RX_IRQHandler() {
	if (RS232->addr->STATUS & RXDATAV_MASK)
	{
		RS232->rxBuf.data[RS232->rxBuf.wdI] = RS232->addr->RXDATA;
		RS232->rxBuf.wdI = (RS232->rxBuf.wdI + 1) % BUFFERSIZE;
		RS232->rxBuf.bytesPending++;
	}
}

void __attribute__ ((interrupt)) UART1_TX_IRQHandler() {
	/* if buffer is free */
	if (RS232->addr->STATUS & TXBL_MASK)
	{
		if (RS232->txBuf.bytesPending > 0)
		{
			RS232->addr->TXDATA = RS232->txBuf.data[RS232->txBuf.rdI];
			RS232->txBuf.rdI = (RS232->txBuf.rdI + 1) % BUFFERSIZE;
			RS232->txBuf.bytesPending--;
		}
	}

	if (RS232->txBuf.bytesPending == 0)
	{
		RS232->addr->IEN &= ~TXBL(1);
	}
}