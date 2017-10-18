#include <stdint.h>

#include "efm32gg.h"  

#define SPI_TX		2
#define SPI_RX		3
#define SPI_CLK		4
#define SPI_CS 		5

typedef struct
{
	uint32_t               refFreq;
	uint32_t               baudrate;
	USART_OVS_TypeDef      oversampling;
	USART_Databits_TypeDef databits;
	USART_Parity_TypeDef   parity;
	USART_Stopbits_TypeDef stopbits;
} USART_InitAsync_TypeDef;


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

	uint32_t baudrate = 7000000;
	
}