#ifndef __BSP_H__
#define __BSP_H__
#include <Arduino.h>

//my 103zet6 core
#ifdef ARDUINO_F103Z_HAOYUCORE
  #include "FSMC_F103Z_HAOYU.h"
#elif defined(ARDUINO_F103Z_UPTECH)
  #include "FSMC_F103Z_UPTECH.h"
#endif

#if FIXED_NBL01_CONNECTEDERR
  #ifdef __cplusplus
  extern "C"{
  #endif
  
  HAL_StatusTypeDef SRAM_Read_8b(uint32_t Addr,  uint8_t *pDstBuffer, uint32_t BufferSize);
  HAL_StatusTypeDef SRAM_Write_8b(uint32_t Addr, uint8_t *pSrcBuffer, uint32_t BufferSize);
  #ifdef __cplusplus
  } //extern "C"
  #endif
  
  #define EXTRAM_Read_8b(a,b,s)   SRAM_Read_8b((a),(b),(s))
  #define EXTRAM_Write_8b(a,b,s)  SRAM_Write_8b((a),(b),(s))
  
  /* 16/32 bit use hal lib function */
  extern SRAM_HandleTypeDef  sramHandle;
  #define EXTRAM_Read_16b(a,b,s)   HAL_SRAM_Read_16b(&sramHandle,(uint32_t *)((a) + EXTRAM_START),b,s)
  #define EXTRAM_Read_32b(a,b,s)   HAL_SRAM_Read_32b(&sramHandle,(uint32_t *)((a) + EXTRAM_START),b,s)
  #define EXTRAM_Write_16b(a,b,s) HAL_SRAM_Write_16b(&sramHandle,(uint32_t *)((a) + EXTRAM_START),b,s)
  #define EXTRAM_Write_32b(a,b,s) HAL_SRAM_Write_32b(&sramHandle,(uint32_t *)((a) + EXTRAM_START),b,s)
#endif

#endif   //__BSP_H__