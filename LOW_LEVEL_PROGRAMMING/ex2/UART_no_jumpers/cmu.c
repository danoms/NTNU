#include <stdint.h>
#include <stdbool.h>
#include "efm32gg.h"

#include "cmu.h"

void enableCMU(CMU_TypeDef perif, bool enable)
{
	uint32_t configRegister = 0;

	switch(perif)
	{
		case CMU_GPIO:
			configRegister = 1 << 13;
			break;

		case CMU_USART0:
			configRegister = 1;
			break;
			
		case CMU_USART2:
			configRegister = 1 << 2;
			break;

		case CMU_UART1:
			configRegister = 1 << 4;
			break;
		
		case CMU_DAC0:
			configRegister = 1 << 17;
			break;

		case CMU_PRS:
			configRegister = 1 << 15;
			break;
	}

	if (enable)
	{
		*CMU_HFPERCLKEN0 |= configRegister;
	} else {
		*CMU_HFPERCLKEN0 &= ~configRegister;
	}
}