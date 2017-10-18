#include <stdint.h>
#include <stdbool.h>
 
#include "efm32gg.h"  
#include "global_var.h"
#include "per_typedef.h"
#include "per_const.h"

void setupNVIC(void); 
void setupGPIO(void);
void setupUART();

uart_cfg_t uartInit;

int main(void)
{
	setupGPIO();  
	setupUART();	
	setupNVIC();

	while(1)
	{
		// LEDS = BUTTONS << 8;
		// *GPIO_PA_DOUT = *GPIO_PE_DIN << 8;
	}

	return 0;
}

void setupNVIC()
{

	*ISER0 |= GPIO_EVEN_IRQ | GPIO_ODD_IRQ;
	// *ISER0 |= TIMER1_IRQ;// | TIMER2_IRQ;
	// *ISER0 |= DMA_IRQ;
	*ISER0 |= UART1_RX_IRQ | UART1_TX_IRQ;
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
