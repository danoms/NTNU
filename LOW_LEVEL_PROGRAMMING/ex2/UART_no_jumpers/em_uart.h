/* control*/
#define IDLELOW			0
#define SAMPLELEADING 	0

#define SYNC(x) 		(x << 0)
#define CLOCKPOL(x) 	(x << 8)
#define CLKPHA(x) 		(x << 9)
#define MSBF(x) 		(x << 10)
#define AUTOTX(x) 		(x << 29)
#define AUTOCS(x) 		(x << 16)
#define LOOPBK(x)		(x << 1)

/* comand register */
#define RXPEN(x) 		(x << 0)
#define TXPEN(x) 		(x << 1)
#define CLKPEN(x) 		(x << 3)
#define LOCATION(x) 	(x << 8)
#define RXEN(x) 		(x << 0)
#define TXEN(x) 		(x << 2)
#define CSPEN(x)		(x << 2)
#define MASTERDIS(x) 	(x << 5)
#define MASTEREN(x) 	(x << 4)
#define TXDIS(x) 		(x << 3)
#define RXDIS(x) 		(x << 1)
#define CLEARRX(x) 		(x << 11)
#define CLEARTX(x) 		(x << 10)

/* interrupts */
#define RXDATAV(x) 		(x << 2)
#define TXC(x) 			(x << 0)
#define TXBL(x) 		(x << 1)
#define RXUF(x) 		(x << 5)

/*status mask*/
#define STATUS_RXFULL	(0x1UL << 8)
#define STATUS_RXDATAV	(0x1UL << 7)
#define STATUS_TXBL 	(0x1UL << 6)
#define STATUS_TXC 		(0x1UL << 5)


