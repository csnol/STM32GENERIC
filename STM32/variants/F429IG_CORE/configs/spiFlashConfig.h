/* spiflashconfig.h specific board spiflash config file, arduino have not autoload! */
#ifndef __BSP_SPIFLASH_H__
#define __BSP_SPIFLASH_H__

#define SPIFLASH_TYPE   AT45DB161

#ifndef SPIFLASH_DEV
# define SPIFLASH_DEV	SPI5
#endif
#ifndef SPIFLASH_CS
# define SPIFLASH_CS	PF6
#endif
#ifndef SPIFLASH_SCK
# define SPIFLASH_SCK	PF7
#endif
#ifndef SPIFLASH_MISO
# define SPIFLASH_MISO	PF8
#endif
#ifndef SPIFLASH_MOSI
# define SPIFLASH_MOSI	PF9
#endif

#ifndef SPIFLASH_SPEED_Mhz
#define SPIFLASH_SPEED_Mhz 25
#endif


#endif   //__BSP_SPIFLASH_H__