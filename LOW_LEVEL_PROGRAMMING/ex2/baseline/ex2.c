#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h" 
  
#include "game_types.h"

#define   TIMER2_PERIOD   65535//90 //~48000     

#define BUTTON_PRESSED(x) 	(1 << x)
/*
 * Declaration of peripheral setup functions 
 */
void setupTimer(uint32_t period);
void setupDAC();
void setupGPIO();

/* game setup functions */
void setupMUSIC(sound_list* my_music);

/*
 * Your code will start executing here 
 */

sound_list* game_music;  /* pointer to available music */
sound* music;			 /* point to song to play */
int sample = 0;	/* sample to play */
uint16_t VOLUME = 10; /* on volume on DAC */

int main(void)
{
	sound_list my_music; 		// create space for music pointers
	game_music = &my_music;		// point to this space
	setupMUSIC(game_music); 	// make this space point to songs

	music = game_music->intro; /* upon restart play this */
	/*
	 * Call the peripheral setup functions 
	 */
	setupGPIO();
	setupDAC();
	setupTimer(TIMER2_PERIOD);

	while (1) {
		/* check buttons , start songs */
		if (~BUTTONS & BUTTON_PRESSED(0))
		{	 
			music = game_music->button[0];
			*TIMER2_CMD = 1;
			// LEDS = BUTTONS << 8;
		}

		if (~BUTTONS & BUTTON_PRESSED(1))
		{	
			music = game_music->button[1];
			*TIMER2_CMD = 1;
			// LEDS = BUTTONS << 8;
		}

		if (~BUTTONS & BUTTON_PRESSED(2))
		{	
			music = game_music->button[2];
			*TIMER2_CMD = 1;
			// LEDS = BUTTONS << 8;
		}

		if (~BUTTONS & BUTTON_PRESSED(3))
		{	
			music = game_music->button[3];
			*TIMER2_CMD = 1;
			// LEDS = BUTTONS << 8;
		}

		/* check TIMER1 and generate note */
		if (( *TIMER1_CNT > music->note_f[sample] ))
		{
			*DAC0_CH0DATA ^= VOLUME;
			*DAC0_CH1DATA ^= VOLUME;
		}

		/* check TIMER2 and change samples */
		if (*TIMER2_CNT > TIMER2_PERIOD )
		{
			static int counter = 0; 

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

	return 0;
}
