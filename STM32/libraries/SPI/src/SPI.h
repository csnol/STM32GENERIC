#ifndef _SPI_H_INCLUDED
#define _SPI_H_INCLUDED

#include <Arduino.h>
#include "stm32_gpio_af.h"

#include "stm32_HAL/stm32XXxx_ll_spi.h"

#if defined(STM32F1) ||defined(GD32F10X)||defined(GD32F20X) || defined(STM32F4)
#define SPI_HAS_OLD_DMATRANSFER
#endif

// SPI_HAS_EXTENDED_TRANSFER means SPI has
//   - transfer(uint8_t data, uint8_t *rxBuffer, size_t count)
//   - transfer(uint8_t *txBuffer, uint8_t *rxBuffer, size_t count)
#define SPI_HAS_EXTENDED_TRANSFER

// SPI_HAS_EXTENDED_NONBLOCKING_TRANSFER means SPI has
//   - implies SPI_HAS_EXTENDED_TRANSFER
//   - transfer(uint8_t data, uint8_t *rxBuffer, size_t count, callback)
//   - transfer(uint8_t *txBuffer, uint8_t *rxBuffer, size_t count, callback)
#define SPI_HAS_EXTENDED_NONBLOCKING_TRANSFER

// SPI_HAS_TRANSACTION means SPI has
//   - beginTransaction()
//   - endTransaction()
//   - usingInterrupt()
//   - SPISetting(clock, bitOrder, dataMode)
#define SPI_HAS_TRANSACTION 1

// SPI_HAS_EXTENDED_CS_PIN_HANDLING means SPI has automatic
// CS pin handling and provides the following methods:
//   - begin(pin)
//   - end(pin)
//   - setBitOrder(pin, bitorder)
//   - setDataMode(pin, datamode)
//   - setClockDivider(pin, clockdiv)
//   - transfer(pin, data, SPI_LAST/SPI_CONTINUE)
//   - beginTransaction(pin, SPISettings settings) (if transactions are available)
// #define SPI_HAS_EXTENDED_CS_PIN_HANDLING 1

// For compatibility with sketches designed for AVR @ 16 MHz
// need to go from 64MHz to 16 (/4)
// New programs should use SPI.beginTransaction to set the SPI clock
#define SPI_CLOCK_DIV2	 2
#define SPI_CLOCK_DIV4	 4
#define SPI_CLOCK_DIV8	 8
#define SPI_CLOCK_DIV16	 16
#define SPI_CLOCK_DIV32	 32
#define SPI_CLOCK_DIV64	 64
#define SPI_CLOCK_DIV128 128

#define SPI_MODE0 0x00  /*clock polarity (CPOL) /The clock phase (CPHA) 00 */
#define SPI_MODE1 0x01  /*                                              01 */
#define SPI_MODE2 0x02  /*                                              10 */
#define SPI_MODE3 0x03  /*                                              11 */

#if defined(STM32F4) || defined(STM32F7)||defined(STM32H7)
	#define _SPISetDMAFIFO(hdma_handler)	do { hdma_handler.Init.FIFOMode = DMA_FIFOMODE_DISABLE; \
								hdma_handler.Init.FIFOMode = DMA_FIFOMODE_ENABLE; \
								hdma_handler.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL; \
								hdma_handler.Init.MemBurst = DMA_MBURST_SINGLE; \
								hdma_handler.Init.PeriphBurst = DMA_PBURST_SINGLE; } while (0)

#else
    #define _SPISetDMAFIFO(hdma_handler)
#endif


class SPISettings {
  public:
    SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode): clock(clock), bitOrder(bitOrder), dataMode(dataMode) {};
    SPISettings(): clock(0), bitOrder(0), dataMode(0) {};
    //init(4000000, MSBFIRST, SPI_MODE0);

    uint32_t clock;
    uint8_t bitOrder;
    uint8_t dataMode;
};

typedef void (*spi_callback_type)();

class SPIClass {
  public:
    SPIClass(){};
	
    SPIClass(SPI_TypeDef *instance){spiHandle.Instance=instance;}

    SPIClass(SPI_TypeDef *instance, uint8_t mosi, uint8_t miso, uint8_t sck):
            mosiPin(mosi),misoPin(miso),sckPin(sck){spiHandle.Instance=instance;}

    SPIClass(uint8_t mosi, uint8_t miso, uint8_t sck) {
        setPins(mosi,miso,sck);
    }

