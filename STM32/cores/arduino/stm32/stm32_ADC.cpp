/**
  ******************************************************************************
  * @file    analog.c
  * @author  WI6LABS
  * @version V1.0.0
  * @date    01-August-2016
  * @brief   provide analog services (ADC + PWM)
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************

  2018 modify by huaweiwx@sina
*/

#include "Arduino.h"
#include "stm32_gpio_af.h"

//#ifdef HAL_ADC_MODULE

#ifndef ADC_SAMPLINGTIME
# if defined(ADC_SAMPLETIME_8CYCLES_5)
#	define ADC_SAMPLINGTIME					ADC_SAMPLETIME_8CYCLES_5
# elif defined(ADC_SAMPLETIME_12CYCLES_5)
#	define ADC_SAMPLINGTIME					ADC_SAMPLETIME_12CYCLES_5
# elif defined(ADC_SAMPLETIME_13CYCLES_5)
#	define ADC_SAMPLINGTIME					ADC_SAMPLETIME_13CYCLES_5
# elif defined(ADC_SAMPLETIME_15CYCLES)
#	define ADC_SAMPLINGTIME					ADC_SAMPLETIME_15CYCLES
# elif defined(ADC_SAMPLETIME_16CYCLES)
#	define ADC_SAMPLINGTIME					ADC_SAMPLETIME_16CYCLES
# elif defined(ADC_SAMPLETIME_19CYCLES_5)
#	define ADC_SAMPLINGTIME					ADC_SAMPLETIME_19CYCLES_5
# endif
#endif /* !ADC_SAMPLINGTIME */

/*
   Minimum ADC sampling time is required when reading
   internal channels so set it to max possible value.
   It can be defined more precisely by defining:
   ADC_SAMPLINGTIME_INTERNAL
   to the desired ADC sample time.
*/
#ifndef ADC_SAMPLINGTIME_INTERNAL
# if defined(ADC_SAMPLETIME_480CYCLES)
#	define ADC_SAMPLINGTIME_INTERNAL		ADC_SAMPLETIME_480CYCLES
# elif defined(ADC_SAMPLETIME_384CYCLES)
#	define ADC_SAMPLINGTIME_INTERNAL		ADC_SAMPLETIME_384CYCLES
# elif defined(ADC_SAMPLETIME_810CYCLES_5)
#	define ADC_SAMPLINGTIME_INTERNAL		ADC_SAMPLETIME_810CYCLES_5
# elif defined(ADC_SAMPLETIME_640CYCLES_5)
#	define ADC_SAMPLINGTIME_INTERNAL		ADC_SAMPLETIME_640CYCLES_5
# elif defined(ADC_SAMPLETIME_601CYCLES_5)
#	define ADC_SAMPLINGTIME_INTERNAL		ADC_SAMPLETIME_601CYCLES_5
# elif defined(ADC_SAMPLETIME_247CYCLES_5)
#	define ADC_SAMPLINGTIME_INTERNAL		ADC_SAMPLETIME_247CYCLES_5
# elif defined(ADC_SAMPLETIME_239CYCLES_5)
#	define ADC_SAMPLINGTIME_INTERNAL		ADC_SAMPLETIME_239CYCLES_5
# elif defined(ADC_SAMPLETIME_160CYCLES_5)
#	define ADC_SAMPLINGTIME_INTERNAL		ADC_SAMPLETIME_160CYCLES_5
# else
#	error "ADC sampling time could not be defined for internal channels!"
# endif
#endif /* !ADC_SAMPLINGTIME_INTERNAL */

#ifndef ADC_CLOCK_DIV
# if   defined(ADC_CLOCK_SYNC_PCLK_DIV4)
#  define ADC_CLOCK_DIV					ADC_CLOCK_SYNC_PCLK_DIV4
# elif defined(ADC_CLOCK_SYNC_PCLK_DIV2)
#  define ADC_CLOCK_DIV					ADC_CLOCK_SYNC_PCLK_DIV2
# elif defined(ADC_CLOCK_ASYNC_DIV1)
#  define ADC_CLOCK_DIV					ADC_CLOCK_ASYNC_DIV1
# endif
#endif //ADC_CLOCK_DIV

