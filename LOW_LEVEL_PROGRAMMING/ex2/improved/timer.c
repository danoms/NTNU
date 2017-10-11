#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

#define UP 0

#define MODE (UP << 0)
/*
 * function to setup the timer 
 */
void setupTimer(uint16_t period)
{
	/*
	 * TODO enable and set up the timer
	 * 
	 * 1. Enable clock to timer by setting bit 6 in CMU_HFPERCLKEN0 
	 * 2. Write the period to register TIMER1_TOP 
	 * 3. Enable timer interrupt generation by writing 1 to TIMER1_IEN 
	 * 4. Start the timer by writing 1 to TIMER1_CMD
	 * 
	 * This will cause a timer interrupt to be generated every (period)
	 * cycles. Remember to configure the NVIC as well, otherwise the
	 * interrupt handler will not be invoked. 
	 */

	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_TIMER1;

	// *TIMER1_CTRL = MODE;
	*TIMER1_TOP = period; /* sets top limit */
	*TIMER1_IEN = 1; /* enables interrupts for overflow */

	// TIMER1 setup for sine wave
	// *CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_PRS; // enable clock for PRS
	// *PRS_CH0_CTRL |= 29 << 16; // set TIMER1 as source, 011101 in 21:16
	// *PRS_CH0_CTRL |= 1; // set overflow as signal 




	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_TIMER2;

	*TIMER2_TOP = 65535;
	*TIMER2_IEN = 1;


	*TIMER2_CMD = 1; /* starts counter */
	*TIMER1_CMD = 1; /* starts counter */


}
