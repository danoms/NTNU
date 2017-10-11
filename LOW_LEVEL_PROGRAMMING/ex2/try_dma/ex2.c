#include <stdint.h>
#include <stdbool.h>
 
#include "efm32gg.h"  
 
#include "game_types.h"
// #include "sample_note_A.h"
#include "global_var.h"
#include "dma.h"
#include "timer.h"

channel_cfg channel_cfg_default= {
	byte, /* increment by dst*/
	byte, /* destination size */
	byte, /* increment by src */
	byte, /* source size */
	0,       //HPROT ,  not privileged 
	0,
	0, /* arbitrates after */
	99, /* n_minus_1, transfers */
	0, /* useburst ??? */
	basic /* mode */
} ;

// #include "global_var.h" 
/*
 * TODO calculate the appropriate sample period for the sound wave(s) you 
 * want to generate. The core clock (which the timer clock is derived
 * from) runs at 14 MHz by default. Also remember that the timer counter
 * registers are 16 bits. 
 */
/*
 * The period between sound samples, bin clock cycles 
 */ 
#define   SAMPLE_PERIOD   318 // 44100 Hz  

/* global for interrupts */
// sound_list* game_music;
// sound* music;  sdf sdf sdf 

/*
 * Declaration of peripheral setup functions 
 */ 
void setupDAC();    
void setupNVIC(); 
void setupGPIO();
void setupDMA(volatile dma_descriptor* dma_descr);
void setupPRS();

/* game setup functions */
// void setupMUSIC(sound_list* my_music);
/*
 * Your code will start executing here 
 */

// volatile dma_descriptor* test_arg = 0;
uint32_t size = 100;
uint16_t sample_note_A[] = {
	0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,10,
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
	10,10,10,10,10,10,10,10,10
};


/* DMA stuff*/
volatile dma_descriptor dma_primary[1] __attribute__ ((aligned(512))); /* create for all channels, primary and alternat */
volatile dma_descriptor* dma_alternate = (dma_descriptor*)(&dma_primary[0] + 16); /*add 512 to move up 0x100 addres. 16*32 = 512 */
volatile channel_cfg config;

int main(void)
{
	// sound_list my_music; 		// create space for music pointers
	// game_music = &my_music;		// point to this space
	// setupMUSIC(game_music); 	// make this space point to songs

	/* 
		alligned because:
			[8] 	: 1/0 	= primary/alternate
			[7:4] 	: xxxx 	= channel
			[3:0]	: 0x00	= source end pointer 
			[3:0]	: 0x04 	= destination end pointer
			[3:0] 	: 0x08	= config register
			[3:0]	: 0x0C	= undefined
	*/
	config = channel_cfg_default;

	
	// dma_descriptor* dma_alternate = (dma_descriptor*) (&dma_primary[0] +0x100);

	// dma_descriptor dma_alternate[12] __attribute__ ((aligned(256)));

	/* create primary DMA descriptor */
	// dma_descriptor dma_desc ;  /* creates space for descriptor */
	setupGPIO();  
	setupNVIC();

	setupTimer(SAMPLE_PERIOD);
	setupPRS();
	setupDAC();


	
	
	// test_arg = &dma_desc;
	config.dst_inc 		= no_increment; /* stay on DATA CHANNEL0*/
	config.dst_size 	= halfword; 	/* size is 16 bits*/
	config.src_inc 		= halfword;		/* increment by halfword = 16 bits */
	config.src_size 	= halfword;		/* size is 16 bits */
	config.n_minus_1 	= size - 1;		/* samples in array */
	config.cycle_ctrl 	= ping_pong; 	/* mode */

	/* assigning pointers to primary descriptor */
	dma_primary[0].src_data_end_ptr = (volatile uint32_t*)&sample_note_A[size-1]; 
	dma_primary[0].dst_data_end_ptr = (volatile uint32_t*)DAC0_CH0DATA;

	// dma_primary[0].src_data_end_ptr = (volatile uint32_t*)0xFEED;
	// dma_primary[0].dst_data_end_ptr = (volatile uint32_t*)0xBEEF;

	/* assigning pointers to alternate descriptor */
	// dma_alternate[0].src_data_end_ptr = (volatile uint32_t*)&sample_note_A[size-1];
	// dma_alternate[0].dst_data_end_ptr = (volatile uint32_t*)DAC0_CH0DATA;
	dma_alternate[0].src_data_end_ptr = (volatile uint32_t*)&sample_note_A[size-1]; 
	dma_alternate[0].dst_data_end_ptr = (volatile uint32_t*)DAC0_CH0DATA;

	// dma_alternate->src_data_end_ptr = (volatile uint32_t*)0xFEED;
	// dma_alternate[0].dst_data_end_ptr = (volatile uint32_t*)0xBEEF;

	updateControl(&dma_primary[0], &config); /* primary descriptor config */
	updateControl(&dma_alternate[0], &config); /* alternate descriptor config */
	setupDMA(&dma_primary[0]);
	

	/*
	 * Call the peripheral setup functions 
	 */
	
	
	

	/*
	 * Enable interrupt handling 
	 */ 
	/*
	 * TODO for higher energy efficiency, sleep while waiting
	 * interrupts instead of infinite loop for busy-waiting 
	 */
	// __asm__ ("WFI");

	// music = game_music->intro; // first played song on restart
	while(1)
	{
	}
	// while (1) {
	// 	LEDS = BUTTONS << 8;
	// }

	return 0;
}