#ifndef ADC_REGULAR_RANK_1
# define ADC_REGULAR_RANK_1  1
#endif


//static int g_current_pin = pin; /* Needed for HAL_ADC_MspInit*/
#ifndef  ADC_DEFAULT_RESOLUTION
# define ADC_DEFAULT_RESOLUTION  10
#endif
static int readResolution = ADC_DEFAULT_RESOLUTION;

#ifdef ADC4
 static ADC_HandleTypeDef handle[4];
#elif defined(ADC3)
 static ADC_HandleTypeDef handle[3];
#elif defined(ADC2)
 static ADC_HandleTypeDef handle[2];
#else
 static ADC_HandleTypeDef handle[1];
#endif

extern "C"
void analogReadResolution(int resolution) {
  readResolution = resolution;
}

extern "C"
int analogReadResolutionVal(void) {
  return  readResolution;
}

extern "C"
void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc) /*called by HAL_ADC_Init() */
{
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* ADC Periph clock enable */
  if (hadc->Instance == ADC1) {
#ifdef __HAL_RCC_ADC1_CLK_ENABLE
    __HAL_RCC_ADC1_CLK_ENABLE();
#endif
#ifdef __HAL_RCC_ADC12_CLK_ENABLE
    __HAL_RCC_ADC12_CLK_ENABLE();
#endif
  }

#ifdef ADC2
  else if (hadc->Instance == ADC2) {
# ifdef __HAL_RCC_ADC2_CLK_ENABLE
    __HAL_RCC_ADC2_CLK_ENABLE();
# endif
# ifdef __HAL_RCC_ADC12_CLK_ENABLE
    __HAL_RCC_ADC12_CLK_ENABLE();
# endif
  }
#endif //ADC2

#ifdef ADC3
  else if (hadc->Instance == ADC3) {
# ifdef __HAL_RCC_ADC3_CLK_ENABLE
    __HAL_RCC_ADC3_CLK_ENABLE();
# endif
# ifdef __HAL_RCC_ADC34_CLK_ENABLE
    __HAL_RCC_ADC34_CLK_ENABLE();
# endif
# if defined(ADC345_COMMON)
    __HAL_RCC_ADC345_CLK_ENABLE();
# endif
  }
#endif //ADC3

#ifdef ADC4
  else if (hadc->Instance == ADC4) {
# ifdef __HAL_RCC_ADC34_CLK_ENABLE
    __HAL_RCC_ADC34_CLK_ENABLE();
# endif
# if defined(ADC345_COMMON)
    __HAL_RCC_ADC345_CLK_ENABLE();
# endif
  }
#endif //ADC4

#ifdef ADC5
# if defined(ADC345_COMMON)
  else if (hadc->Instance == ADC5) {
    __HAL_RCC_ADC345_CLK_ENABLE();
  }
# endif
#endif //ADC5

#ifdef __HAL_RCC_ADC_CLK_ENABLE
  __HAL_RCC_ADC_CLK_ENABLE();
#endif

  /* For STM32F1, STM32H7, and STM32MP1 ADC prescaler is configured in
     SystemClock_Config (variant.cpp) */
#if defined(__HAL_RCC_ADC_CONFIG) && !defined(STM32F1) && !defined(GD32F10X)&& !defined(GD32F20X) && \
    !defined(STM32H7) && !defined(STM32MP1)
  /* ADC Periph interface clock configuration */
  __HAL_RCC_ADC_CONFIG(RCC_ADCCLKSOURCE_SYSCLK);
#endif

  /* Configure ADC GPIO pin */
  //  if (!(g_current_pin & PADC_BASE)) {
  //    pinmap_pinout(g_current_pin, PinMap_ADC);
  //  }
}

extern "C"
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
#ifdef __HAL_RCC_ADC_FORCE_RESET
  __HAL_RCC_ADC_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC_RELEASE_RESET
  __HAL_RCC_ADC_RELEASE_RESET();
