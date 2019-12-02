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

/* Includes ------------------------------------------------------------------*/
#include "arduino.h"

#if __has_include("bsp.h")
 #include "bsp.h"
 #include "sst39vf040.h"
#endif

#if defined(SST39VF040)||defined(SST39VF020)||defined(SST39SF040)||defined(SST39SF020)

/* Support flashes:
 *
 * SST39VF020: 4KB * 64 = 256KB
 * SST39SF020: 4KB * 64 = 256KB
 * SST39VF040: 4KB * 128 = 512KB
 * SST39SF040: 4KB * 128 = 512KB
 */

/* Constants to define address to set to write a command */
#define NOR_CMD_ADDRESS_FIRST                 (uint16_t)0x5555
#define NOR_CMD_ADDRESS_SECOND                (uint16_t)0x2AAA
#define NOR_CMD_ADDRESS_THIRD                 (uint16_t)0x5555
#define NOR_CMD_ADDRESS_FOURTH                (uint16_t)0x5555
#define NOR_CMD_ADDRESS_FIFTH                 (uint16_t)0x2AAA
#define NOR_CMD_ADDRESS_SIXTH                 (uint16_t)0x5555

/* Constants to define data to program a command */
#define NOR_CMD_DATA_READ_RESET               (uint16_t)0x00F0
#define NOR_CMD_DATA_FIRST                    (uint16_t)0x00AA
#define NOR_CMD_DATA_SECOND                   (uint16_t)0x0055
#define NOR_CMD_DATA_AUTO_SELECT              (uint16_t)0x0090
#define NOR_CMD_DATA_PROGRAM                  (uint16_t)0x00A0
#define NOR_CMD_DATA_CHIP_BLOCK_ERASE_THIRD   (uint16_t)0x0080
#define NOR_CMD_DATA_CHIP_BLOCK_ERASE_FOURTH  (uint16_t)0x00AA
#define NOR_CMD_DATA_CHIP_BLOCK_ERASE_FIFTH   (uint16_t)0x0055
#define NOR_CMD_DATA_CHIP_ERASE               (uint16_t)0x0010

#define NOR_CMD_DATA_BLOCK_ERASE              (uint8_t)0x30

#define NOR_ADDR_SHIFT8(__NOR_ADDRESS, __ADDRESS__)   ((uint32_t)((__NOR_ADDRESS) + (__ADDRESS__)))

#define NOR_WRITE8(__ADDRESS__, __DATA__)  (*(__IO uint8_t *)((uint32_t)(__ADDRESS__)) = (__DATA__))

/**
  * @brief  Read NOR flash IDs
  * @param  pNOR_ID : pointer to NOR ID structure
  * @retval HAL status
  */
  
extern  NOR_HandleTypeDef norHandle;
  
HAL_StatusTypeDef  _NOR_Read_ID(NOR_IDTypeDef *pNOR_ID)
{
  NOR_HandleTypeDef *hnor = &norHandle;
  
  /* Process Locked */
  __HAL_LOCK(hnor);
  
  /* Check the NOR controller state */
  if(hnor->State == HAL_NOR_STATE_BUSY)
  {
     return HAL_BUSY;
  }
  
  /* Update the NOR controller state */
  hnor->State = HAL_NOR_STATE_BUSY;
  
  /* Send read ID command */
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_FIRST), NOR_CMD_DATA_FIRST);
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_SECOND), NOR_CMD_DATA_SECOND);
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_THIRD), NOR_CMD_DATA_AUTO_SELECT);

  /* Read the NOR IDs */
  pNOR_ID->Manufacturer_Code = *(__IO uint8_t *) NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, MC_ADDRESS);
  pNOR_ID->Device_Code1      = *(__IO uint8_t *) NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, DEVICE_CODE1_ADDR);
  pNOR_ID->Device_Code2      = 0 ;
  pNOR_ID->Device_Code3      = 0 ;

  /* Send read command */
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_FIRST), NOR_CMD_DATA_FIRST);
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_SECOND), NOR_CMD_DATA_SECOND);
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_THIRD), NOR_CMD_DATA_READ_RESET);

  /* Check the NOR controller state */
  hnor->State = HAL_NOR_STATE_READY;
  
  /* Process unlocked */
  __HAL_UNLOCK(hnor);   
  
  return HAL_OK;
}


