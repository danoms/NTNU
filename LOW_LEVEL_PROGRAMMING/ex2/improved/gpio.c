#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/*
 * function to set up GPIO mode and interrupts
 */
void setupGPIO()
{
	/*
	 * TODO set input and output pins for the joystick 
	 */

	/*
	 * Example of HW access from C code: turn on joystick LEDs D4-D8 check 
	 * efm32gg.h for other useful register definitions 
	 */
	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO;	/* enable GPIO clock */
	
	*GPIO_PA_CTRL = 2;	/* set high drive strength */
	*GPIO_PA_MODEH = 0x55555555;	/* set pins A8-15 as output */
	*GPIO_PA_DOUT = 0xFF00;	/* turn on LEDs D4-D8 (LEDs are active
				 * low) */

	/* Turn on GPIO buttons */
	*GPIO_PC_MODEL = 0x33333333;	/*set pins C0-C7 as input */
	*GPIO_PC_DOUT = 0xFF;	/* enable pull-up */

	/* Enable interrupts */
	*GPIO_EXTIPSELL = 0x22222222;	/* Select port C */
	*GPIO_EXTIRISE = 0xFF;	/* on rising edge, pins 0-7 */
	*GPIO_EXTIFALL = 0xFF;	/* on falling edge, pins 0-7 */
	*GPIO_IEN = 0xFF;	/* enable interrupts for pins 0-7 */

}
