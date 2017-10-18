#include <stdint.h> 

#include "per_typedef.h"

// User config
#define SET(reg, bit) 		(reg |=   (1 << bit))
#define CLEAR(reg, bit)		(reg &= ~ (1 << bit)) 	

#define LEDS 			*GPIO_PA_DOUT
#define BUTTONS 		*GPIO_PE_DIN

/* IRQ - interrupt reques lines */
#define GPIO_EVEN_IRQ 	(1 << 1) 
#define GPIO_ODD_IRQ 	(1 << 11)
#define TIMER1_IRQ		(1 << 12)
#define TIMER2_IRQ 		(1 << 13)
#define DMA_IRQ 		(1 << 0)
#define UART1_RX_IRQ 	(1 << 22)
#define UART1_TX_IRQ 	(1 << 23)

/* BOARD CONTROLLER */

#define BC_REGISTER_BASE    0x80000000

#define BC_MAGIC 		((volatile uint16_t*)(BC_REGISTER_BASE + 0x04))
#define BC_PERICON     	((volatile uint16_t*)(BC_REGISTER_BASE + 0x18)) /* peripheral control, MUX needed */
#define BC_LEDS 		((volatile uint16_t*)(BC_REGISTER_BASE + 0x06))

// GPIO
#define GPIO_BASE 0x40006000

#define GPIO_PIN 		(GPIO_BASE + 0x100) 

#define GPIO_PA_BASE     (GPIO_BASE + 0x000)
#define GPIO_PB_BASE     (GPIO_BASE + 0x024)
#define GPIO_PC_BASE     (GPIO_BASE + 0x048)
#define GPIO_PD_BASE     (GPIO_BASE + 0x06C)
#define GPIO_PE_BASE	 (GPIO_BASE + 0x090)

#define GPIO_PA 		((GPIO_PORT_TypeDef*)GPIO_PA_BASE)
#define GPIO_PB 		((GPIO_PORT_TypeDef*)GPIO_PB_BASE) 
#define GPIO_PC 		((GPIO_PORT_TypeDef*)GPIO_PC_BASE) 
#define GPIO_PD 		((GPIO_PORT_TypeDef*)GPIO_PD_BASE) 
#define GPIO_PE 		((GPIO_PORT_TypeDef*)GPIO_PE_BASE) 


#define GPIO 			((GPIO_PIN_TypeDef*)GPIO_PIN)

// CMU - clock management unit

#define CMU_BASE2 0x400c8000

#define CMU_HFPERCLKDIV  ((volatile uint32_t*)(CMU_BASE2 + 0x008))
#define CMU_HFCORECLKEN0 ((volatile uint32_t*)(CMU_BASE2 + 0x040))
#define CMU_HFPERCLKEN0  ((volatile uint32_t*)(CMU_BASE2 + 0x044))
#define CMU_CMD          ((volatile uint32_t*)(CMU_BASE2 + 0x024))

// #define CMU_DAC0   (1 << 17)
// #define CMU_PRS    (1 << 15)
// #define CMU_GPIO   				(1 << 13)
// #define CMU_TIMER1 (1 << 6)
// #define CMU_TIMER2 (1 << 7)
// #define CMU_USART2	(1 << 2)
// #define CMU_UART1 	(1 << 4)
// #define CMU_USART2 (1 << 2)
// #define CMU_USART0 (1 << 0) /* */

#define CMU_DMA (1 << 0)

// TIMER1

#define TIMER1_BASE 0x40010400

#define TIMER1_CTRL		((volatile uint32_t*)(TIMER1_BASE + 0x00))
#define TIMER1_CMD 		((volatile uint32_t*)(TIMER1_BASE + 0x04))
#define TIMER1_IEN 		((volatile uint32_t*)(TIMER1_BASE + 0x0c))
#define TIMER1_IF 		((volatile uint32_t*)(TIMER1_BASE + 0x10))
#define TIMER1_IFC 		((volatile uint32_t*)(TIMER1_BASE + 0x18))
#define TIMER1_TOP 		((volatile uint32_t*)(TIMER1_BASE + 0x1c))
#define TIMER1_CNT 		((volatile uint32_t*)(TIMER1_BASE + 0x24))
#define TIMER1_CC0_CTRL	((volatile uint32_t*)(TIMER1_BASE + 0x30))
#define TIMER1_CC0_CCV	((volatile uint16_t*)(TIMER1_BASE + 0x34))
#define TIMER1_CC0_CCVB	((volatile uint16_t*)(TIMER1_BASE + 0x3C))

#define TIMER2_BASE 0x40010800

#define TIMER2_CTRL		((volatile uint32_t*)(TIMER2_BASE + 0x00))
#define TIMER2_CMD 		((volatile uint32_t*)(TIMER2_BASE + 0x04))
#define TIMER2_IEN 		((volatile uint32_t*)(TIMER2_BASE + 0x0c))
#define TIMER2_IF 		((volatile uint32_t*)(TIMER2_BASE + 0x10))
#define TIMER2_IFC 		((volatile uint32_t*)(TIMER2_BASE + 0x18))
#define TIMER2_TOP 		((volatile uint32_t*)(TIMER2_BASE + 0x1c))
#define TIMER2_CNT 		((volatile uint32_t*)(TIMER2_BASE + 0x24))
#define TIMER2_CC0_CTRL	((volatile uint32_t*)(TIMER2_BASE + 0x30))
#define TIMER2_CC0_CCV	((volatile uint16_t*)(TIMER2_BASE + 0x34))
#define TIMER2_CC0_CCVB	((volatile uint16_t*)(TIMER2_BASE + 0x3C))

