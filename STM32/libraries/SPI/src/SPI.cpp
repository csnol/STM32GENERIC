#include "SPI.h"
#include "variant.h"
#include "stm32_dma.h"
#include "stm32_HAL/stm32XXxx_ll_spi.h"
#include "util/toolschain.h"

#if defined(MOSI) || defined(MISO) || defined(SCK)
SPIClass SPI(MOSI, MISO, SCK);
#else
SPIClass SPI(SPI1);
#endif

#if defined(SPI6)
#  define SPI_PORT_NR 6
#elif   defined(SPI5)
#  define SPI_PORT_NR 5
#elif   defined(SPI4)
#  define SPI_PORT_NR 4
#elif   defined(SPI3)
#  define SPI_PORT_NR 3
#elif   defined(SPI2)
#  define SPI_PORT_NR 2
#else
#  define SPI_PORT_NR 1
#endif

SPIClass    *spiClass[SPI_PORT_NR] = {NULL};

void SPIClass::Init(uint32_t mode) {

  apb_freq = stm32GetClockFrequency((void*)spiHandle.Instance);

  spiHandle.Init.Mode      =  mode;                /* default SPI_MODE_MASTER/[SPI_MODE_SLAVE] */
  spiHandle.Init.Direction =  SPI_DIRECTION_2LINES;
  spiHandle.Init.DataSize  =  SPI_DATASIZE_8BIT;
  if (mode == SPI_MODE_MASTER) {
    spiHandle.Init.NSS    =  (nssPin == 0xff) ? SPI_NSS_SOFT : SPI_NSS_HARD_OUTPUT; /* default SPI_NSS_SOFT/[SPI_NSS_HARD_INPUT/SPI_NSS_HARD_OUTPUT] */
  } else {  /* SPI_MODE_SLAVE */
    spiHandle.Init.NSS    = SPI_NSS_HARD_INPUT;  /* slave default SPI_NSS_HARD_INPUT */
  }


#if defined(SPI1)&& (USE_SPI1)
  if (spiHandle.Instance == SPI1) {
    __HAL_RCC_SPI1_CLK_ENABLE();
    usedCallback = 0;
    spiClass[0] = this;
  }
#endif
#if defined(SPI2)&& (USE_SPI2)
  else if (spiHandle.Instance == SPI2) {
    __HAL_RCC_SPI2_CLK_ENABLE();
    usedCallback = 1;
    spiClass[1] = this;
  }
#endif
#if defined(SPI3)&& (USE_SPI3)
  else if (spiHandle.Instance == SPI3) {
    __HAL_RCC_SPI3_CLK_ENABLE();
    usedCallback = 2;
    spiClass[2] = this;
  }
#endif
#if defined(SPI4)&& (USE_SPI4)
  else if (spiHandle.Instance ==  SPI4) {
    __HAL_RCC_SPI4_CLK_ENABLE();
    usedCallback = 3;
    spiClass[3] = this;
  }
#endif
#if defined(SPI5)&& (USE_SPI5)
  else if (spiHandle.Instance ==  SPI5) {
    __HAL_RCC_SPI5_CLK_ENABLE();
    usedCallback = 4;
    spiClass[4] = this;
  }
#endif
#if defined(SPI6)&& (USE_SPI6)
  else if (spiHandle.Instance ==  SPI6) {
    __HAL_RCC_SPI6_CLK_ENABLE();
    usedCallback = 5;
    spiClass[5] = this;
  }
#endif


  //////////////// DMA
  if (mode == SPI_MODE_MASTER) {
    __HAL_RCC_DMA1_CLK_ENABLE();
#ifdef __HAL_RCC_DMA2_CLK_ENABLE
    __HAL_RCC_DMA2_CLK_ENABLE();
#endif

    stm32DmaAcquire(&hdma_spi_tx, SPI_TX, spiHandle.Instance, true);
    stm32DmaAcquire(&hdma_spi_rx, SPI_RX, spiHandle.Instance, true);

    hdma_spi_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi_tx.Init.Mode = DMA_NORMAL;
    hdma_spi_tx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    _SPISetDMAFIFO(hdma_spi_tx);

    //hdma_spi_rx.Init.Channel = _ChannelRX;
    hdma_spi_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_spi_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_spi_rx.Init.Mode = DMA_NORMAL;
    hdma_spi_rx.Init.Priority = DMA_PRIORITY_VERY_HIGH;
    _SPISetDMAFIFO(hdma_spi_rx);

    __HAL_LINKDMA(&spiHandle, hdmatx, hdma_spi_tx);
    __HAL_LINKDMA(&spiHandle, hdmarx, hdma_spi_rx);
  }

  assert_param(IS_SPI_ALL_INSTANCE(spiHandle.Instance));

  if (mode == SPI_MODE_MASTER) { /* MASTER */
    stm32AfSPIInit(spiHandle.Instance,
                   variant_pin_list[mosiPin].port,
                   variant_pin_list[mosiPin].pinMask,
                   variant_pin_list[misoPin].port,
                   variant_pin_list[misoPin].pinMask,
                   variant_pin_list[sckPin].port,
                   variant_pin_list[sckPin].pinMask);
    if (spiHandle.Init.NSS == SPI_NSS_HARD_OUTPUT) /* default SPI_NSS_SOFT/[SPI_NSS_HARD_INPUT/SPI_NSS_HARD_OUTPUT] */
      stm32AfSPIInitMasterNss(spiHandle.Instance,
                              variant_pin_list[nssPin].port,
                              variant_pin_list[nssPin].pinMask);
  } else { /* SLAVE mode */
    stm32AfSPIInitSlave(spiHandle.Instance,
                        variant_pin_list[mosiPin].port,
                        variant_pin_list[mosiPin].pinMask,
                        variant_pin_list[misoPin].port,
                        variant_pin_list[misoPin].pinMask,
                        variant_pin_list[sckPin].port,
                        variant_pin_list[sckPin].pinMask,
                        variant_pin_list[nssPin].port,
                        variant_pin_list[nssPin].pinMask);
  }
}