    inline void stm32SetInstance(SPI_TypeDef *instance) {spiHandle.Instance = instance;}
    inline void stm32SetMOSI(uint8_t mosi) {mosiPin = mosi;}
    inline void stm32SetMISO(uint8_t miso) {misoPin = miso;}
    inline void stm32SetSCK(uint8_t sck){sckPin = sck;}
    inline void stm32SetNSS(uint8_t nss){nssPin = nss;}

	HAL_StatusTypeDef setPins(uint8_t mosi,uint8_t miso,uint8_t sck,uint8_t nss = 0xff);
    void Init(uint32_t mode = SPI_MODE_MASTER);

	void deInit();
	
#if USE_ITERATOR == 0  /*for stl begin/end is keywords for iteration*/
    void begin(){Init();}
	void end(){deInit();}
#endif

    void beginTransaction(void);
	 
    inline void beginTransaction(SPISettings settings) {
      if (this->settings.clock == settings.clock
          && this->settings.bitOrder == settings.bitOrder
          && this->settings.dataMode == settings.dataMode) {
        return;
      }
      this->settings = settings;
	  beginTransaction();
    }
	
	void endTransaction(){}

	inline void setBitOrder(uint8_t bitOrder) {
	  beginTransaction(SPISettings(settings.clock, bitOrder, settings.dataMode));
    }
	inline void setDataMode(uint8_t dataMode) {
	  beginTransaction(SPISettings(settings.clock, settings.bitOrder, dataMode));
    }
	inline void setClockDivider(uint8_t clockDevider) {
	  beginTransaction(SPISettings(apb_freq / clockDevider, settings.bitOrder, settings.dataMode));
    }

    uint8_t transfer(uint8_t data);
    uint16_t transfer16(uint16_t data);
    void transfer(uint8_t *buf, size_t count);

    void setDataWidth16(bool width16) {
        if (width16) {
            LL_SPI_SetDataWidth(spiHandle.Instance, LL_SPI_DATAWIDTH_16BIT);

            hdma_spi_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
            hdma_spi_rx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;

            hdma_spi_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
            hdma_spi_tx.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;

        } else if (LL_SPI_GetDataWidth(spiHandle.Instance) == LL_SPI_DATAWIDTH_16BIT) {
            LL_SPI_SetDataWidth(spiHandle.Instance, LL_SPI_DATAWIDTH_8BIT);

            hdma_spi_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
            hdma_spi_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;

            hdma_spi_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
            hdma_spi_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        }
    }


    bool transfer(uint8_t data, uint8_t *rxBuffer, size_t count) {
        repeatTransmitData = data;
        if (transfer((uint8_t*) NULL, rxBuffer, count, NULL)) {
            flush();
            return true;
        }
        return false;
    }
    bool transfer(uint8_t *txBuffer, uint8_t *rxBuffer, size_t count) {
        if (transfer(txBuffer, rxBuffer, count, NULL)) {
            flush();
            return true;
        }
        return false;
    }
    bool transfer(uint8_t data, uint8_t *rxBuffer, size_t count, spi_callback_type callback) {
        repeatTransmitData = data;
        return transfer((uint8_t*) NULL, rxBuffer, count, callback);
    }
    bool transfer(uint8_t *txBuffer, uint8_t *rxBuffer, size_t count, spi_callback_type callback);


    bool transfer16(uint16_t data, uint16_t *rxBuffer, size_t count) {
        setDataWidth16(true);

        repeatTransmitData = data;

        return transfer((uint8_t*)NULL, (uint8_t*)rxBuffer, count);
    }
    bool transfer16(uint16_t *txBuffer, uint16_t *rxBuffer, size_t count) {
        setDataWidth16(true);

        return transfer((uint8_t*)txBuffer, (uint8_t *)rxBuffer, count);
    }
    bool transfer16(uint16_t data, uint16_t *rxBuffer, size_t count, spi_callback_type callback) {
        setDataWidth16(true);

        repeatTransmitData = data;
        return transfer((uint8_t*) NULL, (uint8_t*)rxBuffer, count, callback);
    }
    bool transfer16(uint16_t *txBuffer, uint16_t *rxBuffer, size_t count, spi_callback_type callback) {
        setDataWidth16(true);

        return transfer((uint8_t*)txBuffer, (uint8_t*)rxBuffer, count, callback);
    }

    void flush(void);
    bool done(void);

