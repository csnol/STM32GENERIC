/* bsp_spiflash.h specific board spiflash config file, arduino have not autoload! */
#ifndef __BSP_SPIFLASH_H__
#define __BSP_SPIFLASH_H__

#if defined(SERIALFLASH_USE_SPIx) && (SERIALFLASH_USE_SPIx == 1)
#ifndef SPIFLASH_DEV
# define SPIFLASH_DEV	SPI1
#endif
#ifndef SPIFLASH_CS
# define SPIFLASH_CS	PA4
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

#elif defined(SERIALFLASH_USE_SPIx) && (SERIALFLASH_USE_SPIx == 2)
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

#endif

#define SPIFLASH_SPEED_Mhz 20

#endif   //__BSP_SPIFLASH_H__