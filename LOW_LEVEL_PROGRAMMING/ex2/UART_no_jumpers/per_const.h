#include "global_var.h"
#include "per_typedef.h"

#ifndef per_const_H
#define per_const_H

const uart_cfg_t uartInitDef = {
	14000000,
	16,
	9600,
};

const UART_ALL_TypeDef UART_INIT= {
	{{0},0,0,0},
	{{0},0,0,0},
	UART1,
};

#endif /* per_const_H */