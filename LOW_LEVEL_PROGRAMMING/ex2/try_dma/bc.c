#include <stdint.h>

#include "efm32gg.h"

void setupBC() {

	/* connect MCU UART to outside world
		PB9 : U1_TX#2
		PB10: U1_RX#2
	 */

	uint16_t controlRegister;
	controlRegister = *BC_PERICON; /* read peripheral control register */

	CLEAR(controlRegister, 13); /* clear SHUTDOWN */
	CLEAR(controlRegister, 11); /* clear LEUART */
	SET(controlRegister, 12);   /* set UART */

	*BC_PERICON = controlRegister; /* write back modified controls */
}