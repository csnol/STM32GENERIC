/*
  Copyright (c) 2017 Daniel Fekete

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

  2018.1.8  change SerialUART to HardwareSerial comptatible with arduino stl libs 
            and some apps modified by huaweiwx@sina.com
  2018.7.22 Thanks csnol!  modifyed begin(baud) to begin(baud, config) parm config(optional)
            comptatible with arduino official implementation. by huaweiwx@sina.com
  2018.10.7 fixed: error data may be returned from available() 
;
*/

/**
   TODO: Check if txBuffer is NULL in every method
   TODO: generate different TX/RX_BUFFER_SIZE values for different boards based on available memory
   TODO: add alternate pin selection functions
   TODO: add constructor with custom buffer parameter
*/
#include "Arduino.h"
//#include "HardwareSerial.h"
#include "stm32_gpio_af.h"

#if defined(USART3_BASE) && !defined(USART3_IRQn)
# if defined(STM32F0 ) || defined(GD32F1x0)
#  if defined(STM32F091xC) || defined (STM32F098xx)
#    define USART3_IRQn USART3_8_IRQn
#    define USART3_IRQHandler USART3_8_IRQHandler
#  elif defined(STM32F030xC)
#    define USART3_IRQn USART3_6_IRQn
#    define USART3_IRQHandler USART3_6_IRQHandler
#  else
#    define USART3_IRQn USART3_4_IRQn
#    define USART3_IRQHandler USART3_4_IRQHandler
#  endif /* STM32F091xC || STM32F098xx */
#endif /* STM32F0 */

#if defined(STM32G0)
#define USART3_IRQn       USART3_4_LPUART1_IRQn
#define USART3_IRQHandler USART3_4_LPUART1_IRQHandler
#endif /* STM32G0xx */
#endif

#if defined(USART4_BASE) && !defined(USART4_IRQn)
# if defined(STM32F0) || defined(GD32F1x0)
/* IRQHandler is mapped on USART3_IRQHandler for STM32F0xx */
#   if defined(STM32F091xC) || defined (STM32F098xx)
#     define USART4_IRQn USART3_8_IRQn
#   elif defined(STM32F030xC)
#     define USART4_IRQn USART3_6_IRQn
#   else
#     define USART4_IRQn USART3_4_IRQn
#   endif /* STM32F091xC || STM32F098xx */
# elif defined(STM32L0)
#   define USART4_IRQn USART4_5_IRQn
# endif /* STM32F0 */
# if defined(STM32G0)
#   define USART4_IRQn USART3_4_LPUART1_IRQn
# endif /* STM32G0xx */
#endif

#if defined(USART5_BASE) && !defined(USART5_IRQn)
#if defined(STM32F0) || defined(GD32F1x0)
/* IRQHandler is mapped on USART3_IRQHandler for STM32F0xx */
#if defined(STM32F091xC) || defined (STM32F098xx)
#define USART5_IRQn USART3_8_IRQn
#elif defined(STM32F030xC)
#define USART5_IRQn USART3_6_IRQn
#endif /* STM32F091xC || STM32F098xx */
#elif defined(STM32L0)
#define USART5_IRQn USART4_5_IRQn
#endif /* STM32F0 */
#endif

#if defined (STM32F0) || defined(GD32F1x0)
/* IRQHandler is mapped on USART3_IRQHandler for STM32F0xx */
#if defined(USART6_BASE) && !defined(USART6_IRQn)
#if defined(STM32F091xC) || defined (STM32F098xx)
#define USART6_IRQn USART3_8_IRQn
#elif defined(STM32F030xC)
#define USART6_IRQn USART3_6_IRQn
#endif /* STM32F091xC || STM32F098xx */
#endif

#if defined(USART7_BASE) && !defined(USART7_IRQn)
#if defined(STM32F091xC) || defined (STM32F098xx)
#define USART7_IRQn USART3_8_IRQn
#endif /* STM32F091xC || STM32F098xx */
#endif

#if defined(USART8_BASE) && !defined(USART8_IRQn)
#if defined(STM32F091xC) || defined (STM32F098xx)
#define USART8_IRQn USART3_8_IRQn
#endif /* STM32F091xC || STM32F098xx */
#endif
#endif /* STM32F0xx */

