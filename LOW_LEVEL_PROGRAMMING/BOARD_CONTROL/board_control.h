#include <stdint.h>

#if defined ( MY_BOARD )

typedef enum {
	CB_RS232_SHUTDOWN,
	CB_RS232_UART,
	CB_RS232_LEUART,
} CB_Peripheral_Typedef; 

#endif /* MY_BOARD */


/* function to connect UART to serial outside */


#define BC_REGISTER_BASE 	0x80000000  	/* board control registers */

#define BC_REGISTER 		((volatile uint16_t*) BC_REGISTER_BASE)
#define PERICON 			((volatile uint16_t*)(BC_REGISTER + 0x18))	/* peripheral control, on board switches */


uint16_t controlRegister;

controlRegister = *PERICON; /* read peripheral controls */
controlRegister &= ~ (1 << 13); /* clear SHUTDOWN */
controlRegister &= ~ (1 << 11); /* clear LEUART */
controlRegister |= (1 << 12); /* set UART */