#endif

  if (hadc->Instance == ADC1) {
#ifdef __HAL_RCC_ADC1_FORCE_RESET
    __HAL_RCC_ADC1_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC1_RELEASE_RESET
    __HAL_RCC_ADC1_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC12_FORCE_RESET
    __HAL_RCC_ADC12_FORCE_RESET();
#endif
#ifdef __HAL_RCC_ADC12_RELEASE_RESET
    __HAL_RCC_ADC12_RELEASE_RESET();
#endif
#ifdef __HAL_RCC_ADC1_CLK_DISABLE
    __HAL_RCC_ADC1_CLK_DISABLE();
#endif
#ifdef __HAL_RCC_ADC12_CLK_DISABLE
    __HAL_RCC_ADC12_CLK_DISABLE();
#endif
  }
  
#ifdef ADC2
  else if (hadc->Instance == ADC2) {
# ifdef __HAL_RCC_ADC2_FORCE_RESET
    __HAL_RCC_ADC2_FORCE_RESET();
# endif
# ifdef __HAL_RCC_ADC2_RELEASE_RESET
    __HAL_RCC_ADC2_RELEASE_RESET();
# endif
# ifdef __HAL_RCC_ADC12_FORCE_RESET
    __HAL_RCC_ADC12_FORCE_RESET();
# endif
# ifdef __HAL_RCC_ADC12_RELEASE_RESET
    __HAL_RCC_ADC12_RELEASE_RESET();
# endif
# ifdef __HAL_RCC_ADC2_CLK_DISABLE
    __HAL_RCC_ADC2_CLK_DISABLE();
# endif
# ifdef __HAL_RCC_ADC2_CLK_DISABLE
    __HAL_RCC_ADC2_CLK_DISABLE();
# endif
  }
#endif //ADC2

#ifdef ADC3
  else if (hadc->Instance == ADC3) {
# ifdef __HAL_RCC_ADC3_FORCE_RESET
    __HAL_RCC_ADC3_FORCE_RESET();
# endif
# ifdef __HAL_RCC_ADC3_RELEASE_RESET
    __HAL_RCC_ADC3_RELEASE_RESET();
# endif
# ifdef __HAL_RCC_ADC34_FORCE_RESET
    __HAL_RCC_ADC34_FORCE_RESET();
# endif
# ifdef __HAL_RCC_ADC34_RELEASE_RESET
    __HAL_RCC_ADC34_RELEASE_RESET();
# endif
# ifdef __HAL_RCC_ADC3_CLK_DISABLE
    __HAL_RCC_ADC3_CLK_DISABLE();
# endif
# ifdef __HAL_RCC_ADC34_CLK_DISABLE
    __HAL_RCC_ADC34_CLK_DISABLE();
# endif
# if defined(ADC345_COMMON)
    __HAL_RCC_ADC345_FORCE_RESET();
    __HAL_RCC_ADC345_RELEASE_RESET();
    __HAL_RCC_ADC345_CLK_DISABLE();
# endif
  }
#endif //ADC3

#ifdef ADC4
  else if (hadc->Instance == ADC4) {
# ifdef __HAL_RCC_ADC34_FORCE_RESET
    __HAL_RCC_ADC34_FORCE_RESET();
# endif
# ifdef __HAL_RCC_ADC34_RELEASE_RESET
    __HAL_RCC_ADC34_RELEASE_RESET();
# endif
# ifdef __HAL_RCC_ADC34_CLK_DISABLE
    __HAL_RCC_ADC34_CLK_DISABLE();
# endif
# if defined(ADC345_COMMON)
    __HAL_RCC_ADC345_FORCE_RESET();
    __HAL_RCC_ADC345_RELEASE_RESET();
    __HAL_RCC_ADC345_CLK_DISABLE();
# endif
  }
#endif //ADC4
#ifdef ADC5
  else if (hadc->Instance == ADC5) {
# if defined(ADC345_COMMON)
    __HAL_RCC_ADC345_FORCE_RESET();
    __HAL_RCC_ADC345_RELEASE_RESET();
    __HAL_RCC_ADC345_CLK_DISABLE();
# endif
  }
