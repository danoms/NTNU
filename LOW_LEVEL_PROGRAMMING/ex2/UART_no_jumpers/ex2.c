#include <stdint.h>
#include <stdbool.h>
 
#include "efm32gg.h"  
#include "global_var.h"
#include "per_typedef.h"
// #include "per_const.h"

#include "uart.h"
#include "uart_setup.h"
#include "bc.h"
#include "gpio.h"
#include "microsd.h"
#include "spi_sd.h"

void setupNVIC(void); 
void setupUART( void );

UART_ALL_TypeDef *RS232, *MICROSD_SPI;
UART_ALL_TypeDef RS232_space, MICROSD_SPI_space;

const char welcomeString[] = "Hello from RS232!\n" ;
uint32_t welLen = sizeof(welcomeString) - 1;

const uint8_t terminate_char = 10; /* new line \n*/ 

const uint8_t do_special = 'G';

uint8_t do_func(void)
{
	return my_ready(MICROSD_USART, 80);
	// return test_bench();
}

int main(void)
{
	RS232 = &RS232_space;
	MICROSD_SPI = &MICROSD_SPI_space;

	bc_control(SPI_mode); 		/* SPI addressing mode */


	setupGPIO();
	setupUART();
	setupNVIC();

	// SpiRegisterWrite(USART2, BC_LEDS, 0);

	bc_peripheral(PER_UART1);		/*connect UART1 to serial RS232*/
	bc_peripheral(PER_micro_SD);	/* connect microSD */

	// uint8_t temp = MICROSD_routine();

	// putData(&temp,1,RS232);
	uint8_t temp3;


	temp3 = do_func();

	putData(&temp3,1,RS232);
	uint32_t timeout = 500;
	while(1)
	{
		__asm__ ("WFI");
		if (timeout > 0)
		{
			timeout--;
		}
		if ((RS232->rxBuf.data[RS232->rxBuf.wdI - 1] == terminate_char) && (RS232->rxBuf.data[RS232->rxBuf.wdI - 2] != do_special))
		{
			uint8_t temp[BUFFERSIZE];
			uint32_t length = getData(temp, 0, RS232);
			putData(temp, length, RS232);
		}
		if (RS232->rxBuf.data[RS232->rxBuf.wdI - 1] == do_special && (timeout == 0))
		{
			// RS232->rxBuf.data[RS232->rxBuf.wdI - 2] = 0;
			timeout = 500;
			uint8_t temp6[BUFFERSIZE];
			uint32_t length = getData(temp6, 0, RS232);
			temp6[length] = 10;
			temp6[length + 1] = do_func();
			putData(temp6, length + 2, RS232);
		}

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
