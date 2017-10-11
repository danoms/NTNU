#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"


#define PRSEN(x) 		(x << 2)
#define PRSSEL(x) 		(x << 4)
#define EN(x) 			(x << 0)
#define SINEMODE(x) 	(x << 1)
#define OUTENABLEPRS(x)	(x << 6)

void setupDAC() 
{ 
	/*
	 * TODO enable and set up the Digital-Analog Converter
	 * 
	 * 1. Enable the DAC clock by setting bit 17 in CMU_HFPERCLKEN0 
	 * 2. Prescale DAC clock by writing 0x50010 to DAC0_CTRL 
	 * 3. Enable left and right audio channels by writing 1 to DAC0_CH0CTRL and
	 * DAC0_CH1CTRL 
	 * 4. Write a continuous stream of samples to the DAC data registers, 
	 * DAC0_CH0DATA and DAC0_CH1DATA, for example from a timer interrupt 
	 */

	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_DAC0; /* enable clock */
	*DAC0_CTRL |= 0x50010; /* prescale clock to f/2^5 */

	*DAC0_CH0CTRL |= PRSEN(1) | PRSSEL(0) | EN(1); // PRS enable, PRS CH0, enable channel 0
	// *DAC0_CH1CTRL |= PRSEN(1) | PRSSEL(0) | EN(1);
	// *DAC0_CH0DATA = 0xFED; /* first write */
	
	// *DAC0_CH1CTRL |= EN(1); /* enable channel */

}