void SPIClass::deInit() {
  //TODO deinit GPIO
  HAL_DMA_Init(&hdma_spi_tx);
  HAL_DMA_Init(&hdma_spi_rx);
}

void SPIClass::beginTransaction(void) {

  if (settings.clock >= apb_freq / 2) {
    spiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  } else if (settings.clock >= apb_freq / 4) {
    spiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  } else if (settings.clock >= apb_freq / 8) {
    spiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  } else if (settings.clock >= apb_freq / 16) {
    spiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  } else if (settings.clock >= apb_freq / 32) {
    spiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  } else if (settings.clock >= apb_freq / 64) {
    spiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  } else if (settings.clock >= apb_freq / 128) {
    spiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  }  else {
    spiHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_256;
  }

  if (settings.bitOrder == MSBFIRST) {
    spiHandle.Init.FirstBit = SPI_FIRSTBIT_MSB;
  } else {
    spiHandle.Init.FirstBit = SPI_FIRSTBIT_LSB;
  }

  if ((settings.dataMode == SPI_MODE0) || (settings.dataMode == SPI_MODE1)) {
    spiHandle.Init.CLKPolarity     = SPI_POLARITY_LOW;
  } else {
    spiHandle.Init.CLKPolarity     = SPI_POLARITY_HIGH;
  }

  if ((settings.dataMode == SPI_MODE0) || (settings.dataMode == SPI_MODE2)) {
    spiHandle.Init.CLKPhase        = SPI_PHASE_1EDGE;
  } else {
    spiHandle.Init.CLKPhase        = SPI_PHASE_2EDGE;
  }

  spiHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  spiHandle.Init.CRCPolynomial     = 7;

  spiHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
#if defined(STM32F0) || defined(GD32F1x0)|| defined(STM32F3) || defined(STM32F7) ||\
    defined(STM32G0) || defined(STM32H7) || defined(STM32L4) ||\
    defined(STM32WB) || defined(STM32MP1)
  spiHandle.Init.NSSPMode          = SPI_NSS_PULSE_DISABLE;
  spiHandle.Init.CRCLength         = SPI_CRC_LENGTH_8BIT;
#endif

  HAL_SPI_Init(&spiHandle);
  __HAL_SPI_ENABLE(&spiHandle);
}

