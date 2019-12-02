/* bsp_spiflash.h specific board spiflash config file, arduino have not autoload! */
#ifndef __BSP_SPIFLASH_H__
#define __BSP_SPIFLASH_H__

// W25Q64
#ifndef SPIFLASH_DEV
# define SPIFLASH_DEV	SPI2
#endif
#ifndef SPIFLASH_CS
# define SPIFLASH_CS	PB12
#endif
#ifndef SPIFLASH_SCK
# define SPIFLASH_SCK	PB13
#endif
#ifndef SPIFLASH_MISO
# define SPIFLASH_MISO	PB14
#endif
#ifndef SPIFLASH_MOSI
# define SPIFLASH_MOSI	PB15
#endif

#ifndef SPIFLASH_SPEED_Mhz
#define SPIFLASH_SPEED_Mhz 80
#endif

#endif   //__BSP_SPIFLASH_H__