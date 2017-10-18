#include <stdint.h>

#include "efm32gg.h"  

/* sources */
#define SOURCESEL(x) 	(x << 16)

#define TIMER1 		29

/* signals */
#define SIGSEL(x) 		(x << 0)

#define TIMEROF 	1 

void setupPRS() {
	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_PRS; /* enable PRS */

	*PRS_CH0_CTRL |= SOURCESEL(TIMER1) | SIGSEL(TIMEROF); /* select source and signal */
}