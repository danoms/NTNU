/* global variables shared with interrupts */

#include "game_types.h"

#ifndef global_var_H
#define global_var_H 

// extern sound_list* game_music; 	// acces to all music
// extern sound* music;			// used for interrupts

extern volatile dma_descriptor dma_primary[1];
extern volatile dma_descriptor* dma_alternate;
extern volatile channel_cfg config;

#endif
