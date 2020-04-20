/*  hal_dacdemo.ino  hal dac demo
*
* stm32f103 tested
*/

DAC_HandleTypeDef hdac;
void setup() {
  // put your setup code here, to run once:
  MX_DAC_Init();
  HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (uint32_t out = 0; out < 4096; out++) {
    HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, out);
  }
}

/* DAC init function */
void MX_DAC_Init(void)
{
  DAC_ChannelConfTypeDef sConfig;

  /**DAC Initialization
  */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
  }

  /**DAC channel OUT1 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
  }

}

extern "C" {
  void HAL_DAC_MspInit(DAC_HandleTypeDef* dacHandle)
  {

    GPIO_InitTypeDef GPIO_InitStruct;
    if (dacHandle->Instance == DAC)
    {
      /* USER CODE BEGIN DAC_MspInit 0 */

      /* USER CODE END DAC_MspInit 0 */
      /* DAC clock enable */
      __HAL_RCC_DAC_CLK_ENABLE();

      /**DAC GPIO Configuration
        PA4     ------> DAC_OUT1
      */
      GPIO_InitStruct.Pin = GPIO_PIN_4;
      GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
      HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

      /* USER CODE BEGIN DAC_MspInit 1 */

      /* USER CODE END DAC_MspInit 1 */
    }
  }

  void HAL_DAC_MspDeInit(DAC_HandleTypeDef* dacHandle)
  {

    if (dacHandle->Instance == DAC)
    {
      /* USER CODE BEGIN DAC_MspDeInit 0 */

      /* USER CODE END DAC_MspDeInit 0 */
      /* Peripheral clock disable */
      __HAL_RCC_DAC_CLK_DISABLE();

      /**DAC GPIO Configuration
        PA4     ------> DAC_OUT1
      */
      HAL_GPIO_DeInit(GPIOA, GPIO_PIN_4);

      /* USER CODE BEGIN DAC_MspDeInit 1 */

      /* USER CODE END DAC_MspDeInit 1 */
    }
  }

} // extern "C"