#if defined(STM32G0)
#if defined(LPUART1_BASE) && !defined(LPUART1_IRQn)
#define LPUART1_IRQn USART3_4_LPUART1_IRQn
#endif
#endif /* STM32G0xx */

#if defined(USART1) && (USE_SERIAL1)
static HardwareSerial* interruptUART1  = NULL;
#endif
#if defined(USART2) && (USE_SERIAL2)
static HardwareSerial* interruptUART2  = NULL;
#endif
#if defined(USART3) && (USE_SERIAL3)
static HardwareSerial* interruptUART3  = NULL;
#endif
#if ((defined UART4) || (defined USART4)) && (USE_SERIAL4) 
static HardwareSerial* interruptUART4  = NULL;
#endif
#if ((defined UART5) || (defined USART5)) && (USE_SERIAL5) 
static HardwareSerial* interruptUART5  = NULL;
#endif
#if defined(USART6) && (USE_SERIAL6)
static HardwareSerial *interruptUART6  = NULL;
#endif
#if ((defined UART7) || (defined USART7)) && (USE_SERIAL7) 
static HardwareSerial *interruptUART7  = NULL;
#endif
#if ((defined UART8) || (defined USART8)) && (USE_SERIAL8) 
static HardwareSerial *interruptUART8  = NULL;
#endif
#if (defined UART9) && (USE_SERIAL9) 
static HardwareSerial *interruptUART9  = NULL;
#endif
#if (defined UART10) && (USE_SERIAL10)
static HardwareSerial *interruptUART10  = NULL;
#endif
#if (defined LPUART1) && (USE_LPUART1)
static HardwareSerial *interruptLPUART1 = NULL;
#endif

#pragma GCC diagnostic ignored "-Wunused-parameter"
/**
   Set the underlying UART instance.
*/
HardwareSerial::HardwareSerial(USART_TypeDef *instance) {
  this->instance = instance;
}

/**
   Arduino always instantiates the Serial object.

   To save memory, this implementation will:
   - not use any memory if begin() is never called
   - use statically allocated memory, if begin() is called exactly in one HardwareSerials.
   - use statically allocated memory for the first, and malloc() for any subsequent calls to begin() on DIFFERENT HardwareSerials.
*/

