/* global variables shared with interrupts */

#include "per_typedef.h"

#ifndef global_var_H
#define global_var_H 

// extern sound_list* game_music; 	// acces to all music
// extern sound* music;			// used for interrupts

#define BUFFERSIZE	256


extern const uart_cfg_t uartInitDef;
extern volatile cicularbuffer txBuf;
extern volatile cicularbuffer rxBuf;

extern UART_ALL_TypeDef *RS232, *MICROSD_SPI;  

#endif