#endif //ADC5

#ifdef __HAL_RCC_ADC_CLK_DISABLE
  //  __HAL_RCC_ADC_FORCE_RESET();
  //  __HAL_RCC_ADC_RELEASE_RESET();
  __HAL_RCC_ADC_CLK_DISABLE();
#endif
}

uint32_t analogReadInternalChannel(PinName pin)
{
  uint32_t channel = 0;
  switch (pin) {
#if defined(ADC_CHANNEL_TEMPSENSOR)
    case PADC_TEMP:
      channel = ADC_CHANNEL_TEMPSENSOR;
      break;
#endif
#if defined(ADC_CHANNEL_TEMPSENSOR_ADC1)
    case PADC_TEMP:
      channel = ADC_CHANNEL_TEMPSENSOR_ADC1;
      break;
#endif
#if defined(ADC5) && defined(ADC_CHANNEL_TEMPSENSOR_ADC5)
    case PADC_TEMP_ADC5:
      channel = ADC_CHANNEL_TEMPSENSOR_ADC5;
      break;
#endif
#ifdef ADC_CHANNEL_VREFINT
    case PADC_VREF:
      channel = ADC_CHANNEL_VREFINT;
      break;
#endif
#ifdef ADC_CHANNEL_VBAT
    case PADC_VBAT:
      channel = ADC_CHANNEL_VBAT;
      break;
#endif
    default:
      channel = 0;
      break;
  }
  return channel;
}

