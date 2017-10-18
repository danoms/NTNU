#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

#include "game_types.h" /* struct for music handling */
#include "global_var.h"	/* to access varibales from main func */
#include "music_func.h"	/* */

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
	int VOLUME = 10; // volume of sound, so eardrums don't blow up

	*TIMER1_IFC = 1; /* clear main flag */

	*DAC0_CH0DATA ^= VOLUME;
	*DAC0_CH1DATA ^= VOLUME;
}

void __attribute__ ((interrupt)) TIMER2_IRQHandler() /* control TIMER1 period */
{
	if (*TIMER2_IF & 1) /* main clock overflow flag set */
	{
		*TIMER2_IFC = 1; // clear flags

		*TIMER1_TOP = music->note_f[sample]; // set frequency
		play();
		counter++;
		if (counter > music->duration[sample]) // check note duration
		{
			pause();
			if (counter > music->duration[sample] + music->pause_after[sample]) // check pause duration
			{
				play();
				counter = 0; 
				sample++;
				
			}  
			if (sample > music->size) // check if sample limit reached
			{
				finish();
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
	// LEDS = BUTTONS << 8; 

	if (*GPIO_IF & PIN(0)) // 0000 0001
	{
		init_sound();
		*GPIO_IFC = PIN(0); 				// clear flag
		music = game_music->button[0]; 	// choose music to play
	}
	if (*GPIO_IF & PIN(2)) // 0000 0100
	{
		init_sound();
		*GPIO_IFC = PIN(2);
		music = game_music->button[2]; 
	}
	if (*GPIO_IF & PIN(4)) // 
	{
		init_sound();
		*GPIO_IFC = PIN(4);
		music = game_music->button[4]; 
	}
	if (*GPIO_IF & PIN(6))
	{
		init_sound();
		*GPIO_IFC = PIN(6);
		music = game_music->button[6]; 
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
	// LEDS = BUTTONS << 8;
	if (*GPIO_IF & PIN(1)) // 0000 0010
	{
		init_sound();		/* start playing */
		*GPIO_IFC = PIN(1); /* if pin pressed */
		music = game_music->button[1]; /* play this song, change them in setupMUSIC.c */
	}
	if (*GPIO_IF & PIN(3)) // 0000 1000
	{
		init_sound();
		*GPIO_IFC = PIN(3); 
		music = game_music->button[3]; 
	}

	if (*GPIO_IF & PIN(5)) // 0010 0000
	{
		init_sound();
		*GPIO_IFC = PIN(5);
		music = game_music->button[5]; 
	}
	if (*GPIO_IF & PIN(7)) // 1000 0000
	{
		init_sound();
		*GPIO_IFC = PIN(7);
		music = game_music->button[7]; 
	}
	*GPIO_IFC = *GPIO_IF;
	
}
