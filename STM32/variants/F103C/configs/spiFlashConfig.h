/* bsp_spiflash.h specific board spiflash config file, arduino have not autoload! */
#ifndef __SPIFLASHCONFIG_H__
#define __SPIFLASHCONFIG_H__

// W25Q64
#ifndef SPIFLASH_DEV
# define SPIFLASH_DEV	SPI1
#endif
#ifndef SPIFLASH_CS
# define SPIFLASH_CS	PA2
#endif
#ifndef SPIFLASH_SCK
# define SPIFLASH_SCK	PA5
#endif
#ifndef SPIFLASH_MISO
# define SPIFLASH_MISO	PA6
#endif
#ifndef SPIFLASH_MOSI
# define SPIFLASH_MOSI	PA7
#endif

#ifndef SPIFLASH_SPEED_Mhz
#define SPIFLASH_SPEED_Mhz 18
#endif

#endif   //__BSP_SPIFLASH_H__