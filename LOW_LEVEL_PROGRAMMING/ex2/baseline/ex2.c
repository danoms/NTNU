#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

// #include "music.h" /* for sound generating */
/*
 * TODO calculate the appropriate sample period for the sound wave(s) you 
 * want to generate. The core clock (which the timer clock is derived
 * from) runs at 14 MHz by default. Also remember that the timer counter
 * registers are 16 bits. 
 */
/*
 * The period between sound samples, in clock cycles 
 */
#define   SAMPLE_PERIOD   90 //~48000

#define BUTTON_PRESSED(x) 	(1 << x)
#define START_SOUND 		(*TIMER2_CMD = 1)
#define STOP_SOUND			(*TIMER2_CMD = 2)
/*
 * Declaration of peripheral setup functions 
 */
void setupTimer(uint32_t period);
void setupDAC();
void setupNVIC();
void setupGPIO();
/*
 * Your code will start executing here 
 */
int main(void)
{
	/*
	 * Call the peripheral setup functions 
	 */
	setupGPIO();
	setupDAC();
	setupTimer(SAMPLE_PERIOD);

	/*
	 * Enable interrupt handling 
	 */
	// setupNVIC();
	/*
	 * TODO for higher energy efficiency, sleep while waiting
	 * interrupts instead of infinite loop for busy-waiting 
	 */
	int sample_arr[][10	] = {
		{10,10,12,30,35,40,40,35,20,10},
		{30,20,56,50,20,34,52,23,20,23},
		{64,20,40,50,20,30,60,80,20,65},
		{73,20,74,50,20,30,60,54,54,90}
	};

	int sample_limit = 10;
	int limit = 10;
	int song = 0;

	while (1) {
		if (~BUTTONS & BUTTON_PRESSED(0))
		{	
			song = 1;
			*TIMER1_CMD = 1;
		}

		if (~BUTTONS & BUTTON_PRESSED(1))
		{	
			song = 2;
			*TIMER1_CMD = 1;
		}

		if (~BUTTONS & BUTTON_PRESSED(2))
		{	
			song = 3;
			*TIMER1_CMD = 1;
		}

		if (~BUTTONS & BUTTON_PRESSED(3))
		{	
			song = 3;
			*TIMER1_CMD = 1;
		}

		if (*TIMER1_CNT == SAMPLE_PERIOD )
		{
			// generate note
			static int state = 0;
			static int counter = 0;
			static int timer_cntr = 0;

			int test_sample = 0x00C;

			timer_cntr++;
			state++;

			if (timer_cntr > 1000)
			{
				timer_cntr = 0;
				// limit +=20;
				static int note_cnt = 0;
				note_cnt++;
				limit = sample_arr[song][note_cnt];

				if (note_cnt == sample_limit-1)
				{
					note_cnt=0;
					*TIMER1_CMD = 2; /* turn off timer */
				}

				// if (limit > 120)
				// {
				// 	limit = 10;
				// }
			}

			if (state > limit)
			{
				*DAC0_CH0DATA ^= test_sample;
				*DAC0_CH1DATA ^= test_sample;
				counter++;
				state = 0;
			}
		}
	}

	return 0;
}

void setupNVIC()
{

	*ISER0 |= GPIO_EVEN_IRQ | GPIO_ODD_IRQ; /* generate interrupts for GPIO pins*/
	*ISER0 |= TIMER1_IRQ | TIMER2_IRQ; /* generate interrupts for timers */
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
