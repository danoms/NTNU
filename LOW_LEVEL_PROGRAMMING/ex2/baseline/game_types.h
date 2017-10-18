/* types used for game */
#include <stdint.h>

#ifndef game_types_H
#define game_types_H

typedef struct sound{
	uint16_t note_f[350];
	uint16_t duration[350];
	uint16_t pause_after[350];
	uint16_t size; 
} sound; 

typedef struct sound_list{ 
	sound *intro;
	sound *button[8];
} sound_list;

#endif
