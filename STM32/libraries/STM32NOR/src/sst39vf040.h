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

#ifndef __SST39VF040_H
#define __SST39VF040_H

#ifdef __cplusplus
 extern "C" {
#endif


/* I/O operation functions  ***************************************************/
HAL_StatusTypeDef _NOR_Read_ID(NOR_IDTypeDef *pNOR_ID);
HAL_StatusTypeDef _NOR_ReturnToReadMode(void);
HAL_StatusTypeDef _NOR_writeMode(void);
HAL_StatusTypeDef _NOR_ReadByte(uint32_t address, uint8_t *pData);
HAL_StatusTypeDef _NOR_Read(uint32_t address, uint16_t *pData);
HAL_StatusTypeDef _NOR_ProgramByte(uint32_t address, uint8_t *pData);
HAL_StatusTypeDef _NOR_Program( uint32_t address, uint16_t *pData);
HAL_StatusTypeDef _NOR_ReadByteBuffer(uint32_t uwAddress, uint8_t *pData, uint32_t uwBufferSize);
HAL_StatusTypeDef _NOR_ReadBuffer(uint32_t uwAddress, uint16_t *pData, uint32_t uwBufferSize);
HAL_StatusTypeDef _NOR_ProgramBuffer(uint32_t uwAddress, uint16_t *pData, uint32_t uwBufferSize);
HAL_StatusTypeDef _NOR_ProgramByteBuffer(uint32_t uwAddress, uint8_t *pData, uint32_t uwBufferSize);
HAL_StatusTypeDef _NOR_Erase_Block(uint32_t BlockAddress, uint32_t address);
HAL_StatusTypeDef _NOR_Erase_Chip(void);

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#define  NOR_Read_ID(a)               _NOR_Read_ID(a)
#define  NOR_ReturnToReadMode()       _NOR_ReturnToReadMode()
#define  NOR_writeMode()              _NOR_writeMode()
#define  NOR_ReadByte(a,b)            _NOR_ReadByte(a,b)
#define  NOR_Read(a,b)                _NOR_Read(a,b)
#define  NOR_ProgramByte(a,b)         _NOR_ProgramByte(a,b)
#define  NOR_Program(a,b)             _NOR_Program(a,b)
#define  NOR_ReadByteBuffer(a,b,c)    _NOR_ReadByteBuffer(a,b,c)
#define  NOR_ReadBuffer(a,b,c)        _NOR_ReadBuffer(a,b,c)
#define  NOR_ProgramBuffer(a,b,c)     _NOR_ProgramBuffer(a,b,c)
#define  NOR_ProgramByteBuffer(a,b,c) _NOR_ProgramByteBuffer(a,b,c)
#define  NOR_Erase_Block(a,b)         _NOR_Erase_Block(a,b)
#define  NOR_Erase_Chip()             _NOR_Erase_Chip()


#endif //__SST39VF040_H
