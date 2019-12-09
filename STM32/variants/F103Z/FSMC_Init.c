#include "bsp.h"
#ifdef __GNUC__
  #pragma GCC diagnostic ignored "-Wunused-variable"
#endif

void _Error_Handler(char* file, uint32_t line);
static uint8_t FSMC_GPIO_Initialized = 0;

void STM_FSMC_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  if (FSMC_GPIO_Initialized) return;
     FSMC_GPIO_Initialized=1;
  /* Peripheral clock enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOE_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOG_CLK_ENABLE();
	__HAL_RCC_FSMC_CLK_ENABLE();
  
  /** FSMC GPIO Configuration  
  PF0   ------> FSMC_A0
  PF1   ------> FSMC_A1
  PF2   ------> FSMC_A2
  PF3   ------> FSMC_A3
  PF4   ------> FSMC_A4
  PF5   ------> FSMC_A5
  PF12  ------> FSMC_A6
  PF13  ------> FSMC_A7
  PF14  ------> FSMC_A8
  PF15  ------> FSMC_A9
  PG0   ------> FSMC_A10
  PG1   ------> FSMC_A11
  PG2   ------> FSMC_A12
  PG3   ------> FSMC_A13
  PG4   ------> FSMC_A14
  PG5   ------> FSMC_A15
  PD11  ------> FSMC_A16 FSMC_CLE   //nand
  PD12  ------> FSMC_A17 FSMC_ALE   //nand
  PD13  ------> FSMC_A18
  PE3   ------> FSMC_A19
  PE4   ------> FSMC_A20
  PE5   ------> FSMC_A21
  PE6   ------> FSMC_A22
  PE2   ------> FSMC_A23
  PG13  ------> FSMC_A24
  PG14  ------> FSMC_A25
  PD14  ------> FSMC_D0
  PD15  ------> FSMC_D1
  PD0   ------> FSMC_D2
  PD1   ------> FSMC_D3
  PE7   ------> FSMC_D4
  PE8   ------> FSMC_D5
  PE9   ------> FSMC_D6
  PE10  ------> FSMC_D7
  PE11  ------> FSMC_D8
  PE12  ------> FSMC_D9
  PE13  ------> FSMC_D10
  PE14  ------> FSMC_D11
  PE15  ------> FSMC_D12
  PD8   ------> FSMC_D13
  PD9   ------> FSMC_D14
  PD10  ------> FSMC_D15
  PD4   ------> FSMC_NOE       //r 
  PD5   ------> FSMC_NWE       //w
  
  PD6   ------> FSMC_NWAIT     //nor/nand
  PD7   ------> FSMC_NE1/NCE2  //nand 
  PE0   ------> FSMC_NBL0      //sram
  PE1   ------> FSMC_NBL1      //sram
  PG6  -------> FSMC_INT2      //nand op
  PG9   ------> FSMC_NE2       //nor/sram/lcd
  PG10  ------> FSMC_NE3       //nor/sram/lcd
  PG12  ------> FSMC_NE4       //nor/sram/lcd
*/

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_0| GPIO_PIN_1| GPIO_PIN_2|GPIO_PIN_3| GPIO_PIN_4|GPIO_PIN_5
                      |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4
#if (NORSRAM_BANKS & NORSRAM_BANK1_2)  
                       |GPIO_PIN_9
#endif
#if (NORSRAM_BANKS & NORSRAM_BANK1_3)  
					   |GPIO_PIN_10
#endif
#if (NORSRAM_BANKS & NORSRAM_BANK1_4)  
					   |GPIO_PIN_12 
#endif
#if FSMC_ADDRESSBITS > 24  /* 32M*16 */
                       |GPIO_PIN_13   //A24 PG13
#endif						 
#if FSMC_ADDRESSBITS > 25  /* 16M*16 */
                       |GPIO_PIN_14   //A25 PG14
#endif						 
                       |GPIO_PIN_5;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin =  GPIO_PIN_0|GPIO_PIN_1 /*NBL0/NBL1*/
#if FSMC_ADDRESSBITS > 23  /* 16M*16 */
                         |GPIO_PIN_2   //A23 PE2
#endif						 
#if FSMC_ADDRESSBITS > 19  /* 1M*16 */ 
						 |GPIO_PIN_3  //A19 PE3
#endif
#if FSMC_ADDRESSBITS > 20  /* 2M*16 */
                         |GPIO_PIN_4 //A20 PE4
