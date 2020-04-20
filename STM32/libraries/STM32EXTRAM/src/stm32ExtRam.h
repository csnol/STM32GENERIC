#ifndef __STM32EXTSRAM_H
#define __STM32EXTSRAM_H

//#include <Arduino.h>
#if __has_include("bsp.h")
#include "bsp.h"
#endif

#ifdef SDRAM_START
#define EXTRAM_START     SDRAM_START
#define EXTRAM_LENGTH    SDRAM_LENGTH

#ifndef EXTRAM_Read_8b
extern SDRAM_HandleTypeDef sdramHandle;
#define EXTRAM_Handle    sdramHandle
#define EXTRAM_Read_8b(a,b,s)   HAL_SDRAM_Read_8b(&EXTRAM_Handle,(uint32_t *)((a) + EXTRAM_START),b,s)
#define EXTRAM_Read_16b(a,b,s)  HAL_SDRAM_Read_16b(&EXTRAM_Handle,(uint32_t *)((a) + EXTRAM_START),b,s)
#define EXTRAM_Read_32b(a,b,s)  HAL_SDRAM_Read_32b(&EXTRAM_Handle,(uint32_t *)((a) + EXTRAM_START),b,s)
#define EXTRAM_Write_8b(a,b,s)  HAL_SDRAM_Write_8b(&EXTRAM_Handle,(uint32_t *)((a) + EXTRAM_START),b,s)
#define EXTRAM_Write_16b(a,b,s) HAL_SDRAM_Write_16b(&EXTRAM_Handle,(uint32_t *)((a) + EXTRAM_START),b,s)
#define EXTRAM_Write_32b(a,b,s) HAL_SDRAM_Write_32b(&EXTRAM_Handle,(uint32_t *)((a) + EXTRAM_START),b,s)
#endif

#else
#define EXTRAM_START     SRAM_START
#define EXTRAM_LENGTH    SRAM_LENGTH

#ifndef EXTRAM_Read_8b

extern SRAM_HandleTypeDef  sramHandle;
#define EXTRAM_Handle    sramHandle
#define EXTRAM_Read_8b(a,b,s)   HAL_SRAM_Read_8b(&EXTRAM_Handle,(uint32_t *)((a) + EXTRAM_START),b,s)
#define EXTRAM_Read_16b(a,b,s)  HAL_SRAM_Read_16b(&EXTRAM_Handle,(uint32_t *)((a) + EXTRAM_START),b,s)
#define EXTRAM_Read_32b(a,b,s)  HAL_SRAM_Read_32b(&EXTRAM_Handle,(uint32_t *)((a) + EXTRAM_START),b,s)
#define EXTRAM_Write_8b(a,b,s)  HAL_SRAM_Write_8b(&EXTRAM_Handle,(uint32_t *)((a) + EXTRAM_START),b,s)
#define EXTRAM_Write_16b(a,b,s) HAL_SRAM_Write_16b(&EXTRAM_Handle,(uint32_t *)((a) + EXTRAM_START),b,s)
#define EXTRAM_Write_32b(a,b,s) HAL_SRAM_Write_32b(&EXTRAM_Handle,(uint32_t *)((a) + EXTRAM_START),b,s)
#endif
#endif

#define EXTRAM_END   (EXTRAM_START+EXTRAM_LENGTH)


#if SDRAM_START
#elif SRAM_START
#else
#error !!!undef SRAM_START or SDRAM_START!!!
#endif

class STM32EXTRAM
{
  private:
    STM32EXTRAM(void) {};

  public:
    static STM32EXTRAM& getInstance() {
      static STM32EXTRAM instance; // Guaranteed to be destroyed. Instantiated on first use.
      return instance;
    }

    STM32EXTRAM(STM32EXTRAM const&)    = delete;
    void operator=(STM32EXTRAM const&) = delete;

    inline uint8_t readData( uint32_t uwStartAddress, uint8_t *pData, uint32_t uwDataSize) const {
      return EXTRAM_Read_8b(uwStartAddress, pData, uwDataSize);
    };
    inline uint8_t readData( uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize) const {
      return EXTRAM_Read_16b(uwStartAddress, pData, uwDataSize);
    };
    inline uint8_t readData( uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize) const {
      return EXTRAM_Read_32b(uwStartAddress, pData, uwDataSize);
    };
    inline uint8_t writeData(uint32_t uwStartAddress, uint8_t *pData, uint32_t uwDataSize) const {
      return EXTRAM_Write_8b(uwStartAddress, pData, uwDataSize);
    };
    inline uint8_t writeData(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize) const {
      return EXTRAM_Write_16b(uwStartAddress, pData, uwDataSize);
    };

    inline uint8_t writeData(uint32_t uwStartAddress, uint32_t *pData, uint32_t uwDataSize) const {
      return EXTRAM_Write_32b(uwStartAddress, pData, uwDataSize);
    };

    inline uint32_t getRamBaseAddress() const {
      return EXTRAM_START;
    }

    inline uint32_t getRamByteLength() const {
      return EXTRAM_LENGTH;
    }
};

#endif /* __STM32EXTRAM_H */