// NVIC - nested vector interrupt controller

#define ISER0 ((volatile uint32_t*)0xe000e100)
#define ISER1 ((volatile uint32_t*)0xe000e104)
#define ICER0 ((volatile uint32_t*)0xe000e180)
#define ICER1 ((volatile uint32_t*)0xe000e184)
#define ISPR0 ((volatile uint32_t*)0xe000e200)
#define ISPR1 ((volatile uint32_t*)0xe000e204)
#define ICPR0 ((volatile uint32_t*)0xe000e280)
#define ICPR1 ((volatile uint32_t*)0xe000e284)
#define IABR0 ((volatile uint32_t*)0xe000e300)
#define IABR1 ((volatile uint32_t*)0xe000e304)

// IPR - interrupt priority registers

#define IPR_BASE  0xe000e400

#define IPR0 ((volatile uint32_t*)(IPR_BASE + 0x00))
#define IPR1 ((volatile uint32_t*)(IPR_BASE + 0x04))
#define IPR2 ((volatile uint32_t*)(IPR_BASE + 0x08))
#define IPR3 ((volatile uint32_t*)(IPR_BASE + 0x0c))

// EMU - energy management unit

#define EMU_BASE2 0x400c6000

#define EMU_CTRL 	((volatile uint32_t*)(EMU_BASE2 + 0x000))
#define EMU_MEMCTRL	((volatile uint32_t*)(EMU_BASE2 + 0x004))

#define BLK123 7

// DAC0

#define DAC0_BASE2 0x40004000

#define DAC0_CTRL     ((volatile uint32_t*)(DAC0_BASE2 + 0x000))
#define DAC0_CH0CTRL  ((volatile uint32_t*)(DAC0_BASE2 + 0x008))
#define DAC0_CH1CTRL  ((volatile uint32_t*)(DAC0_BASE2 + 0x00c))
#define DAC0_IEN      ((volatile uint32_t*)(DAC0_BASE2 + 0x010))
#define DAC0_IF       ((volatile uint32_t*)(DAC0_BASE2 + 0x014))
#define DAC0_IFS      ((volatile uint32_t*)(DAC0_BASE2 + 0x018))
#define DAC0_IFC      ((volatile uint32_t*)(DAC0_BASE2 + 0x01c))
#define DAC0_CH0DATA  ((volatile uint32_t*)(DAC0_BASE2 + 0x020))
#define DAC0_CH1DATA  ((volatile uint32_t*)(DAC0_BASE2 + 0x024))
#define DAC0_COMBDATA ((volatile uint32_t*)(DAC0_BASE2 + 0x028))

// DMA

#define DMA_BASE 0x400c2000

#define DMA_STATUS      ((volatile uint32_t*)(DMA_BASE + 0x0000))
#define DMA_CONFIG      ((volatile uint32_t*)(DMA_BASE + 0x0004))
#define DMA_CTRLBASE    ((volatile uint32_t*)(DMA_BASE + 0x0008))
#define DMA_ALTCTRLBASE ((volatile uint32_t*)(DMA_BASE + 0x000c))
#define DMA_CHUSEBURSTS ((volatile uint32_t*)(DMA_BASE + 0x0018))
#define DMA_CHUSEBURSTC ((volatile uint32_t*)(DMA_BASE + 0x001c))
#define DMA_REQMASKC    ((volatile uint32_t*)(DMA_BASE + 0x0024))
#define DMA_CHENS       ((volatile uint32_t*)(DMA_BASE + 0x0028))
#define DMA_CHALTC      ((volatile uint32_t*)(DMA_BASE + 0x0034))
#define DMA_IF 			((volatile uint32_t*)(DMA_BASE + 0x1000))
#define DMA_IFC         ((volatile uint32_t*)(DMA_BASE + 0x1008))
#define DMA_IEN         ((volatile uint32_t*)(DMA_BASE + 0x100c))
#define DMA_LOOP0 		((volatile uint32_t*)(DMA_BASE + 0x1020))
#define DMA_CH0_CTRL    ((volatile uint32_t*)(DMA_BASE + 0x1100))

// PRS - peripheral reflex system

#define PRS_BASE 0x400cc000

#define PRS_CH0_CTRL ((volatile uint32_t*)(PRS_BASE + 0x010))

// System Control Block

#define SCR          ((volatile uint32_t*)0xe000ed10)
#define SYSTICK_CTRL ((volatile uint32_t*)0xe000e010)
#define SYSTICK_LOAD ((volatile uint32_t*)0xe000e014)

#define SLEEPDEEP 	(1 << 2)
#define SLEEPONEXIT (1 << 1)

// UART1

#define UART1_BASE 0x4000E400
#define USART2_BASE 0x4000C800
#define USART0_BASE 0x4000C000

#define UART1 	((UART_TypeDef*)UART1_BASE)
#define USART2 	((UART_TypeDef*)USART2_BASE)
#define USART0 	((UART_TypeDef*)USART0_BASE)