#endif						 
#if FSMC_ADDRESSBITS > 21  /* 4M*16 */ 
                         |GPIO_PIN_5  //A21 PE5
#endif						 
#if FSMC_ADDRESSBITS > 22 /* 8M*16 */
                         |GPIO_PIN_6  //A22 PE6
#endif						 
						 |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10 
                         |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14 
                         |GPIO_PIN_15;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /* GPIO_InitStruct */
  GPIO_InitStruct.Pin = GPIO_PIN_0| GPIO_PIN_1| GPIO_PIN_4| GPIO_PIN_5
#if (NORSRAM_BANKS & NORSRAM_BANK1_1)  
                      | GPIO_PIN_7
#endif

					  | GPIO_PIN_8| GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12
#if   FSMC_ADDRESSBITS > 18 /* 512K*16 */ 					  
					  |GPIO_PIN_13
#endif					  
					  |GPIO_PIN_14|GPIO_PIN_15;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  
    /*!< Configure PD6 for NOR memory Ready/Busy signal */
#if FSMC_NWAIT_PD6	
  GPIO_InitStruct.Pin  = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
#endif

#if FSMC_INT2
    /*!< Configure PG6 for NAND INT signal */
  GPIO_InitStruct.Pin  = GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);
#endif

}

#ifdef FSMC_NORBANK
NOR_HandleTypeDef norHandle;
static uint8_t FSMC_NOR_Initialized = 0;

void STM_FSMC_NOR_Init(void)
{ 	
  static FSMC_NORSRAM_TimingTypeDef Timing;
  norHandle.Instance = FSMC_NORSRAM_DEVICE;
  norHandle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  
  if (FSMC_NOR_Initialized) return;
  FSMC_NOR_Initialized=1;
	 
  STM_FSMC_GPIO_Init();
  
  
  /* Timing  SST39VF040-70  
    TAS  0 ns
	TAH 30 ns
	TDS 40 ns.
	TDH  0 ns 
  */
#ifdef SST39VF040
  Timing.AddressSetupTime      = 0;	  //  14ns(1/72M)*(HCLK+1) 0ns	
  Timing.AddressHoldTime       = 2;   //  FSMC_ACCESS_MODE_B   30  
  Timing.DataSetupTime         = 2;   //  14ns(1/72M)* (1+2)   40ns
#elif defined(MX29LV640)
  Timing.AddressSetupTime = 5;
  Timing.AddressHoldTime = 1;
  Timing.DataSetupTime = 7;   
#else
  #warning "nor device undef! use default!" 	
  Timing.AddressSetupTime = 5;
  Timing.AddressHoldTime = 1;
  Timing.DataSetupTime = 7;   
#endif

  Timing.BusTurnAroundDuration = 1;
  Timing.CLKDivision = 2;
  Timing.DataLatency = 2;
  Timing.AccessMode = FSMC_ACCESS_MODE_B;

  norHandle.Init.NSBank 			= FSMC_NORBANK;
  norHandle.Init.DataAddressMux 	= FSMC_DATA_ADDRESS_MUX_DISABLE;
  norHandle.Init.MemoryType 		= FSMC_MEMORY_TYPE_NOR;
  
#ifdef FSMC_NORSRAM_MEM_BUS_WIDTH   // SST39VF040 is 8 bit width
  norHandle.Init.MemoryDataWidth	= FSMC_NORSRAM_MEM_BUS_WIDTH;
#else  
  norHandle.Init.MemoryDataWidth	= FSMC_NORSRAM_MEM_BUS_WIDTH_16;
#endif  

  norHandle.Init.BurstAccessMode	= FSMC_BURST_ACCESS_MODE_DISABLE;
  norHandle.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  norHandle.Init.WrapMode 			= FSMC_WRAP_MODE_DISABLE;
  norHandle.Init.WaitSignalActive 	= FSMC_WAIT_TIMING_BEFORE_WS;
  norHandle.Init.WriteOperation 	= FSMC_WRITE_OPERATION_ENABLE;
  norHandle.Init.WaitSignal 		= FSMC_WAIT_SIGNAL_DISABLE;
  norHandle.Init.ExtendedMode 		= FSMC_EXTENDED_MODE_DISABLE;
  norHandle.Init.AsynchronousWait 	= FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  norHandle.Init.WriteBurst 		= FSMC_WRITE_BURST_DISABLE;

  /* ExtTiming */

  if(HAL_NOR_Init(&norHandle, &Timing, &Timing) != HAL_OK)
  {
    _Error_Handler(__FILENAME__, __LINE__);
  }
}

