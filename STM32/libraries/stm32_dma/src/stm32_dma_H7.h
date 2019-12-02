/*
  add H7 support by huaweiwx@sina.com 2018.7.25
*/

typedef struct {
    void *periphInstance;
    dmaRequest request;
    DMA_Stream_TypeDef *dmaInstance;
    DMAMUX_Channel_TypeDef* channel;
    uint8_t dmaHandlesIndex;
    uint8_t irqN;
} dma_request_to_instance_t;

const dma_request_to_instance_t dmaRequestToStream[] = {
    {SPI1, SPI_TX, DMA2_Stream3, DMAMUX1_Channel3, 3 + 8, DMA2_Stream3_IRQn},
    {SPI1, SPI_RX, DMA2_Stream0, DMAMUX1_Channel3, 0 + 8, DMA2_Stream0_IRQn},

    {SPI2, SPI_TX, DMA1_Stream4, DMAMUX1_Channel0, 4, DMA1_Stream4_IRQn},
    {SPI2, SPI_RX, DMA1_Stream3, DMAMUX1_Channel0, 3, DMA1_Stream3_IRQn},

#ifdef SPI3
    {SPI3, SPI_TX, DMA1_Stream5, DMAMUX1_Channel0, 5, DMA1_Stream5_IRQn},
    {SPI3, SPI_RX, DMA1_Stream0, DMAMUX1_Channel0, 0, DMA1_Stream0_IRQn},
#endif

#if defined(SDIO) && defined(SD_InitTypeDef)
    {SDIO, SDIO_RXTX, DMA2_Stream6, DMAMUX1_Channel4, 6 + 8, DMA2_Stream6_IRQn},
    {SDIO, SDIO_RXTX, DMA2_Stream3, DMAMUX1_Channel4, 3 + 8, DMA2_Stream3_IRQn},
#endif

#if defined(SDMMC1) && defined(SD_InitTypeDef)
    {SDMMC1, SDIO_RXTX, DMA2_Stream6, DMAMUX1_Channel4, 6 + 8, DMA2_Stream6_IRQn},
    {SDMMC1, SDIO_RXTX, DMA2_Stream3, DMAMUX1_Channel4, 3 + 8, DMA2_Stream3_IRQn},
#endif

#if defined(DAC1)
    {DAC1,   DAC1_CH1,  DMA1_Stream5, DMAMUX1_Channel5, 5,     DMA1_Stream5_IRQn},
    {DAC1,   DAC1_CH2,  DMA1_Stream6, DMAMUX1_Channel5, 6,     DMA1_Stream6_IRQn},
#endif

};

static inline void setDmaInstance(DMA_HandleTypeDef *handle, dma_request_to_instance_t dmaRequestToStream) {
    handle->Instance = dmaRequestToStream.dmaInstance;
}
