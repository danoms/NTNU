/* -------------------------- DMA --------------------------------------------------------*/
/* for control config register */
/* size used */
#define BUFFERSIZE	256

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

#define __IO 	volatile

typedef enum {
	SPI_mode,
	EBI_mode,
} BC_control_TypeDef;

typedef enum {
	PER_UART1,
	PER_micro_SD,
} BC_per_TypeDef;

typedef enum {
	CMU_GPIO,
	CMU_USART0,
	CMU_USART2,
	CMU_UART1,
	CMU_DAC0,
	CMU_PRS,
} CMU_TypeDef;

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


typedef struct  {
	uint8_t data[BUFFERSIZE];
	uint32_t rdI; /* read index */
	uint32_t wdI; /*write index*/
	uint32_t bytesPending;  
} cicularbuffer;


/* ----------UARTS ----------*/
typedef struct {
	__IO uint32_t CTRL;
	__IO uint32_t FRAME;
	__IO uint32_t TRIGCTRL;
	__IO uint32_t CMD;
	__IO uint32_t STATUS;
	__IO uint32_t CLKDIV;
	__IO uint32_t RXDATAX;
	__IO uint32_t RXDATA;
	__IO uint32_t RXDOUBLEX;
	__IO uint32_t RXDOUBLE;
	__IO uint32_t RXDATAXP;
	__IO uint32_t RXDOUBLEXP;
	__IO uint32_t TXDATAX;
	__IO uint32_t TXDATA;
	__IO uint32_t TXDOUBLEX;
	__IO uint32_t TXDOUBLE;
	__IO uint32_t IF;
	__IO uint32_t IFS;
	__IO uint32_t IFC;
	__IO uint32_t IEN;
	__IO uint32_t IRCTRL;
	__IO uint32_t ROUTE;
	__IO uint32_t INPUT;
	__IO uint32_t I2SCTRL;
} UART_TypeDef;


typedef struct {
	cicularbuffer txBuf;
	cicularbuffer rxBuf;
	UART_TypeDef *addr;
} UART_ALL_TypeDef;

/* ----------GPIO ----------*/
typedef struct {
	__IO uint32_t CTRL;
	__IO uint32_t MODEL;
	__IO uint32_t MODEH;
	__IO uint32_t DOUT;
	__IO uint32_t DOUTSET;
	__IO uint32_t DOUTCLR;
	__IO uint32_t DOUTTGL;
	__IO uint32_t DIN;
	__IO uint32_t PINLOCKIN;
} GPIO_PORT_TypeDef;

typedef struct {
	__IO uint32_t EXTIPSELL;
	__IO uint32_t EXTIPSELH;
	__IO uint32_t EXTIRISE;
	__IO uint32_t EXTIFALL;
	__IO uint32_t IEN;
	__IO uint32_t IF;
	__IO uint32_t IFS;
	__IO uint32_t IFC;
	__IO uint32_t ROUTE;
	__IO uint32_t INSENSE;
	__IO uint32_t LOCK;
	__IO uint32_t CTRL;
	__IO uint32_t CMD;
	__IO uint32_t EM4WUEN;
	__IO uint32_t EM4WUPOL;
	__IO uint32_t EM4WUCAUSE;
} GPIO_PIN_TypeDef;


#endif