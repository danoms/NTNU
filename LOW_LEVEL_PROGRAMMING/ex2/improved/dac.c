#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

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
	// *DAC0_CTRL |= 1 << 1; // enable sin mod

	// *DAC0_CH0CTRL |= 0 << 4; // sel PRS ch0
	// *DAC0_CH0CTRL |= 1 << 2; // PRS enable

		// *DAC0_CH0CTRL |= 1 << 0;  enable channel 
		// *DAC0_CH1CTRL |= 1 << 0; /* enable channel */

	*DAC0_CH0DATA = 0x000; /* set data to zero */
	*DAC0_CH1DATA = 0x000; /* set data to zero */
}
