/* modes */
#define PUSHPULLDRIVE 		(0x5UL)
#define PUSHPULL			(0x4UL)
#define INPUTPULLFILTER		(0x3UL)
#define INPUTPULL 			(0x2UL)

/* control register*/
#define DRIVEMODE(x) 		(x << 0)

/* drive modes*/
#define HIGH 	2 /* 20 mA */

/* pins for modes */
#define MODE_PIN15(x)	(x << 28)
#define MODE_PIN13(x) 	(x << 20)
#define MODE_PIN10(x) 	(x << 8)
#define MODE_PIN9(x) 	(x << 4)
#define MODE_PIN5(x)	(x << 20)
#define MODE_PIN4(x) 	(x << 16)
#define MODE_PIN3(x) 	(x << 12)	
#define MODE_PIN2(x) 	(x << 12)

#define OUT_PIN(x) 		(1 << x)