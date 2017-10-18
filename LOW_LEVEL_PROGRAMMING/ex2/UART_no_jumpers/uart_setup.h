#define MICROSD_USART 		USART0
#define MICROSD_PORT 		GPIO_PE
#define MICROSD_LOW_FREQ	12000000


#define MICROSD_CLK		5
#define MICROSD_CS		4
#define MICROSD_DI		7
#define MICROSD_DO		6

#define OUT_HIGH(port, pin)	(port->DOUTSET |= 1 << pin)
#define OUT_LOW(port, pin)	(port->DOUTCLR |= 1 << pin) 

#ifndef uart_setup_H
#define uart_setup_H

void UART1_RS232(void);
void BC_USART2_SPI(void);
void MICROSD_USART_SPI(void);
void UART_init(UART_ALL_TypeDef *system, UART_TypeDef *device);

#endif /* uart_setup_H */