#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

#include "game_types.h"
#include "global_var.h"

#define PIN(x) (1 << x)

/*
 * TIMER1 interrupt handler 
 */

void __attribute__ ((interrupt)) TIMER1_IRQHandler() /* control periodic data to DAC */
{
	/*
	 * TODO feed new samples to the DAC remember to clear the pending
	 * interrupt by writing 1 to TIMER1_IFC 
	 */

	volatile int VOLUME = 10; // volume of sound, so eardrums don't blow up

	static int state = 0;
		*TIMER1_IFC = 1; /* clear main flag */
		
		state ^= 1; // for period creation
		if (state)
		{
			*DAC0_CH0DATA = VOLUME;
			*DAC0_CH1DATA = VOLUME;
		} else{
			*DAC0_CH0DATA = 0x000;
			*DAC0_CH1DATA = 0x000;
		}

}

void __attribute__ ((interrupt)) TIMER2_IRQHandler() /* control TIMER1 period */
{
	static int counter = 0; 
	static int sample = 0;

	if (*TIMER2_IF & 1) /* main clock overflow flag set */
	{
		*TIMER2_IFC = 1; // clear flags
		*TIMER1_TOP = music->note_f[sample]; // set frequency

		*TIMER1_CMD = 1; // turn on timer/ generate tone

		counter++;
		if (counter > music->duration[sample]) // check note duration
		{
			
			*TIMER1_CMD = 2; //turn off for pause
			if (counter > music->duration[sample] + music->pause_after[sample]) // check pause duration
			{
				counter = 0; 
				sample++;
				*TIMER1_CMD = 1; 
			}  
			if (sample > music->size) // check if sample limit reached
			{
				LEDS ^= 0xFF00;
				*TIMER2_CMD = 2; 
				*TIMER1_CMD = 2;
				sample = 0;
			}
		}
	}
}

/*
 * GPIO even pin interrupt handler 
 */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
	/*
	 * TODO handle button pressed event, remember to clear pending
	 * interrupt 
	 */
	// *GPIO_IFC = 0x55;   //clear flags
	LEDS = BUTTONS << 8; 

	if (*GPIO_IF & PIN(0)) // 0000 0001
	{
		*GPIO_IFC = PIN(0); 				// clear flag
		music = game_music->button[0]; 	// choose music to play
		*TIMER2_CMD = 1; 				// turn on timer/generate sound
	}
	if (*GPIO_IF & PIN(2)) // 0000 0100
	{
		*GPIO_IFC = PIN(2);
		music = game_music->button[2]; 
		*TIMER2_CMD = 1;
	}
	if (*GPIO_IF & PIN(4)) // 
	{
		*GPIO_IFC = PIN(4);
		music = game_music->button[4]; 
		*TIMER2_CMD = 1;
	}
	if (*GPIO_IF & PIN(6))
	{
		*GPIO_IFC = PIN(6);
		music = game_music->button[6]; 
		*TIMER2_CMD = 1;
	}
	// *GPIO_IFC = 0x55; /* clear even pins */
	*GPIO_IFC = *GPIO_IF;
	
	
	
}

/*
 * GPIO odd pin interrupt handler 
 */



void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
	/*
	 * TODO handle button pressed event, remember to clear pending
	 * interrupt 
	 */
	LEDS = BUTTONS << 8;
	if (*GPIO_IF & PIN(1)) // 0000 0010
	{
		*GPIO_IFC = PIN(1);
		music = game_music->button[1]; 
		*TIMER2_CMD = 1;
	}
	if (*GPIO_IF & PIN(3)) // 0000 1000
	{
		*GPIO_IFC = PIN(3); 
		music = game_music->button[3]; 
		*TIMER2_CMD = 1;
	}

	if (*GPIO_IF & PIN(5)) // 0010 0000
	{
		*GPIO_IFC = PIN(5);
		music = game_music->button[5]; 
		*TIMER2_CMD = 1;
	}
	if (*GPIO_IF & PIN(7)) // 1000 0000
	{
		*GPIO_IFC = PIN(7);
		music = game_music->button[7]; 
		*TIMER2_CMD = 1;
	}
	*GPIO_IFC = *GPIO_IF;
	
}