/**
  * @brief  Read data from NOR memory 
  * @param  uwAddress: Device address
  * @param  pData : pointer to read data  
  * @retval HAL status
  */
HAL_StatusTypeDef _NOR_ReadByte(uint32_t uwAddress, uint8_t *pData)
{
  /* Read the data */
  *pData = *(__IO uint8_t *)(uwAddress + NOR_DEVICE_ADDR);

  return HAL_OK;  
}
HAL_StatusTypeDef _NOR_Read(uint32_t uwAddress, uint16_t *pData)
{
  /* Read the data */
  *pData = *(__IO uint16_t *)(uwAddress+NOR_DEVICE_ADDR);

  return HAL_OK;  
}

HAL_StatusTypeDef _NOR_ReturnToReadMode(void)
{
  /* Send read command */
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_FIRST), NOR_CMD_DATA_FIRST);
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_SECOND), NOR_CMD_DATA_SECOND);
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_THIRD), NOR_CMD_DATA_READ_RESET);
 
  return HAL_OK;  
}
HAL_StatusTypeDef _NOR_writeMode(void)
{
  /* Send program data command */
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_FIRST), NOR_CMD_DATA_FIRST);
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_SECOND), NOR_CMD_DATA_SECOND);
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_THIRD), NOR_CMD_DATA_PROGRAM);

  return HAL_OK;  
}

/**
  * @brief  Program data to NOR memory 
  * @param  uwAddress: Device uwAddress
  * @param  pData : pointer to the data to write   
  * @retval HAL status
  */
HAL_StatusTypeDef _NOR_ProgramByte(uint32_t uwAddress, uint8_t *pData)
{
  NOR_HandleTypeDef *hnor = &norHandle;
  
  /* Process Locked */
  __HAL_LOCK(hnor);
  
  /* Check the NOR controller state */
  if(hnor->State == HAL_NOR_STATE_BUSY)
  {
     return HAL_BUSY;
  }
    
  /* Update the NOR controller state */
  hnor->State = HAL_NOR_STATE_BUSY;
  
  /* Send program data command */
  _NOR_writeMode();
  /* Write the data */
  *((uint8_t *)(NOR_DEVICE_ADDR + uwAddress))  = *pData;
  
  /* Check the NOR controller state */
  hnor->State = HAL_NOR_STATE_READY;
  
  /* Process unlocked */
  __HAL_UNLOCK(hnor);
  
  return HAL_OK;  
}

/**
  * @brief  Program data to NOR memory 
  * @param  uwAddress: Device address
  * @param  pData : pointer to the data to write   
  * @retval HAL status
  */

HAL_StatusTypeDef _NOR_Program(uint32_t uwAddress, uint16_t *pData)
{
   uint8_t *pByte = (uint8_t *)pData;
  _NOR_ProgramByte(uwAddress++, pByte++);
  _NOR_ProgramByte(uwAddress,pByte);  
  return HAL_OK;  
}

HAL_StatusTypeDef _NOR_ReadByteBuffer(uint32_t uwAddress, uint8_t *pData, uint32_t uwBufferSize)
{
 
  /* Read buffer */
  while( uwBufferSize > 0U)
  {
    *pData++ = *(__IO uint8_t *)(uwAddress + NOR_DEVICE_ADDR);
    uwAddress ++;
    uwBufferSize--;
  } 

  return HAL_OK;  
}

HAL_StatusTypeDef _NOR_ReadBuffer(uint32_t uwAddress, uint16_t *pData, uint32_t uwBufferSize)
{
  /* Read buffer */
  while( uwBufferSize > 0U)
  {
    *pData++ = *(__IO uint16_t *)(uwAddress + NOR_DEVICE_ADDR);
    uwAddress    += 2U;
    uwBufferSize -= 2;
  } 
 
  return HAL_OK;  
}

