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
  Copyright (c) 2019 STMicroelectronics
  Modified to support Arduino_Core_STM32
*/

#ifndef HARDWARETIMER_H_
#define HARDWARETIMER_H_

#include <Arduino.h>
#include "stm32_gpio_af.h"

#define  TIMER_CHANNELS 4  // channel5 and channel 6 are not considered here has they don't have gpio output and they don't have interrupt

typedef enum {
    //libmaple:                             // HAL compatible
    TIMER_DISABLED,
    TIMER_PWM,                              // == TIM_OCMODE_PWM1
    TIMER_OUTPUT_COMPARE,                   // == TIM_OCMODE_TIMING           no output, useful for only-interrupt

    //other:
    TIMER_OUTPUT_COMPARE_ACTIVE,            // == TIM_OCMODE_ACTIVE           pin is set high when counter == channel compare
    TIMER_OUTPUT_COMPARE_INACTIVE,          // == TIM_OCMODE_INACTIVE         pin is set low when counter == channel compare
    TIMER_OUTPUT_COMPARE_TOGGLE,            // == TIM_OCMODE_TOGGLE           pin toggles when counter == channel compare
    TIMER_OUTPUT_COMPARE_PWM1,              // == TIM_OCMODE_PWM1             pin high when counter < channel compare, low otherwise
    TIMER_OUTPUT_COMPARE_PWM2,              // == TIM_OCMODE_PWM2             pin low when counter < channel compare, high otherwise
    TIMER_OUTPUT_COMPARE_FORCED_ACTIVE,     // == TIM_OCMODE_FORCED_ACTIVE    pin always high
    TIMER_OUTPUT_COMPARE_FORCED_INACTIVE,   // == TIM_OCMODE_FORCED_INACTIVE  pin always low

    //Input capture
    TIMER_INPUT_CAPTURE_RISING,             // == TIM_INPUTCHANNELPOLARITY_RISING
    TIMER_INPUT_CAPTURE_FALLING,            // == TIM_INPUTCHANNELPOLARITY_FALLING
    TIMER_INPUT_CAPTURE_BOTHEDGE,           // == TIM_INPUTCHANNELPOLARITY_BOTHEDGE

//  Used 2 channels for a single pin. One channel in TIM_INPUTCHANNELPOLARITY_RISING another channel in TIM_INPUTCHANNELPOLARITY_FALLING.
//  Channels must be used by pair: CH1 with CH2, or CH3 with CH4
//  This mode is very useful for Frequency and Dutycycle measurement
//    TIMER_INPUT_CAPTURE_PWM,                // == TIM_INPUTCHANNELPOLARITY_RISING (channel 1) + TIM_INPUTCHANNELPOLARITY_FALLING (channel 2)
    TIMER_INPUT_FREQ_DUTY_MEASUREMENT,

    //Encoder mode
    TIMER_ENCODER,                            // == TIM_ENCODERMODE_TI1
	
    TIMER_NOT_USED = 0xFFFF  // This must be the last item of this enum
} TIMER_MODES;

typedef enum {
  TICK_FORMAT, // default
  MICROSEC_FORMAT,
  HERTZ_FORMAT,
} TimerFormat_t;

typedef enum {
  RESOLUTION_1B_COMPARE_FORMAT = 1,  // used for Dutycycle: [0 .. 1]
  RESOLUTION_2B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 3]
  RESOLUTION_3B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 7]
  RESOLUTION_4B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 15]
  RESOLUTION_5B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 31]
  RESOLUTION_6B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 63]
  RESOLUTION_7B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 127]
  RESOLUTION_8B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 255]
  RESOLUTION_9B_COMPARE_FORMAT,      // used for Dutycycle: [0 .. 511]
  RESOLUTION_10B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 1023]
  RESOLUTION_11B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 2047]
  RESOLUTION_12B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 4095]
  RESOLUTION_13B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 8191]
  RESOLUTION_14B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 16383]
  RESOLUTION_15B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 32767]
  RESOLUTION_16B_COMPARE_FORMAT,     // used for Dutycycle: [0 .. 65535]

  TICK_COMPARE_FORMAT = 0x80, // default
  MICROSEC_COMPARE_FORMAT,
  HERTZ_COMPARE_FORMAT,
  PERCENT_COMPARE_FORMAT,  // used for Dutycycle
} TimerCompareFormat_t;

