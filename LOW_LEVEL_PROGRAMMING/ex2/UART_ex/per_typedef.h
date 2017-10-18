/* -------------------------- DMA --------------------------------------------------------*/
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

#ifndef per_typedef_H
#define per_typedef_H

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
} channel_cfg_t;

/* for DMA descriptor creation */
typedef struct {  
	volatile uint32_t* src_data_end_ptr; /* source end pointer*/
	volatile uint32_t* dst_data_end_ptr; /* destination end pointer */
	volatile uint32_t control; 
	uint32_t user;
} dma_descriptor_t ;//__attribute__ ((aligned(256)));

/* -------------------------- DMA --------------------------------------------------------*/
typedef struct {
	uint32_t refFreq ;
	uint32_t oversample;
	uint32_t baudrate;
} uart_cfg_t;

#endif