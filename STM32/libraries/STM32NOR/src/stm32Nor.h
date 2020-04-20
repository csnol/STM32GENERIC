/*
  Copyright (c) 2018 huaweiwx@sina.com 2018.11.1

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#ifndef __STM32NOR_H
#define __STM32NOR_H

#include "BSP.h"
#include "sst39vf040.h"

#ifdef __cplusplus
 extern "C" {
#endif 


#define   NOR_STATUS_OK         0x00
#define   NOR_STATUS_ERROR      0x01


#ifndef FSMC_NORSRAM_MEM_BUS_WIDTH
#define FSMC_NORSRAM_MEM_BUS_WIDTH    FSMC_NORSRAM_MEM_BUS_WIDTH_16
#endif

#define NOR_BURSTACCESS     FSMC_BURST_ACCESS_MODE_DISABLE  
  
#define NOR_WRITEBURST    FSMC_WRITE_BURST_DISABLE  
 
/* NOR operations Timeout definitions */
#define BLOCKERASE_TIMEOUT   ((uint32_t)0x00A00000)  /* NOR block erase timeout */
#define CHIPERASE_TIMEOUT    ((uint32_t)0x30000000)  /* NOR chip erase timeout  */ 
#define PROGRAM_TIMEOUT      ((uint32_t)0x00004400)  /* NOR program timeout     */ 

/* NOR Ready/Busy signal GPIO definitions */
#define NOR_READY_BUSY_PIN    GPIO_PIN_6 
#define NOR_READY_BUSY_GPIO   GPIOD
#define NOR_READY_STATE       GPIO_PIN_SET
#define NOR_BUSY_STATE        GPIO_PIN_RESET 

#ifndef  NOR_Read_ID
#define  NOR_Read_ID(a)               HAL_NOR_Read_ID(&norHandle,a)
#endif
#ifndef  NOR_ReturnToReadMode
#define  NOR_ReturnToReadMode()       HAL_NOR_ReturnToReadMode(&norHandle)
#endif
#ifndef  NOR_Read
#define  NOR_Read(a,b)                HAL_NOR_Read(&norHandle, (uint32_t *)(a+NOR_DEVICE_ADDR), b)
#endif
#ifndef  NOR_Program
#define  NOR_Program(a,b)             HAL_NOR_Program(&norHandle, (uint32_t *)(a+NOR_DEVICE_ADDR), b)
#endif
#ifndef  NOR_ReadBuffer
#define  NOR_ReadBuffer(a,b,c)        HAL_NOR_ReadBuffer(&norHandle, (uint32_t *)(a+NOR_DEVICE_ADDR),b,c)
#endif
#ifndef  NOR_ProgramBuffer
#define  NOR_ProgramBuffer(a,b,c)     HAL_NOR_ProgramBuffer(&norHandle, a + NOR_DEVICE_ADDR, b, c)
#endif
#ifndef  NOR_Erase_Block
#define  NOR_Erase_Block(a,b)         HAL_NOR_Erase_Block(&norHandle, a,b)
#endif
#ifndef  NOR_Erase_Chip
#define  NOR_Erase_Chip()             HAL_NOR_Erase_Chip(&norHandle,0)
#endif


#ifdef __cplusplus
}

extern NOR_HandleTypeDef norHandle;
class STM32NOR
{
  private:   
    STM32NOR(void){};

  public:
    static STM32NOR& getInstance() {
       static STM32NOR instance; // Guaranteed to be destroyed. Instantiated on first use.
       return instance;
    }
    inline void Init(void){
		STM_FSMC_NOR_Init();
	}
	
    inline HAL_StatusTypeDef readID(NOR_IDTypeDef *pNOR_ID) const {
    	return NOR_Read_ID(pNOR_ID);
    };
    inline HAL_StatusTypeDef returnToReadMode(void) const {
    	return NOR_ReturnToReadMode();
    };

#ifdef NOR_writeMod
     inline HAL_StatusTypeDef writeMode(void) const {
    	return NOR_writeMode();
    };
#endif

#ifdef NOR_ReadByte
    inline HAL_StatusTypeDef readData(uint32_t uwStartAddress, uint8_t *pData) const {
    	return NOR_ReadByte(uwStartAddress, pData);
    };
#endif
    inline HAL_StatusTypeDef readData(uint32_t uwStartAddress, uint16_t *pData) const {
    	return NOR_Read(uwStartAddress, pData);
    };
	
#ifdef NOR_ProgramByte
    inline HAL_StatusTypeDef writeData(uint32_t uwStartAddress, uint8_t *pData) const {
    	return NOR_ProgramByte(uwStartAddress, pData);
    };
#endif
	
    inline HAL_StatusTypeDef writeData(uint32_t uwStartAddress, uint16_t *pData) const {
    	return NOR_Program(uwStartAddress, pData);
    };
	
#ifdef NOR_ReadByteBuffer
    inline HAL_StatusTypeDef readDataBuf(uint32_t uwStartAddress, uint8_t *pData,int32_t uwDataSize) const {
    	return NOR_ReadByteBuffer(uwStartAddress, pData,uwDataSize);
    };
#endif
    inline HAL_StatusTypeDef readDataBuf(uint32_t uwStartAddress, uint16_t *pData,int32_t uwDataSize) const {
    	return NOR_ReadBuffer(uwStartAddress, pData,uwDataSize);
    };

#ifdef NOR_ProgramByteBuffer
    inline HAL_StatusTypeDef writeDataBuf(uint32_t uwStartAddress, uint8_t *pData, uint32_t uwDataSize) const {
    	return NOR_ProgramByteBuffer(uwStartAddress, pData, uwDataSize);
    }
#endif

    inline HAL_StatusTypeDef writeDataBuf(uint32_t uwStartAddress, uint16_t *pData, uint32_t uwDataSize) const {
    	return NOR_ProgramBuffer(uwStartAddress, pData, uwDataSize);
    }
    inline HAL_StatusTypeDef eraseBlock(uint32_t BlockAddress,uint32_t Address) const {
    	return NOR_Erase_Block(BlockAddress,Address);
      }
    inline HAL_StatusTypeDef eraseChip(void) const {
    	return NOR_Erase_Chip();
    };
    
      inline uint32_t getNorAddr(void) const {
    	return NOR_DEVICE_ADDR;
    }
      inline uint32_t getNorLength(void) const {
    	return NOR_DEVICE_LENGTH;
    }
};

#endif

#endif /* __STM32NOR_H */
