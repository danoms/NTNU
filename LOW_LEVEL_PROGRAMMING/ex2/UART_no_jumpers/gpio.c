#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "em_gpio.h"
#include "uart_setup.h"

/*
 * function to set up GPIO mode and interrupts
 */

void setupGPIO(void)
{
	*CMU_HFPERCLKEN0 |= CMU_GPIO;	/* enable GPIO clock */
	
	GPIO_PA->CTRL |= 2;	/* set high drive strength */
	GPIO_PA->MODEH |= 0x55555555;	/* set pins A8-15 as output */
	GPIO_PA->DOUT |= 0xF000;	/* turn on LEDs D4-D8 (LEDs are active low) */

	/* Turn on GPIO buttons */
	// GPIO_PE->MODEL |= 0x33333333;	/* set pins C0-C7 as input */
	// GPIO_PE->DOUT |= 0xFF;	/* enable pull-up */

	// /* Enable interrupts */
	// GPIO->EXTIPSELL = 0x44444444;	/* Select port E */
	// GPIO->EXTIRISE = 0xFF;	 /*on rising edge, pins 0-7*/ 
	// GPIO->EXTIFALL = 0xFF;	/* on falling edge, pins 0-7 */
	// GPIO->IEN = 0xFF;	/* enable interrupts for pins 0-7 */
}

void setupGPIO_conf(GPIO_PORT_TypeDef *port, uint32_t pin, uint32_t mode, uint32_t high)
{
	/* if drive mode needed, write default drive strength */
	if (mode == PUSHPULLDRIVE) 
	{
		port->CTRL |= DRIVEMODE(HIGH);
	}

	/* write mode to MODE register */
	if (pin < 8)/* lower pins */
	{
		port->MODEL |= (mode << (pin * 4));
	} else {	/* high pins */
		port->MODEH |= (mode << ((pin-8)*4));
	}

	/* set or clear output*/
	if (high)
	{
		OUT_HIGH(port, pin);
	} else {
		OUT_LOW(port, pin);
	}
}