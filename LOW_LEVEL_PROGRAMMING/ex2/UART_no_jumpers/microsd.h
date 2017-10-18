#define CMD0  	0
#define CMD1 	1

#ifndef microsd_H
#define microsd_H

uint8_t WaitReady(void);
uint8_t MICROSD_XferSpi(uint8_t data);
int MICROSD_Select(void);
void MICROSD_Deselect(void);
uint8_t MICROSD_SendCmd(uint8_t cmd, uint32_t arg);
uint8_t spi_transfer(UART_TypeDef *uart, uint8_t data);
uint8_t powerUp(void);
uint8_t MICROSD_routine(void);

/* my functions, using AUTOTX */
uint8_t single_write(UART_TypeDef *uart, uint8_t data); 	/* write needed block */
uint8_t single_read(UART_TypeDef *uart);					/* keep receiving while reading out */

uint8_t my_ready(UART_TypeDef *uart, uint32_t retry); 		/* wait for startup, need to receive 0xFF */
uint8_t warmup(UART_TypeDef *uart, uint32_t retry);
#endif /* microsd_H */