void setupNVIC()
{

	*ISER0 |= GPIO_EVEN_IRQ | GPIO_ODD_IRQ;
	// *ISER0 |= TIMER1_IRQ;// | TIMER2_IRQ;
	*ISER0 |= DMA_IRQ;
	/*
	 * TODO use the NVIC ISERx registers to enable handling of
	 * interrupt(s) remember two things are necessary for interrupt
	 * handling: - the peripheral must generate an interrupt signal - The
	 * NVIC must be configured to make the CPU handle the signal You will
	 * need TIMER1, GPIO odd and GPIO even interrupt handling for this
	 * assignment. 
	 */
}

/*
 * if other interrupt handlers are needed, use the following names:
 * NMI_Handler HardFault_Handler MemManage_Handler BusFault_Handler
 * UsageFault_Handler Reserved7_Handler Reserved8_Handler
 * Reserved9_Handler Reserved10_Handler SVC_Handler DebugMon_Handler
 * Reserved13_Handler PendSV_Handler SysTick_Handler DMA_IRQHandler
 * GPIO_EVEN_IRQHandler TIMER0_IRQHandler USART0_RX_IRQHandler
 * USART0_TX_IRQHandler USB_IRQHandler ACMP0_IRQHandler ADC0_IRQHandler
 * DAC0_IRQHandler I2C0_IRQHandler I2C1_IRQHandler GPIO_ODD_IRQHandler
 * TIMER1_IRQHandler TIMER2_IRQHandler TIMER3_IRQHandler
 * USART1_RX_IRQHandler USART1_TX_IRQHandler LESENSE_IRQHandler
 * USART2_RX_IRQHandler USART2_TX_IRQHandler UART0_RX_IRQHandler
 * UART0_TX_IRQHandler UART1_RX_IRQHandler UART1_TX_IRQHandler
 * LEUART0_IRQHandler LEUART1_IRQHandler LETIMER0_IRQHandler
 * PCNT0_IRQHandler PCNT1_IRQHandler PCNT2_IRQHandler RTC_IRQHandler
 * BURTC_IRQHandler CMU_IRQHandler VCMP_IRQHandler LCD_IRQHandler
 * MSC_IRQHandler AES_IRQHandler EBI_IRQHandler EMU_IRQHandler 
 */