void HardwareSerial::begin(const uint32_t baud, uint8_t config) {
  if (txBuffer == NULL) {
    static uint8_t tx[TX_BUFFER_SIZE];
    static uint8_t static_tx_used = 0;

    if (!static_tx_used) {
      txBuffer = (uint8_t*)tx;
      static_tx_used = true;
    } else {
      txBuffer = (uint8_t*)malloc(TX_BUFFER_SIZE);
    }
  }

  if (rxBuffer == NULL) {
    static uint8_t rx[RX_BUFFER_SIZE];
    static uint8_t static_rx_used = 0;

    if (!static_rx_used) {
      rxBuffer = (uint8_t*)rx;
      static_rx_used = true;
    } else {
      rxBuffer = (uint8_t*)malloc(RX_BUFFER_SIZE);
    }
  }

  if (handle == NULL) {
    static UART_HandleTypeDef h = {};
    static uint8_t static_handle_used = 0;

    if (!static_handle_used) {
      handle = &h;
      static_handle_used = true;
    } else {
      handle = (UART_HandleTypeDef*)malloc(sizeof(UART_HandleTypeDef));
    }
  }

  handle->Instance = instance;

#if defined(USART1) && (USE_SERIAL1)
  if (handle->Instance == USART1) {
    __HAL_RCC_USART1_FORCE_RESET();
    __HAL_RCC_USART1_RELEASE_RESET();
    __HAL_RCC_USART1_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART1_IRQn, USART_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
	interruptUART1 = this;
  }
#endif

#if defined(USART2) && (USE_SERIAL2)
  if (handle->Instance == USART2) {
    __HAL_RCC_USART2_FORCE_RESET();
    __HAL_RCC_USART2_RELEASE_RESET();
    __HAL_RCC_USART2_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART2_IRQn, USART_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
	interruptUART2 = this;
  }
#endif

#if defined(USART3) && (USE_SERIAL3)
  if (handle->Instance == USART3) {
    __HAL_RCC_USART3_FORCE_RESET();
    __HAL_RCC_USART3_RELEASE_RESET();
    __HAL_RCC_USART3_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART3_IRQn, USART_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(USART3_IRQn);
	interruptUART3 = this;
  }
#endif

#if defined(UART4) && (USE_SERIAL4)
  if (handle->Instance == UART4) {
    __HAL_RCC_UART4_FORCE_RESET();
    __HAL_RCC_UART4_RELEASE_RESET();
    __HAL_RCC_UART4_CLK_ENABLE();
    HAL_NVIC_SetPriority(UART4_IRQn, USART_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(UART4_IRQn);
	interruptUART4 = this;
  }
#endif
#if defined(USART4) && (USE_SERIAL4)
  if (handle->Instance == USART4) {
    __HAL_RCC_USART4_FORCE_RESET();
    __HAL_RCC_USART4_RELEASE_RESET();
    __HAL_RCC_USART4_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART4_IRQn, USART_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(USART4_IRQn);
 	interruptUART4 = this;
 }
#endif

#if defined(UART5) && (USE_SERIAL5)
  if (handle->Instance == UART5) {
    __HAL_RCC_UART5_FORCE_RESET();
    __HAL_RCC_UART5_RELEASE_RESET();
    __HAL_RCC_UART5_CLK_ENABLE();
    HAL_NVIC_SetPriority(UART5_IRQn, USART_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(UART5_IRQn);
	interruptUART5 = this;
  }
#endif
#if defined(USART5) && (USE_SERIAL5)
  if (handle->Instance == USART5) {
    __HAL_RCC_USART5_FORCE_RESET();
    __HAL_RCC_USART5_RELEASE_RESET();
    __HAL_RCC_USART5_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART5_IRQn, USART_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(USART5_IRQn);
	interruptUART6 = this;
  }
#endif

#if defined(USART6) && (USE_SERIAL6)
  if (handle->Instance == USART6) {
    __HAL_RCC_USART6_FORCE_RESET();
    __HAL_RCC_USART6_RELEASE_RESET();
    __HAL_RCC_USART6_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART6_IRQn, USART_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(USART6_IRQn);
	interruptUART6 = this;
  }
#endif
#if defined(UART7) && (USE_SERIAL7)
  if (handle->Instance == UART7) {
    __HAL_RCC_UART7_FORCE_RESET();
    __HAL_RCC_UART7_RELEASE_RESET();
    __HAL_RCC_UART7_CLK_ENABLE();
    HAL_NVIC_SetPriority(UART7_IRQn, USART_PRIORITY, 0);
	interruptUART7 = this;
  }
#endif
#if defined(USART7) && (USE_SERIAL7)
  if (handle->Instance == USART7) {
    __HAL_RCC_USART7_FORCE_RESET();
    __HAL_RCC_USART7_RELEASE_RESET();
    __HAL_RCC_USART7_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART7_IRQn, USART_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(USART7_IRQn);
	interruptUART7 = this;
  }
#endif
#if defined(UART8) && (USE_SERIAL8)
  if (handle->Instance == UART8) {
    __HAL_RCC_UART8_FORCE_RESET();
    __HAL_RCC_UART8_RELEASE_RESET();
    __HAL_RCC_UART8_CLK_ENABLE();
    HAL_NVIC_SetPriority(UART8_IRQn, USART_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(UART8_IRQn);
	interruptUART8 = this;
  }
#endif
#if defined(USART8) && (USE_SERIAL8)
  if (handle->Instance == USART8) {
    __HAL_RCC_USART8_FORCE_RESET();
    __HAL_RCC_USART8_RELEASE_RESET();
    __HAL_RCC_USART8_CLK_ENABLE();
    HAL_NVIC_SetPriority(USART8_IRQn, USART_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(USART8_IRQn);
 	interruptUART8 = this;
 }
#endif
#if defined(UART9) && (USE_SERIAL9)
  if (handle->Instance == UART9) {
    __HAL_RCC_UART9_FORCE_RESET();
    __HAL_RCC_UART9_RELEASE_RESET();
    __HAL_RCC_UART9_CLK_ENABLE();
    HAL_NVIC_SetPriority(UART9_IRQn, USART_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(UART9_IRQn);
	interruptUART9 = this;
  }
#endif
#if defined(UART10) && (USE_SERIAL10)
  if (handle->Instance == UART10) {
    __HAL_RCC_UART10_FORCE_RESET();
    __HAL_RCC_UART10_RELEASE_RESET();
    __HAL_RCC_UART10_CLK_ENABLE();
    HAL_NVIC_SetPriority(UART10_IRQn, USART_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(UART10_IRQn);
	interruptUART10 = this;
  }
#endif
#if defined(LPUART1) && (USE_LPUART1)
  if (handle->Instance == LPUART1) {
    __HAL_RCC_LPUART1_FORCE_RESET();
    __HAL_RCC_LPUART1_RELEASE_RESET();
    __HAL_RCC_LPUART1_CLK_ENABLE();
    HAL_NVIC_SetPriority(LPUART1_IRQn, USART_PRIORITY, 0);
    HAL_NVIC_EnableIRQ(LPUART1_IRQn);
    interruptLPUART1 = this;
   
    if ((txPin < 0xff) && (rxPin < 0xff))
      stm32AfLPUARTInit(instance,
                        variant_pin_list[rxPin].port,
                        variant_pin_list[rxPin].pinMask,
                        variant_pin_list[txPin].port,
                        variant_pin_list[txPin].pinMask);
    else
      stm32AfLPUARTInit(instance, NULL, 0, NULL, 0);

  }
  else if ((txPin < 0xff) && (rxPin < 0xff))
    stm32AfUARTInit(instance,
                    variant_pin_list[rxPin].port,
                    variant_pin_list[rxPin].pinMask,
                    variant_pin_list[txPin].port,
                    variant_pin_list[txPin].pinMask);
  else
    stm32AfUARTInit(instance, NULL, 0, NULL, 0);

#else
  if ((txPin < 0xff) && (rxPin < 0xff))
    stm32AfUARTInit(instance,
                    variant_pin_list[rxPin].port,
                    variant_pin_list[rxPin].pinMask,
                    variant_pin_list[txPin].port,
                    variant_pin_list[txPin].pinMask);
  else
    stm32AfUARTInit(instance, NULL, 0, NULL, 0);
#endif

/*from Arduino_Core*/
  uint32_t databits = 0;
  _config = config;
 switch (config & 0x07) {
    //    case 0x02:
    //      databits = 6;
    //      break;
    case 0x04:
      databits = 7;
      break;
    case 0x06:
      databits = 8;
      break;
    default:
      databits = 0;
      break;
  }
  if ((config & 0x30) == 0x30) {
    handle->Init.Parity = UART_PARITY_ODD;
    databits++;
  } else if ((config & 0x20) == 0x20) {
    handle->Init.Parity = UART_PARITY_EVEN;
    databits++;
  } else {
    handle->Init.Parity = UART_PARITY_NONE;
  }
  if ((config & 0x08) == 0x08) {
    handle->Init.StopBits = UART_STOPBITS_2;
  } else {
    handle->Init.StopBits = UART_STOPBITS_1;
  }
  handle->Init.BaudRate = baud;
  switch (databits) {
#ifdef UART_WORDLENGTH_7B
    case 7:
      handle->Init.WordLength = UART_WORDLENGTH_7B;
      break;
#endif
    case 8:
      handle->Init.WordLength = UART_WORDLENGTH_8B;
      break;
    case 9:
      handle->Init.WordLength = UART_WORDLENGTH_9B;
      break;
    default:
      databits = 0;
      break;
  }
/*from Arduino_Core*/


  handle->Init.Mode = UART_MODE_TX_RX;
  handle->Init.HwFlowCtl = UART_HWCONTROL_NONE;

#if defined(LPUART1) && (USE_LPUART1) // && defined(STM32L4)
  if (handle->Instance == LPUART1) {
    handle->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    handle->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
# if defined(USART_PRESC_PRESCALER)  /* L4R5/7 */
    handle->Init.ClockPrescaler = UART_PRESCALER_DIV1;
    handle->FifoMode = UART_FIFOMODE_DISABLE;
# endif

    if (handle->Init.BaudRate <= 9600) {
# ifdef STM32L0
      HAL_UARTEx_EnableClockStopMode(handle);
# endif
      HAL_UARTEx_EnableStopMode(handle);
    } else {
# ifdef STM32L0
      HAL_UARTEx_DisableClockStopMode(handle);
# endif
      HAL_UARTEx_DisableStopMode(handle);
    }
  }
  
  HAL_UART_Init(handle);
# if defined(USART_CR1_FIFOEN) /* L4R5/7 */
  HAL_UARTEx_SetTxFifoThreshold(handle, UART_TXFIFO_THRESHOLD_1_8);
  HAL_UARTEx_SetRxFifoThreshold(handle, UART_RXFIFO_THRESHOLD_1_8);
# endif

#else
  handle->Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(handle);
#endif

  HAL_UART_Receive_IT(handle, &receive_buffer, 1);
}


#if defined(HAL_PWR_MODULE_ENABLED) && defined(UART_IT_WUF)
extern "C" {
  void Lowpower_uartConfig(UART_HandleTypeDef *handle) __weak;
  void Lowpower_uartConfig(UART_HandleTypeDef *handle) { }
}
#endif
/**
    @brief  Function called to configure the uart interface for low power
    @param  obj : pointer to serial_t structure
    @retval None
*/
void HardwareSerial::configForLowPower(void)
{
#if defined(HAL_PWR_MODULE_ENABLED) && defined(UART_IT_WUF)
  end();
  Lowpower_uartConfig(handle);
  this->begin(handle->Init.BaudRate,_config);
#endif
}

void HardwareSerial::end(void) {
  flush();
#if defined(USART1) && (USE_SERIAL1)
  if (handle->Instance == USART1) {
    HAL_NVIC_DisableIRQ(USART1_IRQn);
    __HAL_RCC_USART1_CLK_DISABLE();
  }
#endif

#if defined(USART2) && (USE_SERIAL2)
  if (handle->Instance == USART2) {
    HAL_NVIC_DisableIRQ(USART2_IRQn);
    __HAL_RCC_USART2_CLK_DISABLE();
  }
#endif

#if defined(USART3) && (USE_SERIAL3)
  if (handle->Instance == USART3) {
    HAL_NVIC_DisableIRQ(USART3_IRQn);
    __HAL_RCC_USART3_CLK_DISABLE();
  }
#endif

#if defined(UART4) && (USE_SERIAL4)
  if (handle->Instance == UART4) {
    HAL_NVIC_DisableIRQ(UART4_IRQn);
    __HAL_RCC_UART4_CLK_DISABLE();
  }
#endif
#if defined(USART4) && (USE_SERIAL4)
  if (handle->Instance == USART4) {
    HAL_NVIC_DisableIRQ(USART4_IRQn);
    __HAL_RCC_USART4_CLK_DISABLE();
  }
#endif

#if defined(UART5) && (USE_SERIAL5)
  if (handle->Instance == UART5) {
    HAL_NVIC_DisableIRQ(UART5_IRQn);
    __HAL_RCC_UART5_CLK_DISABLE();
  }
#endif
#if defined(USART5) && (USE_SERIAL5)
  if (handle->Instance == USART5) {
    HAL_NVIC_DisableIRQ(USART5_IRQn);
    __HAL_RCC_USART5_CLK_DISABLE();
  }
#endif

#if defined(USART6) && (USE_SERIAL6)
  if (handle->Instance == USART6) {
    HAL_NVIC_DisableIRQ(USART6_IRQn);
    __HAL_RCC_USART6_CLK_DISABLE();
  }
#endif

#if defined(UART7) && (USE_SERIAL7)
  if (handle->Instance == UART7) {
    HAL_NVIC_DisableIRQ(UART7_IRQn);
    __HAL_RCC_UART7_CLK_DISABLE();
  }
#endif
#if defined(USART7) && (USE_SERIAL7)
  if (handle->Instance == USART7) {
    HAL_NVIC_DisableIRQ(USART7_IRQn);
    __HAL_RCC_USART7_CLK_DISABLE();
  }
#endif
#if defined(UART8) && (USE_SERIAL8)
  if (handle->Instance == UART8) {
    HAL_NVIC_DisableIRQ(UART8_IRQn);
    __HAL_RCC_UART8_CLK_DISABLE();
  }
#endif
#if defined(USART8) && (USE_SERIAL8)
  if (handle->Instance == USART8) {
    HAL_NVIC_DisableIRQ(USART8_IRQn);
    __HAL_RCC_USART8_CLK_DISABLE();
  }
#endif
#if defined(UART9) && (USE_SERIAL9)
  if (handle->Instance == UART9) {
    HAL_NVIC_DisableIRQ(UART9_IRQn);
    __HAL_RCC_UART9_CLK_DISABLE();
  }
#endif
#if defined(UART10) && (USE_SERIAL10)
  if (handle->Instance == UART10) {
    HAL_NVIC_DisableIRQ(UART10_IRQn);
    __HAL_RCC_UART10_CLK_DISABLE();
  }
#endif

#if defined(LPUART1) && (USE_LPUART1)
  if (handle->Instance == LPUART1) {
    HAL_NVIC_DisableIRQ(LPUART1_IRQn);
    __HAL_RCC_LPUART1_CLK_DISABLE();
  }
#endif
}

int HardwareSerial::available() {
  return ((unsigned int) (RX_BUFFER_SIZE + rxEnd - rxStart)) % RX_BUFFER_SIZE;
}

int HardwareSerial::availableForWrite() {
  return txEnd != txStart;
}

int HardwareSerial::peek() {
  if (available()) {
    return rxBuffer[rxStart];
  } else {
    return -1;
  }
}

void HardwareSerial::flush() {
  while (txEnd != txStart);
}

int HardwareSerial::read() {
  if (available()) {
    uint8_t uc = rxBuffer[rxStart];
	rxStart = (rxStart + 1) % RX_BUFFER_SIZE;
    return uc;
  } else {
    return -1;
  }
}

size_t HardwareSerial::write(const uint8_t c) {
#if defined(USE_FULL_ASSERT) || defined(PROTEUS)
   HAL_UART_Transmit(handle, (uint8_t*)&c, 1,100); /*use polling mode for debug / proteus */
#else
   while ((txEnd + 1) % TX_BUFFER_SIZE == txStart);

   txBuffer[txEnd] = c;
   txEnd = (txEnd + 1) % TX_BUFFER_SIZE;
   if (txEnd == (txStart + 1) % TX_BUFFER_SIZE) {
      HAL_UART_Transmit_IT(handle, &txBuffer[txStart], 1);
   } 
#endif
   return 1;
}

void HardwareSerial::stm32SetRX(uint8_t rx) {
  rxPin = rx;
}

void HardwareSerial::stm32SetTX(uint8_t tx) {
  txPin = tx;
}

void HardwareSerial::setPins(uint8_t tx, uint8_t rx) {
  txPin = tx;
  rxPin = rx;
}
//// Interrupt


#if defined(USART1) &&(USE_SERIAL1)
extern "C" void USART1_IRQHandler(void) {
  if(interruptUART1) HAL_UART_IRQHandler(interruptUART1->handle);
}
HardwareSerial SerialUART1(USART1);
#endif

#if defined(USART2) && (USE_SERIAL2)
extern "C" void USART2_IRQHandler(void) {
  if(interruptUART2) HAL_UART_IRQHandler(interruptUART2->handle);
}
HardwareSerial SerialUART2(USART2);
#endif

#if defined(USART3) && (USE_SERIAL3)
extern "C" void USART3_IRQHandler(void) {
# if defined(STM32F091xC) || defined (STM32F098xx)
  if(interruptUART3) HAL_UART_IRQHandler(interruptUART3->handle);
#	if defined(USART4) && (USE_SERIAL4)
  if(interruptUART4) HAL_UART_IRQHandler(interruptUART4->handle);
#	endif  
#	if defined(USART5) && (USE_SERIAL5)
  if(interruptUART5) HAL_UART_IRQHandler(interruptUART5->handle);
#	endif  
#	if defined(USART6) && (USE_SERIAL6)
  if(interruptUART6) HAL_UART_IRQHandler(interruptUART6->handle);
#	endif  
#	if defined(USART7) && (USE_SERIAL7)
  if(interruptUART7) HAL_UART_IRQHandler(interruptUART7->handle);
#	endif  
#	if defined(USART8) && (USE_SERIAL8)
  if(interruptUART8) HAL_UART_IRQHandler(interruptUART8->handle);
#	endif   
#else
  if(interruptUART3) HAL_UART_IRQHandler(interruptUART3->handle);
# if defined(STM32F0) || defined(GD32F1x0)
#	if defined(UART4) && (USE_SERIAL4)
  if(interruptUART4) HAL_UART_IRQHandler(interruptUART4->handle);
#		if defined(STM32F030xC)
#	       if defined(USART5) && (USE_SERIAL5)
  if(interruptUART5) HAL_UART_IRQHandler(interruptUART5->handle);
#	       endif  
#	       if defined(USART6) && (USE_SERIAL6)
  if(interruptUART6) HAL_UART_IRQHandler(interruptUART6->handle);
#	       endif  
#		endif  
#	endif  
# endif
#endif
}
HardwareSerial SerialUART3(USART3);
#endif

#if defined(UART4) && (USE_SERIAL4)
extern "C" void UART4_IRQHandler(void) {
  if(interruptUART4) HAL_UART_IRQHandler(interruptUART4->handle);
}
HardwareSerial SerialUART4(UART4);
#endif //UART4

#if defined(STM32L0)
# if (defined(USART4) && (USE_SERIAL4)) || (defined(USART5) && (USE_SERIAL5))
extern "C" void USART4_5_IRQHandler(void)
{
#   if defined(USART4) && (USE_SERIAL4)
  if(interruptUART4) HAL_UART_IRQHandler(interruptUART4->handle);
#   endif
#   if defined(USART5) && (USE_SERIAL5)
  if(interruptUART5) HAL_UART_IRQHandler(interruptUART5->handle);
#   endif
}
# endif

#else

# ifdef USART4
#   if (USE_SERIAL4)
extern "C" void USART4_IRQHandler(void) {
  if(interruptUART4) HAL_UART_IRQHandler(interruptUART4->handle);
}
HardwareSerial SerialUART4(USART4);
#   endif
# endif

# ifdef UART5
#   if (USE_SERIAL5)
extern "C" void UART5_IRQHandler(void) {
  if(interruptUART5) HAL_UART_IRQHandler(interruptUART5->handle);
}
HardwareSerial SerialUART5(UART5);
#   endif
# endif
# ifdef USART5
#   if (USE_SERIAL5)
extern "C" void USART5_IRQHandler(void) {
  if(interruptUART6) HAL_UART_IRQHandler(interruptUART6->handle);
}
HardwareSerial SerialUART5(USART5);
#   endif
# endif

#endif //STM32L0

#if (defined USART6)  && !defined(STM32F0)  && !defined(GD32F1x0)
#if (USE_SERIAL6)
extern "C" void USART6_IRQHandler(void) {
  if(interruptUART6) HAL_UART_IRQHandler(interruptUART6->handle);
}
HardwareSerial SerialUART6(USART6);
#endif
#endif

#ifdef UART7
#if (USE_SERIAL7)
extern "C" void UART7_IRQHandler(void) {
  if(interruptUART7) HAL_UART_IRQHandler(interruptUART7->handle);
}
HardwareSerial SerialUART7(UART7);
#endif
#endif

#ifdef USART7
#if (USE_SERIAL7)
extern "C" void USART7_IRQHandler(void) {
  if(interruptUART7) HAL_UART_IRQHandler(interruptUART7->handle);
}
HardwareSerial SerialUART7(USART7);
#endif
#endif
#ifdef UART8
#if (USE_SERIAL8)
extern "C" void UART8_IRQHandler(void) {
  if(interruptUART8) HAL_UART_IRQHandler(interruptUART8->handle);
}
HardwareSerial SerialUART8(UART8);
#endif
#endif
#ifdef USART8
#if (USE_SERIAL8)
extern "C" void USART8_IRQHandler(void) {
  if(interruptUART8) HAL_UART_IRQHandler(interruptUART8->handle);
}
HardwareSerial SerialUART8(USART8);
#endif
#endif

#ifdef UART9
#if (USE_SERIAL9)
extern "C" void UART9_IRQHandler(void) {
  if(interruptUART9) HAL_UART_IRQHandler(interruptUART9->handle);
}
HardwareSerial SerialUART9(UART9);
#endif
#endif

#ifdef UART10
#if (USE_SERIAL10)
extern "C" void UART10_IRQHandler(void) {
  if(interruptUART10) HAL_UART_IRQHandler(interruptUART10->handle);
}
HardwareSerial SerialUART10(UART10);
#endif
#endif

#ifdef LPUART1
#if (USE_LPUART1)
extern "C" void LPUART1_IRQHandler(void) {
  if(interruptLPUART1) HAL_UART_IRQHandler(interruptLPUART1->handle);
}
HardwareSerial SerialLPUART1(LPUART1);
#endif
#endif


static HardwareSerial* getObj(UART_HandleTypeDef *huart){
	HardwareSerial* rtn = interruptUART1;

	if(huart->Instance == USART1) rtn = interruptUART1;
#if defined(USART2) && (USE_SERIAL2)
	else if (huart->Instance == USART2)   rtn = interruptUART2;
#endif
#if defined(USART3) && (USE_SERIAL3)
	else if (huart->Instance == USART3)   rtn = interruptUART3;
#endif
#if (defined UART4) && (USE_SERIAL4)
	else if (huart->Instance == UART4)    rtn = interruptUART4;
#endif
#if  (defined USART4) && (USE_SERIAL4)
	else if (huart->Instance == USART4)   rtn = interruptUART4;
#endif
#if (defined UART5) && (USE_SERIAL5)
	else if (huart->Instance == UART5)    rtn = interruptUART5;
#endif
#if (defined USART5) && (USE_SERIAL5)
	else if (huart->Instance == USART5)   rtn = interruptUART5;
#endif
#if defined(USART6) && (USE_SERIAL6)
	else if (huart->Instance == USART6)   rtn = interruptUART6;
#endif
#if (defined UART7) && (USE_SERIAL7)
	else if (huart->Instance == UART7)    rtn = interruptUART7;
#endif
#if (defined USART7) && (USE_SERIAL7)
	else if (huart->Instance == USART7)   rtn = interruptUART7;
#endif
#if (defined UART8) && (USE_SERIAL8)
	else if (huart->Instance == UART8)    rtn = interruptUART8;
#endif
#if (defined USART8) && (USE_SERIAL8)
	else if (huart->Instance == USART8)   rtn = interruptUART8;
#endif
#if (defined UART9) && (USE_SERIAL9)
	else if (huart->Instance == UART9)    rtn = interruptUART9;
#endif
#if (defined UART10)  && (USE_SERIAL10)
	else if (huart->Instance == UART10)  rtn = interruptUART10;
#endif
#if (defined LPUART1) && (USE_LPUART1)
	else if (huart->Instance == LPUART1) rtn = interruptLPUART1;
#endif
    return rtn;
 }
 
extern "C" void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
  HardwareSerial* _m_serial  = getObj(huart);
  _m_serial->txStart = (_m_serial->txStart+1) % TX_BUFFER_SIZE;
  if (_m_serial->txStart != _m_serial->txEnd) {
    HAL_UART_Transmit_IT(_m_serial->handle, &_m_serial->txBuffer[_m_serial->txStart], 1);
  }
}

extern "C" void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
  HardwareSerial* _m_serial  = getObj(huart);
  _m_serial->rxBuffer[_m_serial->rxEnd % RX_BUFFER_SIZE] = _m_serial->receive_buffer;
  _m_serial->rxEnd = (_m_serial->rxEnd + 1) % RX_BUFFER_SIZE;
  HAL_UART_Receive_IT(_m_serial->handle, &_m_serial->receive_buffer, 1);
}


extern "C" void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  uint32_t tmpval;
#if defined(STM32F1)||defined(GD32F10X)||defined(GD32F20X) || defined(STM32F2) || defined(STM32F4) || defined(STM32L1)

  if (__HAL_UART_GET_FLAG(huart, UART_FLAG_PE) != RESET) {
    tmpval = huart->Instance->DR; /* Clear PE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_FE) != RESET) {
    tmpval = huart->Instance->DR; /* Clear FE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_NE) != RESET) {
    tmpval = huart->Instance->DR; /* Clear NE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE) != RESET) {
    tmpval = huart->Instance->DR; /* Clear ORE flag */
  }
#else
  if (__HAL_UART_GET_FLAG(huart, UART_FLAG_PE) != RESET) {
    tmpval = huart->Instance->RDR; /* Clear PE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_FE) != RESET) {
    tmpval = huart->Instance->RDR; /* Clear FE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_NE) != RESET) {
    tmpval = huart->Instance->RDR; /* Clear NE flag */
  } else if (__HAL_UART_GET_FLAG(huart, UART_FLAG_ORE) != RESET) {
    tmpval = huart->Instance->RDR; /* Clear ORE flag */
  }
#endif
  UNUSED(tmpval);
}

extern "C" void HAL_UARTEx_WakeupCallback(UART_HandleTypeDef *huart)
{
  HAL_UART_RxCpltCallback(huart);
}
