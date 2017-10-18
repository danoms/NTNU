#include "em_gpio.h"

#ifndef gpio_H
#define gpio_H

void setupGPIO(void);
void setupGPIO_conf(GPIO_PORT_TypeDef *port, uint32_t pin, uint32_t mode, uint32_t dout);

#endif /* gpio_H */