#define TIMER_DEFAULT_PIN 0xFF

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"

class HardwareTimer {
public:
    HardwareTimer(TIM_TypeDef *instance, const stm32_tim_pin_list_type *pin_list , int pin_list_size = 0);
    ~HardwareTimer(){};  // destructor

    void pause(void);
    void resume(TIMER_MODES mode = TIMER_DISABLED,int channel = 0);

    uint32_t getPrescaleFactor();
    void setPrescaleFactor(uint32_t factor);

    uint32_t getOverflow();
    void setOverflow(uint32_t val);

    uint32_t getCount(void);
    void setCount(uint32_t val);

    uint32_t setPeriod(uint32_t microseconds);
    void setMode(int channel, TIMER_MODES mode, uint8_t pin = TIMER_DEFAULT_PIN);

    uint32_t getCompare(int channel);
    void setCompare(int channel, uint32_t compare);

    //Add interrupt to period update
    void attachInterrupt(void (*handler)(void));
    void detachInterrupt();

    //Add interrupt to channel
    void attachInterrupt(int channel, void (*handler)(void));
    void detachInterrupt(int channel);

    void refresh(void);

    uint32_t getBaseFrequency();

    TIM_HandleTypeDef handle = {0};

    TIM_OC_InitTypeDef channelOC[TIMER_CHANNELS];
    TIM_IC_InitTypeDef channelIC[TIMER_CHANNELS];
	
    //Callbacks: 0 for update, 1-4 for channels
    void (*callbacks[TIMER_CHANNELS+1])(void);

    const stm32_tim_pin_list_type *tim_pin_list;

    int tim_pin_list_size;

private:
    int  getChannel(int channel);
    void resumeChannel(int channel);
    void resumePwm(int channel);
    void resumeEncoder(void);
};

#pragma GCC diagnostic pop

#ifdef TIM1_BASE
    extern HardwareTimer Timer1;
#endif

#ifdef TIM2_BASE
    extern HardwareTimer Timer2;
#endif

#ifdef TIM3_BASE
    extern HardwareTimer Timer3;
#endif

#ifdef TIM4_BASE
    extern HardwareTimer Timer4;
#endif

#ifdef TIM5_BASE
    extern HardwareTimer Timer5;
#endif

#ifdef TIM8_BASE
    extern HardwareTimer Timer8;
#endif

//F2/4/7 H7 L1
#ifdef TIM9_BASE
    extern HardwareTimer Timer9;
#endif
#ifdef TIM10_BASE
    extern HardwareTimer Timer10;
#endif
#ifdef TIM11_BASE
# if  (FREERTOS == 0) || (portTickUSE_TIMx != 11) 
    extern HardwareTimer Timer11;
# endif
#elif defined(TIM21)	/*L0 only*/
    extern HardwareTimer Timer21;
#endif
#ifdef TIM12_BASE
    extern HardwareTimer Timer12;
#elif defined(TIM22)	/*L0 only*/
    extern HardwareTimer Timer22;
#endif
#ifdef TIM13_BASE
    extern HardwareTimer Timer13;
#endif
#ifdef TIM14_BASE
    extern HardwareTimer Timer14;
#endif

// F0/3 L4 H7
#ifdef TIM15_BASE
    extern HardwareTimer Timer15;
#endif
#ifdef TIM16_BASE
    extern HardwareTimer Timer16;
#endif
#ifdef TIM17_BASE
# if  (FREERTOS == 0) || (portTickUSE_TIMx != 17) 
    extern HardwareTimer Timer17;
# endif
#endif

#endif //HARDWARETIMER_H_
