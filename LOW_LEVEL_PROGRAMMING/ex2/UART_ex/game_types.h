/* types used for game */
#include <stdint.h>

#ifndef game_types_H
#define game_types_H

/* MUSIC ------------------------- */
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




//  const channel_cfg_default = {
// 	byte, /* increment by dst*/
// 	byte, /* destination size */
// 	byte, /* increment by src */
// 	byte,  source size 
// 	0, /* HPROT ,  not privileged */
// 	0,
// 	0, /* arbitrates after */
// 	99, /* n_minus_1, transfers */
// 	0, /* useburst ??? */
// 	basic /* mode */
// };

// typedef struct channel_cfg channel_cfg;



#endif
