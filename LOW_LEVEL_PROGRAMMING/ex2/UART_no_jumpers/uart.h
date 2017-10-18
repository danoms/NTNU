#include "per_typedef.h"

#ifndef uart_H
#define uart_H

uint32_t calculate_clkdiv(uart_cfg_t *uart);
uint32_t sync_clkdiv(uart_cfg_t *uart);
uint16_t SpiRegisterRead(UART_TypeDef *UART, volatile uint16_t *addr);
void SpiRegisterWrite(UART_TypeDef *UART, volatile uint16_t *addr, uint16_t data);
void my_USART_Tx(UART_TypeDef *UART, uint8_t data);
uint8_t my_USART_Rx(UART_TypeDef *UART) ;

void putData(uint8_t *data, uint32_t length, UART_ALL_TypeDef *UART);
uint32_t getData(uint8_t *data, uint32_t dataLength, UART_ALL_TypeDef *UART);

void intToChar(uint32_t *data);
void check_BC_SPI(void);

#endif /*uart_H*/