#ifdef ADC_OFFSET_NONE  //F3/H7/L4
extern "C"
int analogReadChanel(ADC_TypeDef* ADCx, uint32_t ch, uint32_t differentialMode)
#else
extern "C"
int analogReadChanel(ADC_TypeDef* ADCx, uint32_t ch)
#endif
{
  int instanceIndex = 0;
  volatile int ret = 0;
#ifdef ADC2
  if (ADCx == ADC2) {
    instanceIndex = 1;
  }
#endif
#ifdef ADC3
  if (ADCx == ADC3) {
    instanceIndex = 2;
  }
#endif
#ifdef ADC4
  if (ADCx == ADC4) {
    instanceIndex = 3;
  }
#endif

  handle[instanceIndex].Instance = ADCx;
  
  HAL_ADC_MspInit(&handle[instanceIndex]);

#ifdef ADC_CLOCK_DIV
  handle[instanceIndex].Init.ClockPrescaler = ADC_CLOCK_DIV;
#endif
#ifdef ADC_RESOLUTION_12B
  handle[instanceIndex].Init.Resolution = ADC_RESOLUTION_12B;
#endif
#ifdef ADC_DATAALIGN_RIGHT
  handle[instanceIndex].Init.DataAlign = ADC_DATAALIGN_RIGHT;
#endif
#ifdef ADC_SCAN_SEQ_FIXED
  handle[instanceIndex].Init.ScanConvMode = ADC_SCAN_SEQ_FIXED; /* Sequencer disabled (ADC conversion on only 1 channel: channel set on rank 1) */
#else
  handle[instanceIndex].Init.ScanConvMode = DISABLE;
#endif	
#ifdef ADC_EOC_SINGLE_CONV
  handle[instanceIndex].Init.EOCSelection = ADC_EOC_SINGLE_CONV;
#endif

#if !defined(STM32F1) && !defined(STM32F2) && !defined(STM32F4) && !defined(GD32F10X) && !defined(GD32F20X) &&\
    !defined(STM32F7) && !defined(STM32F373xC) && !defined(STM32F378)
  handle[instanceIndex].Init.LowPowerAutoWait      = DISABLE;                       /* Auto-delayed conversion feature disabled */
#endif
#if !defined(STM32F1) && !defined(STM32F2) && !defined(STM32F3) && \
    !defined(STM32F4) && !defined(STM32F7) && !defined(STM32G4) && \
    !defined(STM32H7) && !defined(STM32L4) && !defined(STM32MP1 ) && \
    !defined(STM32WB) && !defined(STM32F4) && !defined(GD32F10X) && !defined(GD32F20X)
  handle[instanceIndex].Init.LowPowerAutoPowerOff  = DISABLE;                       /* ADC automatically powers-off after a conversion and automatically wakes-up when a new conversion is triggered */
#endif
#ifdef ADC_CHANNELS_BANK_A
  handle[instanceIndex].Init.ChannelsBank          = ADC_CHANNELS_BANK_A;
#endif
  handle[instanceIndex].Init.ContinuousConvMode = DISABLE;                          /* Continuous mode disabled to have only 1 conversion at each conversion trig */
#if !defined(STM32F0) && !defined(STM32L0)&& !defined(GD32F10X)
  handle[instanceIndex].Init.NbrOfConversion       = 1;                             /* Specifies the number of ranks that will be converted within the regular group sequencer. */
#endif
  handle[instanceIndex].Init.DiscontinuousConvMode  = DISABLE;                      /* Parameter discarded because sequencer is disabled */
#if !defined(STM32F0)&& !defined(GD32F10X) && !defined(STM32G0) && !defined(STM32L0)
  handle[instanceIndex].Init.NbrOfDiscConversion   = 0;
#endif
  handle[instanceIndex].Init.ExternalTrigConv = ADC_SOFTWARE_START;
#if !defined(STM32F1) && !defined(GD32F10X) && !defined(GD32F20X)&& !defined(STM32F373xC) && !defined(STM32F378)
  handle[instanceIndex].Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
#endif
#if !defined(STM32F1) && !defined(STM32H7) && !defined(STM32MP1) && \
    !defined(STM32F373xC) && !defined(STM32F378)&& !defined(GD32F10X) && !defined(GD32F20X)
  handle[instanceIndex].Init.DMAContinuousRequests = DISABLE;
#endif
#ifdef ADC_CONVERSIONDATA_DR
  handle[instanceIndex].Init.ConversionDataManagement = ADC_CONVERSIONDATA_DR;      /* Regular Conversion data stored in DR register only */
#endif
#ifdef ADC_OVR_DATA_OVERWRITTEN
  handle[instanceIndex].Init.Overrun = ADC_OVR_DATA_OVERWRITTEN;
#endif
#ifdef ADC_LEFTBITSHIFT_NONE
  handle[instanceIndex].Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
#endif

#if defined(STM32F0)
  handle[instanceIndex].Init.SamplingTimeCommon = ADC_SAMPLINGTIME;
#endif
#if defined(STM32G0)
  handle[instanceIndex].Init.SamplingTimeCommon1   = ADC_SAMPLINGTIME;              /* Set sampling time common to a group of channels. */
  handle[instanceIndex].Init.SamplingTimeCommon2   = ADC_SAMPLINGTIME;              /* Set sampling time common to a group of channels, second common setting possible.*/
#endif
#if defined(STM32L0)
  handle[instanceIndex].Init.LowPowerFrequencyMode = DISABLE;                       /* To be enabled only if ADC clock < 2.8 MHz */
  handle[instanceIndex].Init.SamplingTime          = ADC_SAMPLINGTIME;
#endif
#if !defined(STM32F0) && !defined(STM32F1) && !defined(STM32F2) && \
    !defined(STM32F3) && !defined(STM32F4) && !defined(STM32F7) && \
    !defined(STM32L1) && !defined(GD32F10X) && !defined(GD32F20X)
  handle[instanceIndex].Init.OversamplingMode = DISABLE;
#endif
#if defined(ADC_CFGR_DFSDMCFG) && defined(DFSDM1_Channel0)
  handle[instanceIndex].Init.DFSDMConfig           = ADC_DFSDM_MODE_DISABLE;        /* ADC conversions are not transferred by DFSDM. */
#endif
#ifdef ADC_TRIGGER_FREQ_HIGH
  handle[instanceIndex].Init.TriggerFrequencyMode  = ADC_TRIGGER_FREQ_HIGH;
#endif

  handle[instanceIndex].State = HAL_ADC_STATE_RESET;
  handle[instanceIndex].DMA_Handle = NULL;
  handle[instanceIndex].Lock = HAL_UNLOCKED;

  HAL_StatusTypeDef error = HAL_ADC_Init(&handle[instanceIndex]);
  if (error != HAL_OK) {
    PRINT_ERROR("HAL_ADC_Init failed, error: %d", error);
    return 0;
  }

  ADC_ChannelConfTypeDef sConfig;
  sConfig.Channel = ch;
#if defined(STM32L4) || defined(STM32WB) || defined(STM32G4)
  if (!IS_ADC_CHANNEL(&handle[instanceIndex], ch)) {
#else
  if (!IS_ADC_CHANNEL(ch)) {
#endif /* STM32L4 || STM32WB ||STM32G4 */
	PRINT_ERROR("err channel");  
    return 0;
  }

#ifdef ADC_SCAN_SEQ_FIXED
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
#else
  sConfig.Rank = ADC_REGULAR_RANK_1;
#endif
#if !defined(STM32L0)
#if !defined(STM32G0)
  sConfig.SamplingTime = ADC_SAMPLINGTIME;                /* Sampling time value to be set for the selected channel */
#else
  sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;        /* Sampling time value to be set for the selected channel */
#endif
#endif


#if !defined(STM32F0) && !defined(STM32F1) && !defined(STM32F2) && \
    !defined(STM32F4) && !defined(STM32F7) && !defined(STM32G0) && \
    !defined(STM32L0) && !defined(STM32L1) && !defined(GD32F10X) && !defined(GD32F20X) &&\
    !defined(STM32F373xC) && !defined(STM32F378)
  sConfig.SingleDiff   = differentialMode;
  sConfig.OffsetNumber = ADC_OFFSET_NONE;
#endif
#if !defined(STM32F0) && !defined(STM32F1) && !defined(STM32F2) && \
    !defined(STM32G0) && !defined(STM32L0) && !defined(STM32L1) && !defined(GD32F10X) && !defined(GD32F20X) && \
    !defined(STM32WB) && !defined(STM32F373xC) && !defined(STM32F378)
  sConfig.Offset = 0;
#endif

#if defined (STM32H7) || defined(STM32MP1)
  sConfig.OffsetRightShift       = DISABLE;                    /* No Right Offset Shift */
  sConfig.OffsetSignedSaturation = DISABLE;                    /* No Signed Saturation */
#endif

  /*##-2- Configure ADC regular channel ######################################*/
  error = HAL_ADC_ConfigChannel(&handle[instanceIndex], &sConfig);
  if (error != HAL_OK) {
    PRINT_ERROR("HAL_ADC_ConfigChannel failed, error: %d", error);
    return 0;
  }
  
#if defined(STM32F0) || defined(STM32F1) || defined(STM32F3) || \
    defined(STM32G0) || defined(STM32G4) || defined(STM32H7) || \
    defined(STM32L0) || defined(STM32L4) || defined(STM32MP1) || \
    defined(STM32WB) || defined(GD32F10X) || defined(GD32F20X) 
  /*##-2.1- Calibrate ADC then Start the conversion process ####################*/
#if defined(STM32F0) || defined(STM32G0) || defined(STM32F1) || \
    defined(STM32F373xC) || defined(STM32F378) || defined(GD32F10X) || defined(GD32F20X)
  if (HAL_ADCEx_Calibration_Start(&handle[instanceIndex]) !=  HAL_OK)
#elif defined (STM32H7) || defined(STM32MP1)
  if (HAL_ADCEx_Calibration_Start(&handle[instanceIndex], ADC_CALIB_OFFSET, ADC_SINGLE_ENDED) != HAL_OK)
#else
  if (HAL_ADCEx_Calibration_Start(&handle[instanceIndex], ADC_SINGLE_ENDED) !=  HAL_OK)
#endif
  {
	PRINT_ERROR("err Calibration");  
    /* ADC Calibration Error */
    return 0;
  }
#endif

  /*##-3- Start the conversion process ####################*/
  error = HAL_ADC_Start(&handle[instanceIndex]);
  if (error != HAL_OK) {
    PRINT_ERROR("HAL_ADC_Start failed, error: %d", error);
    return 0;
  }

  /*##-4- Wait for the end of conversion #####################################*/
  /*  For simplicity reasons, this example is just waiting till the end of the
      conversion, but application may perform other tasks while conversion
      operation is ongoing. */
  error = HAL_ADC_PollForConversion(&handle[instanceIndex], 10);
  if (error != HAL_OK) {
    PRINT_ERROR("HAL_ADC_PollForConversion failed, error: %d", error);
    return 0;
  }

  /* Check if the continous conversion of regular channel is finished */
  if ((HAL_ADC_GetState(&handle[instanceIndex]) & HAL_ADC_STATE_REG_EOC) == HAL_ADC_STATE_REG_EOC) {
     ret = HAL_ADC_GetValue(&handle[instanceIndex]);
  }
  
  if ( HAL_ADC_Stop(&handle[instanceIndex]) != HAL_OK) {
	PRINT_ERROR("err stop");  
	return 0;
  }
  HAL_ADC_DeInit(&handle[instanceIndex]);
  LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(handle[instanceIndex].Instance), LL_ADC_PATH_INTERNAL_NONE);

  return ret;
}

