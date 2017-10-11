#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "global_var.h"
#include "dma.h"
// #include "sample_note_A.h" 
  
#include "game_types.h"

#define PIN(x) 			(1 << x)
#define N_minus_1(x) 	(x << 4)

/*
 * TIMER1 interrupt handler 
 */




void __attribute__ ((interrupt)) TIMER1_IRQHandler() /* control periodic data to DAC */
{
	/*
	 * TODO feed new samples to the DAC remember to clear the pending
	 * interrupt by writing 1 to TIMER1_IFC 
	 */
	static uint32_t counter = 0;
	counter++;
	LEDS = counter;
		// *TIMER1_IFC = 1; /* clear main flag */ 
		// int static sample = 0;
		// sample++;
		// if (sample > size-1)
		// {
		// 	sample = 0; 
		// }
		// *DAC0_CH0DATA = sample_note_A[sample];
		// *DAC0_CH1DATA = sample_note_A[sample]; 	

}

void __attribute__ ((interrupt)) DMA_IRQHandler()
{
	/*
		DMA done routine
	*/

	// channel_cfg my_config = channel_cfg_default;

	static bool dma_primary_desc = true;
	dma_primary_desc = !dma_primary_desc;

	/* clear flags */
	*DMA_IFC = 1; /* channel 0 */
	// LEDS = 0x2200;
	
	
	
	if (dma_primary_desc)
	{
		updateControl(&dma_primary[0], &config); /* primary descriptor config */
		LEDS = 0xF000;
	} else {
		updateControl(&dma_alternate[0], &config); /* alternate descriptor config */
		LEDS = 0x0F00;
	}
	// LEDS = 0Xf000;
}

void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler()
{
	*GPIO_IFC = *GPIO_IF;

	// LEDS = BUTTONS << 8;
	// LEDS = 0xF000;
}

void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler()
{
	*GPIO_IFC = *GPIO_IF;
	// LEDS = BUTTONS << 8;
	// LEDS = 0xF000;
}
