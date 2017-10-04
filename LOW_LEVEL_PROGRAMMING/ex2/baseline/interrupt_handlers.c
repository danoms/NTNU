#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/*
 * TIMER1 interrupt handler 
 */

volatile int VOLUME = 10;
volatile int STEP = 32;
int MAX_VOL = 0xFFF;

int start_sound = 0;

#define DO 	53449
#define RE 	47674
#define MI 	42472
#define FA 	40088
#define SOL 35714
#define LA  31818
#define SI 	28347

#define LOWEST 65535
#define HIGHEST 5000

int sound_arr[] = {DO,RE,MI,FA,SOL,LA,SI};
int sample = 0;
int SAMPLE_LIMIT = 4;
int *music;

// int music1[] = {DO,DO,MI,SOL,SOL,SI,SI,SOL,MI, DO, DO};
// int music2[] = {LOWEST, MI,LA, FA, LOWEST, LOWEST, LOWEST, LOWEST, SI, SI ,DO,RE,RE};
// int music3[] = {LOWEST, LOWEST, HIGHEST ,LOWEST};
// int music4[] = {LOWEST,HIGHEST, HIGHEST,LOWEST};

struct Albums {
	int music1[12];
	int music2[13];
	int music3[12];
	int music4[12];
} album;

struct Albums first_album = {
	{DO,DO,MI,SOL,SOL,SI,SI,SOL,MI, DO, DO},
	{LOWEST, MI,LA, FA, LOWEST, LOWEST, LOWEST, LOWEST, SI, SI ,DO,RE,RE},
	{LOWEST, LOWEST, HIGHEST ,LOWEST},
	{LOWEST,HIGHEST, HIGHEST,LOWEST}
};

int my_music[][13] = {
	{DO,DO,MI,SOL,SOL,SI,SI,SOL,MI, DO, DO},
	{LOWEST, MI,LA, FA, LOWEST, LOWEST, LOWEST, LOWEST, SI, SI ,DO,RE,RE},
	{LOWEST, LOWEST, HIGHEST ,LOWEST},
	{LOWEST,HIGHEST, HIGHEST,LOWEST}
};

void __attribute__ ((interrupt)) TIMER1_IRQHandler() /* control periodic data to DAC */
{
	/*
	 * TODO feed new samples to the DAC remember to clear the pending
	 * interrupt by writing 1 to TIMER1_IFC 
	 */

	static int state = 0;
	
	if (*TIMER1_IF & 1) /* main flag set */
	{
		*TIMER1_IFC = 1; /* clear main flag */
		
		state ^= 1;
		if (state)
		{
			*DAC0_CH0DATA ^= VOLUME;
			*DAC0_CH1DATA ^= VOLUME;
		} else{
			*DAC0_CH0DATA ^= 0x000;
			*DAC0_CH1DATA ^= 0x000;
		}
	}
	// *TIMER1_IFC = 1; /* clear main flag */
		
	// 	state ^= 1;
	// 	if (state)
	// 	{
	// 		*DAC0_CH0DATA ^= VOLUME;
	// 		*DAC0_CH1DATA ^= VOLUME;
	// 	} else{
	// 		*DAC0_CH0DATA ^= 0x000;
	// 		*DAC0_CH1DATA ^= 0x000;
	// 	}
}

void __attribute__ ((interrupt)) TIMER2_IRQHandler() /* control TIMER1 period */
{

	if (*TIMER2_IF & 1) /* main clock overflow flag set */
	{
		*TIMER2_IFC = 1;
		*TIMER1_TOP = music[sample];

		*TIMER1_CMD = 1;

		static int counter = 0;

		counter++;
		if (counter > 214/8)
		{
			LEDS ^= 0xFF00;

			counter = 0;
			sample++;

			if (sample > SAMPLE_LIMIT)
			{
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
	// *GPIO_IFC = *GPIO_IF; /* clear flags*/

	if (*GPIO_IF & 1)
	{
		*GPIO_IFC = 0x55;
		music = first_album.music3;
		SAMPLE_LIMIT = 3;
		*TIMER2_CMD = 1;
	}

	if (*GPIO_IF & 4)
	{
		*GPIO_IFC = 0x55;
		music = first_album.music4;
		SAMPLE_LIMIT = 3;
		*TIMER2_CMD = 1;
	}

	*GPIO_IFC = 0x55; /* clear even pins */
	LEDS = BUTTONS << 8; 
	
	
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
	// *GPIO_IFC = *GPIO_IF;
	// *GPIO_IFC = 0xAA; /* clear odd pins */
	LEDS = BUTTONS << 8;
	

	// *TIMER1_TOP = sound_arr[incr];
	// incr++;
	// if (incr > 6)
	// {
	// 	incr = 0;
	// }
	if (*GPIO_IF & 8)
	{
		*GPIO_IFC = 0xAA;
		music = first_album.music2;
		SAMPLE_LIMIT = 7;
		*TIMER2_CMD = 1;
	}

	if (*GPIO_IF & 2)
	{
		*GPIO_IFC = 0xAA;
		SAMPLE_LIMIT = 5;
		music = my_music[0];
		*TIMER2_CMD = 1;
	}
	*GPIO_IFC = 0xAA;
	
}
