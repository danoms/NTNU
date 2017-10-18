#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "global_var.h"
#include "dma.h"
// #include "sample_note_A.h" 
  
#include "game_types.h"

#define PIN(x) 			(1 << x)
#define N_minus_1(x) 	(x << 4)

#define TXEN(x) 		(x << 2)
#define TXC(x) 			(x << 0)
#define TXBL(x) 		(x << 1)

/*
 * TIMER1 interrupt handler 
 */

int counter = 5;
int i = 0;
uint8_t buffer[6];
int size = 5;

void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
	*GPIO_IFC = *GPIO_IF;
	counter = 5;
	// *UART1_IEN |= TXC(1) | TXBL(1);
	// LEDS = BUTTONS << 8;
	// LEDS = 0xF000;
}

void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
	*GPIO_IFC = *GPIO_IF;
	// LEDS = BUTTONS << 8;
	// LEDS = BUTTONS << 8;
	// LEDS = 0xF000;
}

void __attribute__ ((interrupt)) UART1_RX_IRQHandler() {
	*GPIO_IFC = 0x20;
	// *GPIO_PA_DOUT = 0x4400;
	size--;
	buffer[size] = *UART1_RXDATA;

	if (size == 0)
	{
		size = 5;
		// *UART1_IEN |= TXC(1) | TXBL(1);
	}
	LEDS = *UART1_RXDATA << 8;

	// counter = *UART1_RXDATA;
	// *GPIO_PA_DOUT =  *UART1_RXDATA;
}

void __attribute__ ((interrupt)) UART1_TX_IRQHandler() {
	*UART1_IFC = 3;
	// *GPIO_PA_DOUT = 0x510;
	// *UART1_TXDATA = 0x45;
	buffer[5] = 10;
	// uint8_t data = 10;
	i++;
	LEDS = 0xF300;
	if (i > size )
	{
		*UART1_IEN &= ~( TXC(1) | TXBL(1) );
		i = 0;
	}
	counter--;
	*UART1_TXDATA = buffer[i];
}