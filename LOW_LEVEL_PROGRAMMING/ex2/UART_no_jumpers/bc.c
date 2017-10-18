#include "efm32gg.h"
#include "per_typedef.h"
#include "uart.h"

#include "gpio.h"
#include "cmu.h"

void bc_peripheral(BC_per_TypeDef device)
{
	uint16_t perfControl;

	perfControl = SpiRegisterRead(USART2, BC_PERICON);

	switch(device)
	{
		case PER_UART1:
			perfControl &= ~(1 << 13);
			perfControl &= ~(1 << 11);
			perfControl |= (1 << 12);
			break;

		case PER_micro_SD:
			perfControl |= (1 << 0);
			break;
	}

	SpiRegisterWrite(USART2, BC_PERICON, perfControl);
}

void bc_control(BC_control_TypeDef mode)
{	
	enableCMU(CMU_GPIO, true);
	
	switch(mode)
	{
		case SPI_mode:
			/*-------------------BUS control mode------------------------------*/
			setupGPIO_conf(GPIO_PB, 15, PUSHPULL, 1);
			setupGPIO_conf(GPIO_PD, 13, PUSHPULL, 0);
			break;

		case EBI_mode:
			setupGPIO_conf(GPIO_PB, 15, PUSHPULL, 0);
			setupGPIO_conf(GPIO_PD, 13, PUSHPULL, 1);
			break;
	}
}