HAL_StatusTypeDef SPIClass::setPins(uint8_t mosi, uint8_t miso, uint8_t sck, uint8_t nss) {
  mosiPin = mosi;
  misoPin = miso;
  sckPin  = sck;
  nssPin  = nss;
  spiHandle.Instance = stm32GetSPIInstance(
                         variant_pin_list[mosi].port,
                         variant_pin_list[mosi].pinMask,
                         variant_pin_list[miso].port,
                         variant_pin_list[miso].pinMask,
                         variant_pin_list[sck].port,
                         variant_pin_list[sck].pinMask);
  assert_param(IS_SPI_ALL_INSTANCE(spiHandle.Instance));
  if (spiHandle.Instance) return HAL_OK;
  return HAL_ERROR;
};


/** Returns true on success, false on failure
 * */
bool SPIClass::transfer(uint8_t *txBuffer, uint8_t *rxBuffer, size_t count, spi_callback_type callback) {
  this->callback = callback;

  //Some series (F1, L0) will ignore MemInc setting if the DMA is still enabled
  __HAL_DMA_DISABLE(&hdma_spi_tx);
  __HAL_DMA_DISABLE(&hdma_spi_rx);

  if (txBuffer != NULL) {
    hdma_spi_tx.Init.MemInc = DMA_MINC_ENABLE;
  } else {
    txBuffer = (uint8_t*)&repeatTransmitData;
    hdma_spi_tx.Init.MemInc = DMA_MINC_DISABLE;
  }

  if (rxBuffer != NULL) {

    if (HAL_DMA_Init(&hdma_spi_tx) != HAL_OK) {
      return false;
    }

    if (HAL_DMA_Init(&hdma_spi_rx) != HAL_OK) {
      return false;
    }

    dmaDone = false;
    if (HAL_SPI_TransmitReceive_DMA(&spiHandle, txBuffer, rxBuffer, count) != HAL_OK) {
      return false;
    }
  } else {
    if (HAL_DMA_Init(&hdma_spi_tx) != HAL_OK) {
      return false;
    }

    dmaDone = false;
    if (HAL_SPI_Transmit_DMA(&spiHandle, txBuffer, count) != HAL_OK) {
      return false;
    }
  }
  return true;
}

void SPIClass::flush(void) {
  while (!done()) {
    yield();
  }
}
bool SPIClass::done(void) {
  return dmaDone;
}

/** Returns 0 on success, 1 on failure
 * */
uint8_t SPIClass::dmaTransfer(uint8_t *transmitBuf, uint8_t *receiveBuf, uint16_t length) {
  return !transfer(transmitBuf, receiveBuf, length);
}

/** Returns 0 on success, 1 on failure
 * */
uint8_t SPIClass::dmaSend(uint8_t *transmitBuf, uint16_t length, bool minc) {
  if (minc) {
    return !transfer(transmitBuf, NULL, length);
  } else {
    repeatTransmitData = transmitBuf[0];
    return !transfer((uint8_t*)NULL, NULL, length);
  }
}

static SPIClass* getobj(SPI_HandleTypeDef *hspi) {
  for (int i = 0; i < SPI_PORT_NR; i++) {
    if (spiClass[i]) {
      if (spiClass[i]->spiHandle.Instance == hspi->Instance)
        return spiClass[i];
    }
  }
  return NULL;
}

static void stm32SpiDmaFinished(SPI_HandleTypeDef *hspi) {
  SPIClass* obj = getobj(hspi);
  if (obj) {
    obj->repeatTransmitData = 0xFFFF;

    if (obj->callback != NULL) {
      obj->callback();
    }
    obj->setDataWidth16(false);
    obj->dmaDone = true;
  }
}

extern "C" void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi) {
  stm32SpiDmaFinished(hspi);
}

extern "C" void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi) {
  stm32SpiDmaFinished(hspi);
}
/*
extern "C" void SPI1_IRQHandler(void) {
  HAL_SPI_IRQHandler(&spiClass[0]->spiHandle);
}
*/