#endif

#ifdef FSMC_NANDBANK
NAND_HandleTypeDef nandHandle;
static uint8_t FSMC_NAND_Initialized = 0;
void STM_FSMC_NAND_Init(void)
{ 	
  FSMC_NAND_PCC_TimingTypeDef Timing;

  if (FSMC_NAND_Initialized) return;
  FSMC_NAND_Initialized=1;

  STM_FSMC_GPIO_Init();
  
  nandHandle.Instance  = FSMC_NAND_DEVICE;
  
  /*NAND Configuration */  
  Timing.SetupTime     = 0U;
  Timing.WaitSetupTime = 2U; 
  Timing.HoldSetupTime = 1U;
  Timing.HiZSetupTime  = 0U;
  
  nandHandle.Init.NandBank        = FSMC_NANDBANK;
  nandHandle.Init.Waitfeature     = FSMC_NAND_PCC_WAIT_FEATURE_ENABLE;
  nandHandle.Init.MemoryDataWidth = FSMC_NAND_PCC_MEM_BUS_WIDTH_8;
  nandHandle.Init.EccComputation  = FSMC_NAND_ECC_ENABLE;
  nandHandle.Init.ECCPageSize     = FSMC_NAND_ECC_PAGE_SIZE_512BYTE;
  nandHandle.Init.TCLRSetupTime   = 0U;
  nandHandle.Init.TARSetupTime    = 0U;
  
  nandHandle.Config.BlockNbr      = NAND_MAX_PLANE;
  nandHandle.Config.BlockSize     = NAND_BLOCK_SIZE;
  nandHandle.Config.PlaneSize     = NAND_PLANE_SIZE;
  nandHandle.Config.PageSize      = NAND_PAGE_SIZE; 
  nandHandle.Config.SpareAreaSize = NAND_SPARE_AREA_SIZE;
  
  /* NAND controller initialization */
//  NAND_MspInit();
  HAL_NAND_Init(&nandHandle, &Timing, &Timing);
}
#endif

//lcd FSMC
#ifdef FSMC_LCDBANK
SRAM_HandleTypeDef fsmcLcdHandle;
void STM_FSMC_LCD_TimeSet(uint8_t _as, uint8_t _ds)
{ 	
  FSMC_NORSRAM_TimingTypeDef Timing;

  STM_FSMC_GPIO_Init();
  /** Perform the SRAM4(LCD) initialization sequence
  */
  fsmcLcdHandle.Instance = FSMC_NORSRAM_DEVICE;
  fsmcLcdHandle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
  /* fsmcLcdHandle.Init */
  fsmcLcdHandle.Init.NSBank = FSMC_LCDBANK;
  fsmcLcdHandle.Init.DataAddressMux = FSMC_DATA_ADDRESS_MUX_DISABLE;
  fsmcLcdHandle.Init.MemoryType = FSMC_MEMORY_TYPE_SRAM;
  fsmcLcdHandle.Init.MemoryDataWidth = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  fsmcLcdHandle.Init.BurstAccessMode = FSMC_BURST_ACCESS_MODE_DISABLE;
  fsmcLcdHandle.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  fsmcLcdHandle.Init.WrapMode = FSMC_WRAP_MODE_DISABLE;
  fsmcLcdHandle.Init.WaitSignalActive = FSMC_WAIT_TIMING_BEFORE_WS;
  fsmcLcdHandle.Init.WriteOperation = FSMC_WRITE_OPERATION_ENABLE;
  fsmcLcdHandle.Init.WaitSignal = FSMC_WAIT_SIGNAL_DISABLE;
  fsmcLcdHandle.Init.ExtendedMode = FSMC_EXTENDED_MODE_DISABLE;
  fsmcLcdHandle.Init.AsynchronousWait = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  fsmcLcdHandle.Init.WriteBurst = FSMC_WRITE_BURST_DISABLE;
//  fsmcLcdHandle.Init.PageSize = FSMC_PAGE_SIZE_NONE;
  /* Timing */
  Timing.AddressSetupTime = _as/14;	//   1000/72(HCLK) =14ns
  Timing.AddressHoldTime  =   1;
  Timing.DataSetupTime    =    _ds/14;	//   1000/72(HCLK) =14ns
  Timing.BusTurnAroundDuration = 1;
  Timing.CLKDivision      = 2;
  Timing.DataLatency      = 2;
  Timing.AccessMode       = FSMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_SRAM_Init(&fsmcLcdHandle, &Timing, NULL) != HAL_OK)
  {
    _Error_Handler(__FILENAME__, __LINE__);
  }
}