	uint8_t __attribute__ ((deprecated)) dmaTransfer(uint8_t *transmitBuf, uint8_t *receiveBuf, uint16_t length);
	uint8_t __attribute__ ((deprecated)) dmaSend(uint8_t *transmitBuf, uint16_t length, bool minc = 1);


/**
  * @brief  Not implemented.
  */
    void usingInterrupt(uint8_t interruptNumber){ UNUSED(interruptNumber);}
/**
  * @brief  Not implemented.
  */
    void attachInterrupt(void){/* Should be enableInterrupt()*/ }

/**
  * @brief  Not implemented.
  */
    void detachInterrupt(void){/* Should be disableInterrupt()*/}

    SPI_HandleTypeDef spiHandle = {};

    uint16_t repeatTransmitData = 0XFFFF;
    spi_callback_type callback;

    volatile bool dmaDone = true;

  private:
    uint32_t apb_freq = 0;

    SPISettings settings = {
      .clock = 4'000'000,
      .bitOrder = MSBFIRST,
      .dataMode = SPI_MODE0,
	};

    DMA_HandleTypeDef hdma_spi_rx = {};
    DMA_HandleTypeDef hdma_spi_tx = {};
	
    uint8_t mosiPin = 0xff;
    uint8_t misoPin = 0xff;
    uint8_t sckPin  = 0xff;
    uint8_t nssPin  = 0xff;
	
    uint8_t usedCallback;
};


inline uint8_t SPIClass::transfer(uint8_t data) {
#if 0	
    while(__HAL_SPI_GET_FLAG(&spiHandle, SPI_FLAG_TXE) == RESET){};

#if defined(STM32H7)
    *(volatile uint16_t*)&spiHandle.Instance->TXDR = data;
//	while(__HAL_SPI_GET_FLAG(&spiHandle, SPI_FLAG_RXNE) == RESET){};
//	while(__HAL_SPI_GET_FLAG(&spiHandle, SPI_FLAG_BSY) == SET){};
#else
    *(volatile uint16_t*)&spiHandle.Instance->DR = data;
	while(__HAL_SPI_GET_FLAG(&spiHandle, SPI_FLAG_RXNE) == RESET){};
	while(__HAL_SPI_GET_FLAG(&spiHandle, SPI_FLAG_BSY) == SET){};
#endif


#if defined(STM32H7)
    return *(volatile uint16_t*)&spiHandle.Instance->TXDR = data;
#else
    return *(volatile uint16_t*)&spiHandle.Instance->DR = data;
#endif

#else
	uint8_t ret = data;
	HAL_SPI_TransmitReceive(&spiHandle, &ret,&ret, 1, 1000);
	return ret;
#endif
}

#if defined ( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

inline uint16_t SPIClass::transfer16(uint16_t data) {
    LL_SPI_SetDataWidth(spiHandle.Instance, LL_SPI_DATAWIDTH_16BIT);
	
#if 0
    while(__HAL_SPI_GET_FLAG(&spiHandle, SPI_FLAG_TXE) == RESET){};
#if defined(STM32H7)
    *(volatile uint16_t*)&spiHandle.Instance->TXDR = data;
//    while(__HAL_SPI_GET_FLAG(&spiHandle, SPI_FLAG_RXNE) == RESET){};
//    while(__HAL_SPI_GET_FLAG(&spiHandle, SPI_FLAG_BSY) == SET){};
#else
    *(volatile uint16_t*)&spiHandle.Instance->DR = data;
    while(__HAL_SPI_GET_FLAG(&spiHandle, SPI_FLAG_RXNE) == RESET){};
    while(__HAL_SPI_GET_FLAG(&spiHandle, SPI_FLAG_BSY) == SET){};
#endif
#if defined(STM32H7)
    uint16_t ret = *(volatile uint16_t*)&spiHandle.Instance->RXDR;
#else
    uint16_t ret = *(volatile uint16_t*)&spiHandle.Instance->DR;
#endif
#else
	uint16_t ret = data;
	HAL_SPI_TransmitReceive(&spiHandle, (uint8_t *)&ret,(uint8_t *)&ret, sizeof(uint16_t), 1000);
#endif

    LL_SPI_SetDataWidth(spiHandle.Instance, LL_SPI_DATAWIDTH_8BIT);
    return ret;
}
#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif

inline void SPIClass::transfer(uint8_t *buf, size_t count) {
	HAL_SPI_TransmitReceive(&spiHandle, buf, buf, count, 1000);
}

extern SPIClass SPI;
#if  USE_SOFTWARE_SPI
  #include "SpiSoft.h"
#endif

#endif
