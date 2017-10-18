#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/*
 * function to setup EMU
 */

void setupEMU()
{
	/*
	 * TODO enable low energy mode for cpu
	 */
	// *SCR = SLEEPDEEP; /* go to EM2, don't go back to main */
	*EMU_MEMCTRL = 7; /* power down RAM blocks, change linker script for provided RAM  */
	*CMU_LFCLKSEL = 0; /* disable all LF clocks */
}