#ifndef  LCD_ADDR_SETUPTIME
# define LCD_ADDR_SETUPTIME 20
#endif
#ifndef  LCD_DATA_SETUPTIME
# define LCD_DATA_SETUPTIME 45
#endif

static uint8_t FSMC_LCD_Initialized = 0;
void STM_FSMC_LCD_Init(void)
{
    if (FSMC_LCD_Initialized) return;
    FSMC_LCD_Initialized=1;
  
	STM_FSMC_LCD_TimeSet(LCD_ADDR_SETUPTIME, LCD_DATA_SETUPTIME);
#ifdef LCDBL_PIN
    pinMode(LCDBL_PIN,OUTPUT);
# ifdef LCDBL_ON
	digitalWrite(LCDBL_PIN, LCDBL_ON); //backlight on if can set
# else	
	digitalWrite(LCDBL_PIN, HIGH); //backlight on if can set
# endif	
#endif	
}

#endif



#ifdef FSMC_SRAMBANK

SRAM_HandleTypeDef sramHandle;
static uint8_t FSMC_SRAM_Initialized = 0;
void STM_FSMC_SRAM_Init(void)
{ 	
  FSMC_NORSRAM_TimingTypeDef Timing;
  
  if (FSMC_SRAM_Initialized) return;
  FSMC_SRAM_Initialized=1;
  
  STM_FSMC_GPIO_Init();
  
   /** Perform the SRAM memory initialization sequence
  */
  sramHandle.Instance = FSMC_NORSRAM_DEVICE;
  sramHandle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;

  /* sramHandle.Init */
  sramHandle.Init.NSBank             = FSMC_SRAMBANK;
  sramHandle.Init.DataAddressMux     = FSMC_DATA_ADDRESS_MUX_DISABLE;   //数据线与地址线不复用
  sramHandle.Init.MemoryType         = FSMC_MEMORY_TYPE_SRAM;           //存储器类型SRAM
  sramHandle.Init.MemoryDataWidth    = FSMC_NORSRAM_MEM_BUS_WIDTH_16;   //16bit SRAM
  sramHandle.Init.BurstAccessMode    = FSMC_BURST_ACCESS_MODE_DISABLE;  //使用异步写模式，禁止突发模式
  sramHandle.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;   //等待信号，只在突发模式下有效，
  sramHandle.Init.WrapMode           = FSMC_WRAP_MODE_DISABLE;
  sramHandle.Init.WaitSignalActive   = FSMC_WAIT_TIMING_BEFORE_WS;
  sramHandle.Init.WriteOperation     = FSMC_WRITE_OPERATION_ENABLE;
  sramHandle.Init.WaitSignal         = FSMC_WAIT_SIGNAL_DISABLE;
  sramHandle.Init.ExtendedMode       = FSMC_EXTENDED_MODE_DISABLE;     /*读写采用相同时序*/
  sramHandle.Init.AsynchronousWait   = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  sramHandle.Init.WriteBurst         = FSMC_WRITE_BURST_DISABLE;
 //  sramHandle.Init.PageSize = FSMC_PAGE_SIZE_NONE;

  /* Timing
    IS64LV25616-12T   12ns
	IS61LV25616AL-10T 10ns
	IS62WV51216BLL-55 55ns
  */
  Timing.AddressSetupTime      = 0;	  //  <15   14ns(1/72M)*(HCLK+1) ns	
  Timing.AddressHoldTime       = 1;   //  1~15  FSMC_ACCESS_MODE_A unused 
  Timing.DataSetupTime         = 3;   //  1~255 14ns(1/72M)* (1+3) 56ns  for IS62WV51216BLL-55TL
//  Timing.DataSetupTime       = 1;   //        14ns(1/72M)* (0+1) 14ns  for IS64/61LVx-10T/12T
  Timing.BusTurnAroundDuration = 1;
  Timing.CLKDivision           = 2;   //  1~16 
  Timing.DataLatency           = 2;
  Timing.AccessMode = FSMC_ACCESS_MODE_A;
  /* ExtTiming */

  if (HAL_SRAM_Init(&sramHandle, &Timing, NULL) != HAL_OK)
  {
    _Error_Handler(__FILENAME__, __LINE__);
  }
}