#ifdef ADC_OFFSET_NONE  //F3/H7/L4
extern "C"
int analogReadChanelAve(ADC_TypeDef* ADCx, uint32_t ch, uint32_t differentialMode, uint8_t n)
{
  int rtn = analogReadChanel(ADCx, ch, differentialMode);
  rtn = 0;
  for (auto i = 0; i < n; i++) {
    rtn += analogReadChanel(ADCx, ch, differentialMode);
  }
  return rtn / n;
}
#else
extern "C"
int analogReadChanelAve(ADC_TypeDef* ADCx, uint32_t ch, uint8_t n)
{
  int rtn = analogReadChanel(ADCx, ch);
  rtn = 0;
  for (uint8_t i = 0; i < n; i++) {
    rtn += analogReadChanel(ADCx, ch);
  }
  return rtn / n;
}
#endif //ADC_OFFSET_NONE

extern "C"
int analogRead(uint8_t pin) {
#ifdef A0
  if (pin == 0) pin = A0;
#endif
#ifdef A1
  if (pin == 1) pin = A1;
#endif
#ifdef A2
  if (pin == 2) pin = A2;
#endif
#ifdef A3
  if (pin == 3) pin = A3;
#endif
#ifdef A4
  if (pin == 4) pin = A4;
#endif
#ifdef A5
  if (pin == 5) pin = A5;
#endif
#ifdef A6
  if (pin == 6) pin = A6;
#endif

  stm32_chip_adc1_channel_type config = stm32ADC1GetChannel(variant_pin_list[pin].port, variant_pin_list[pin].pinMask, 0);
  if (config.instance == NULL) {
	PRINT_ERROR("none instance");  
    return 0;
  }

  pinMode(pin, ANALOG);
#ifdef  ADC_OFFSET_NONE
  return analogReadChanel(config.instance, config.channel, ADC_SINGLE_ENDED) >> (MAX_RESOLUTION - readResolution);
#else
  return analogReadChanel(config.instance, config.channel) >> (MAX_RESOLUTION - readResolution);
#endif
}

#if 0  //def ADC_CHANNEL_VBAT
extern "C"
void ADC_EnableVbat(void) {
  /* Enable VBAT */
#if defined(ADC_CCR_VBATEN)
  ADC->CCR |= ADC_CCR_VBATEN;
#else
  ADC->CCR |= ADC_CCR_VBATE;
#endif
}

extern "C"
void ADC_DisableVbat(void) {
  /* Disable VBAT */
#if defined(ADC_CCR_VBATEN)
  ADC->CCR &= ~ADC_CCR_VBATEN;
#else
  ADC->CCR &= ~ADC_CCR_VBATE;
#endif
}
#endif

#ifdef ADC1
ADCClass adc;
#endif

//#endif //HAL_ADC_MODULE
