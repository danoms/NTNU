#include "efm32gg.h"
#include "global_var.h"
#include "music_func.h"

int counter = 0; 
int sample = 0;

/* make no sound */
void pause(void) {
	*TIMER1_CMD = 2; 	 /* turn off for pause */
	*DAC0_CH0CTRL &= ~1; /* disable channel */
	*DAC0_CH1CTRL &= ~1; /* disable channel */
}

/* generate note */
void play(void) {
	*TIMER1_CMD = 1;    /* turn on to play */
	*DAC0_CH0CTRL |= 1; /* enable channel */
	*DAC0_CH1CTRL |= 1; /* enable channel */
}

/* stop music generation */
void finish(void) {
	/* disable everything */
	*TIMER2_CMD = 2; 
	*TIMER1_CMD = 2;
	*SCR |= SLEEPONEXIT | SLEEPDEEP; /* go EM 2 */

	*DAC0_CH0CTRL &= ~1; /* disable channel */
	*DAC0_CH1CTRL &= ~1; /* disable channel */
}

/* start playing music */
void init_sound(void){
	*TIMER2_CMD = 2; 
	*TIMER2_CNT = 0;
	*TIMER1_CMD = 2;
	*TIMER1_CNT = 0;
	sample = 0;
	counter = 0;

	*TIMER2_CMD = 1;
	*SCR = 0; /* no sleeping */
}