#if FIXED_NBL01_CONNECTEDERR
/* 
   F103Z_UPTECH have a hardware err ,now fixed it
   F103Z_UPTECH 板子的硬件错误，FSMC_NBL0 错接在 sram UB，FSMC_NBL1 错接在 sram LB，造成8bit 读写错误；
   因此8位读写函数 采用16位读写代替，并根据奇偶地址相应处理高byte和低byte,替代HAL_SRAM_Read_8b 和
   替代HAL_SRAM_Write_8b
*/
HAL_StatusTypeDef SRAM_Read_8b(uint32_t Addr,  uint8_t *pDstBuffer, uint32_t BufferSize)
{
  uint32_t sramaddress = Addr + SRAM_START;
  __IO uint16_t* ptr;
  
  SRAM_HandleTypeDef *hsram = &sramHandle;
  
  /* Process Locked */
  __HAL_LOCK(hsram);
  
  /* Update the SRAM controller state */
  hsram->State = HAL_SRAM_STATE_BUSY;  
  
  /* Read data from memory */
  for(; BufferSize != 0U; BufferSize--)
  {
	ptr = (uint16_t *)(sramaddress & 0xfffffffe);  /* 指向包含该8bit数据的16位地址(偶地址) */
	
	if((sramaddress &  0x00000001U) == 0)  
	   *pDstBuffer = *ptr & 0x00ff;  /*低位*/
    else
       *pDstBuffer = *ptr >> 8;    /*高位*/
   
    pDstBuffer++;
    sramaddress++;
  }
  
  /* Update the SRAM controller state */
  hsram->State = HAL_SRAM_STATE_READY;    

  /* Process unlocked */
  __HAL_UNLOCK(hsram); 
    
  return HAL_OK;   
}

/**
  * @brief  Writes 8-bit buffer to SRAM memory. 
  * @param  hsram: pointer to a SRAM_HandleTypeDef structure that contains
  *                the configuration information for SRAM module.
  * @param  pAddress: Pointer to write start address
  * @param  pSrcBuffer: Pointer to source buffer to write  
  * @param  BufferSize: Size of the buffer to write to memory
  * @retval HAL status
  */
HAL_StatusTypeDef  SRAM_Write_8b(uint32_t Addr, uint8_t *pSrcBuffer, uint32_t BufferSize)
{
  uint32_t sramaddress = Addr + SRAM_START;
  __IO uint16_t* ptr;
  SRAM_HandleTypeDef *hsram = &sramHandle;
  
  /* Check the SRAM controller state */
  if(hsram->State == HAL_SRAM_STATE_PROTECTED)
  {
    return  HAL_ERROR; 
  }
  
  /* Process Locked */
  __HAL_LOCK(hsram);
  
  /* Update the SRAM controller state */
  hsram->State = HAL_SRAM_STATE_BUSY; 

  /* Write data to memory */
  for(; BufferSize != 0U; BufferSize--)
  {
	ptr = (uint16_t *)(sramaddress & 0xfffffffe);  /*请低位*/
    	
	if((sramaddress &  0x00000001U) == 0)
       *ptr  = (*ptr & 0xff00) | *pSrcBuffer; 
    else
       *ptr  = (*ptr & 0x00ff) | (*pSrcBuffer << 8);
  
    pSrcBuffer++;
    sramaddress++;    
  }    

  /* Update the SRAM controller state */
  hsram->State = HAL_SRAM_STATE_READY; 
  
  /* Process unlocked */
  __HAL_UNLOCK(hsram);
    
  return HAL_OK;   
}

#endif

#endif

#if NORSRAM_BANKS
void initVariant() {
#ifdef FSMC_SRAMBANK
	STM_FSMC_SRAM_Init();
#endif
#ifdef  FSMC_NORBANK
    STM_FSMC_NOR_Init();
#endif
#ifdef FSMC_LCDBANK
    STM_FSMC_LCD_Init();
#endif
#ifdef FSMC_NANDBANK
    STM_FSMC_NAND_Init();
#endif
}
#endif

#if USE_EXTRAMSYSMALLOC
extern void setHeap(unsigned char* s, unsigned char* e);
void setHeapAtSram(void){
 setHeap((unsigned char*)SRAM_START, (unsigned char*)(SRAM_START +SRAM_LENGTH));
}
#endif