HAL_StatusTypeDef _NOR_ProgramByteBuffer(uint32_t uwAddress, uint8_t *pData, uint32_t uwBufferSize)
{
  while(uwBufferSize >0)
  {
     _NOR_ProgramByte(uwAddress++, pData++);
	 uwBufferSize--;
  }  
    return HAL_OK; 
}

HAL_StatusTypeDef _NOR_ProgramBuffer(uint32_t uwAddress, uint16_t *pData, uint32_t uwBufferSize)
{
  uint8_t *pByte = (uint8_t *)pData;
  while(uwBufferSize >0)
  {
     _NOR_ProgramByte(uwAddress++, pByte++);
     _NOR_ProgramByte(uwAddress++, pByte++);
     uwBufferSize -=2;
  }  
  
  return HAL_OK; 
  
}

/**
  * @brief  Erase the specified block of the NOR memory 
  * @param  BlockAddress : Block to erase address 
  * @param  Address: Device address
  * @retval HAL status
  */
HAL_StatusTypeDef _NOR_Erase_Block(uint32_t BlockAddress, uint32_t Address)
{
  NOR_HandleTypeDef *hnor = &norHandle;

  /* Process Locked */
  __HAL_LOCK(hnor);
  
  /* Check the NOR controller state */
  if(hnor->State == HAL_NOR_STATE_BUSY)
  {
     return HAL_BUSY;
  }
     
  /* Update the NOR controller state */
  hnor->State = HAL_NOR_STATE_BUSY;
  
  /* Send block erase command sequence */
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_FIRST), NOR_CMD_DATA_FIRST);
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_SECOND), NOR_CMD_DATA_SECOND);
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_THIRD), NOR_CMD_DATA_CHIP_BLOCK_ERASE_THIRD);
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_FOURTH), NOR_CMD_DATA_CHIP_BLOCK_ERASE_FOURTH);
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_FIFTH), NOR_CMD_DATA_CHIP_BLOCK_ERASE_FIFTH);
  NOR_WRITE8((uint32_t)(BlockAddress + Address), NOR_CMD_DATA_BLOCK_ERASE);

  /* Check the NOR memory status and update the controller state */
  hnor->State = HAL_NOR_STATE_READY;
    
  /* Process unlocked */
  __HAL_UNLOCK(hnor);
  
  return HAL_OK;
}

/**
  * @brief  Erase the entire NOR chip.
  * @param  Address : Device address  
  * @retval HAL status
  */
HAL_StatusTypeDef _NOR_Erase_Chip(void)
{
  NOR_HandleTypeDef *hnor = &norHandle;
  
  /* Process Locked */
  __HAL_LOCK(hnor);
  
  /* Check the NOR controller state */
  if(hnor->State == HAL_NOR_STATE_BUSY)
  {
     return HAL_BUSY;
  }
  
    
  /* Update the NOR controller state */
  hnor->State = HAL_NOR_STATE_BUSY;  
    
  /* Send NOR chip erase command sequence */
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_FIRST),  NOR_CMD_DATA_FIRST);
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_SECOND), NOR_CMD_DATA_SECOND);
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_THIRD),  NOR_CMD_DATA_CHIP_BLOCK_ERASE_THIRD);
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_FOURTH), NOR_CMD_DATA_CHIP_BLOCK_ERASE_FOURTH);
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_FIFTH),  NOR_CMD_DATA_CHIP_BLOCK_ERASE_FIFTH);  
  NOR_WRITE8(NOR_ADDR_SHIFT8(NOR_DEVICE_ADDR, NOR_CMD_ADDRESS_SIXTH),  NOR_CMD_DATA_CHIP_ERASE);
  
  /* Check the NOR memory status and update the controller state */
  hnor->State = HAL_NOR_STATE_READY;
    
  /* Process unlocked */
  __HAL_UNLOCK(hnor);
  
  return HAL_OK;  
}


#endif /* HAL_NOR_MODULE_ENABLED */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
