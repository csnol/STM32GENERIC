/* spiflashconfig.h specific board spiflash config file, arduino have not autoload! */
#ifndef __BSP_SPIFLASH_H__
#define __BSP_SPIFLASH_H__

#define SPIFLASH_TYPE W25Q16

#ifndef SPIFLASH_DEV
# define SPIFLASH_DEV	SPI3
#endif
#ifndef SPIFLASH_CS
# define SPIFLASH_CS	PB0
#endif
#ifndef SPIFLASH_SCK
# define SPIFLASH_SCK	PB3
#endif
#ifndef SPIFLASH_MISO
# define SPIFLASH_MISO	PB4
#endif
#ifndef SPIFLASH_MOSI
# define SPIFLASH_MOSI	PB5
#endif

#ifndef SPIFLASH_SPEED_Mhz
#define SPIFLASH_SPEED_Mhz 25
#endif

#endif   //__BSP_SPIFLASH_H__