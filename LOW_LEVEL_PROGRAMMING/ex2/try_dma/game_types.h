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

/* DMA ------------------------------*/
/* for control config register */
/* size used */
#define byte 			0
#define halfword 		1
#define word 			2
#define no_increment	3

/* mode used */
#define stop 			0
#define basic			1
#define ping_pong 		3

typedef struct  {
	uint32_t dst_inc;
	uint32_t dst_size;
	uint32_t src_inc;
	uint32_t src_size;
	uint32_t dst_prot_ctrl;
	uint32_t src_prot_ctrl;
	uint32_t R_power;
	uint32_t n_minus_1;
	uint32_t next_useburst;
	uint32_t cycle_ctrl;
} channel_cfg;
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

/* for DMA descriptor creation */
typedef struct dma_descriptor {  
	volatile uint32_t* src_data_end_ptr; /* source end pointer*/
	volatile uint32_t* dst_data_end_ptr; /* destination end pointer */
	volatile uint32_t control; 
	uint32_t user;
} dma_descriptor ;//__attribute__ ((aligned(256)));

#endif
