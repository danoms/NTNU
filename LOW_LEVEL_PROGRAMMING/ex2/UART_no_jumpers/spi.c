#include <stdint.h>

#include "efm32gg.h"  

#define SPI_TX		2
#define SPI_RX		3
#define SPI_CLK		4
#define SPI_CS 		5

void SpiInit(void) {
	/* turn on SPI mode */

	/*-------------------BSP_BusControlModeSet------------------------------*/
	/* B15 : push-pull : out 1 */
	/* D13 : push-pull : out 0 */

	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_GPIO; /* enable clock for GPIO */
	
	*GPIO_PB_MODEH |= 4 << 28; /* pushpull, B15 */
	*GPIO_PB_DOUT |= 1 << 15; /* high */

	*GPIO_PD_MODEH |= 4 << 20; /* pushpull, D13 */
	*GPIO_PD_DOUT |= 1 << 13;  /* high */


	/*-------------------SpiBcInit------------------------------*/

	*GPIO_PC_MODEL |= 0x00444400; /* pushpull, C2 - C5 */
	*GPIO_PC_DOUT |= 0x0020;	/* C5 high */

	/*-------------------InitUSART2------------------------------*/

	*CMU_HFPERCLKEN0 |= CMU2_HFPERCLKEN0_USART2; /* enable clock for USART2 */

	#define USART_INITSYNC_DEFAULT                                                              
	{                                                                                          
	     usartEnable,       /* Enable RX/TX when init completed. */                                
	     0,                 /* Use current configured reference clock for configuring baudrate. */ 
	     1000000,           /* 1 Mbits/s. */                                                       
	     usartDatabits8,    /* 8 databits. */                                                      
	     true,              /* Master mode. */                                                     
	     false,             /* Send least significant bit first. */                                
	     usartClockMode0,   /* Clock idle low, sample on rising edge. */                           
	     false,             /* Not USART PRS input mode. */                                        
	     usartPrsRxCh0,     /* PRS channel 0. */                                                   
	     false,             /* No AUTOTX mode. */                                                  
	     false,             /* No AUTOCS mode */                                                   
	     0,                 /* Auto CS Hold cycles */                                              
	     0                  /* Auto CS Setup cycles */                                             
	}

	typedef struct
	{
	    USART_Enable_TypeDef    enable;
	    uint32_t                refFreq;
	    uint32_t                baudrate;
	    USART_Databits_TypeDef  databits;
	    bool                    master;
	    bool                    msbf;
	    USART_ClockMode_TypeDef clockMode;
	    bool                    prsRxEnable;
	    USART_PrsRxCh_TypeDef   prsRxCh;
	    bool                    autoTx;
	    bool                    autoCsEnable;
	    uint8_t                 autoCsHold;
	    uint8_t                 autoCsSetup;
	} USART_InitSync_TypeDef;

	


	
}