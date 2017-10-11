#include "dma.h"

#include <stdint.h>

#include "efm32gg.h"  
#include "game_types.h"

/* size used */
#define byte 			0
#define halfword 		1
#define word 			2
#define no_increment	3

/* mode used */
#define stop 			0
#define basic			1
#define ping_pong 		3

/* for channel_cfg register */
#define cycle_ctrl(x) 		(x << 0)
#define next_useburst(x) 	(x << 3)
#define N_minus_1(x) 		(x << 4)
#define R_power(x) 			(x << 14)
#define src_prot_ctrl(x)	(x << 18)
#define dst_prot_ctrl(x)	(x << 21)
#define src_size(x) 		(x << 24)
#define src_inc(x) 			(x << 26)
#define dst_size(x) 		(x << 28)
#define dst_inc(x) 			(x << 30)

/* for channel control */
#define SOURCESEL(x) 		(x << 16)
#define SIGSEL(x) 			(x << 0)

/* sources */
#define DAC0 		10
#define TIMER1 		25

/* signals */
#define DAC0CH0 	0
#define DAC0CH1 	1
#define TIMERUFOF 	0

/* channels */
#define CH(x)	(1 << x)


void updateControl(volatile dma_descriptor* dma_descr, volatile channel_cfg* cfg) {
	dma_descr->control = 0; /* clear it, then add new values */
	dma_descr->control |= dst_inc(cfg->dst_inc);
	dma_descr->control |= dst_size(cfg->dst_size);
	dma_descr->control |= src_inc(cfg->src_inc);
	dma_descr->control |= src_size(cfg->src_size);
	dma_descr->control |= dst_prot_ctrl(cfg->dst_prot_ctrl);
	dma_descr->control |= src_prot_ctrl(cfg->src_prot_ctrl);
	dma_descr->control |= R_power(cfg->R_power);
	dma_descr->control |= N_minus_1(cfg->n_minus_1);
	dma_descr->control |= next_useburst(cfg->next_useburst);
	dma_descr->control |= cycle_ctrl(cfg->cycle_ctrl);
}

void setupDMA( volatile dma_descriptor* dma_descr) {

	/* write data to descriptor */

	// updateControl(dma_descr, cfg);

	*CMU_HFCORECLKEN0 |= CMU_HFCORECLKEN0_DMA; /* enable clock for DMA */

	*DMA_CONFIG = 1; /* enable DMA controller */
	
	*DMA_CTRLBASE = (uint32_t)dma_descr; /* write descriptor address */
	*DMA_CHUSEBURSTC = CH(0); /* clear use-burst */
	*DMA_REQMASKC = 1; /* enable signals from peripherals for channel 0 */
	*DMA_CHALTC = CH(0); /* set primary structure*/
	// *DMA_LOOP0 = 1 << 16; /* enable looping */
	// *DMA_LOOP0 |= 99; /* N_MINUS_1 reloaded for next loop */

	

	*DMA_IEN = CH(0); /* enable interrupts on complete */ 

	*DMA_CH0_CTRL = SOURCESEL(DAC0) | SIGSEL(DAC0CH0); /* choose source and signal */
	

	

	*DMA_CHENS = CH(0); /* enable channel */

}