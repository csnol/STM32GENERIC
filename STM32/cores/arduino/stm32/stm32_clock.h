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
*/

/**
* Implementation of Arduino methods:
* millis() https://www.arduino.cc/en/Reference/Millis
* micros() https://www.arduino.cc/en/Reference/Micros
* delay() https://www.arduino.cc/en/Reference/Delay
* TODO delayMicroseconds() https://www.arduino.cc/en/Reference/DelayMicroseconds
*/
#ifndef STM32_CLOCK_H
#define STM32_CLOCK_H

#include "dwt.h"

#ifndef LOOP_PERCYCLE 
# if __CORTEX_M == 7
#   define  LOOP_PERCYCLE  1    /* F/H7*/
# elif defined(GD32F20X) || (__CORTEX_M == 0)
#   define  LOOP_PERCYCLE  9    /* 9 F0/L0/gd32f2/atsam4s */ 
# else
#   define  LOOP_PERCYCLE  6    /* 6 */
# endif
#endif 

#ifdef __cplusplus
extern "C"{
#endif

void yield(void);
void delay(unsigned long millis);
uint32_t micros();
void delayMicroseconds(uint32_t microseconds);
void stm32ScheduleMicros(uint32_t microseconds, void (*callback)());


static inline uint32_t millis() {
    return HAL_GetTick();
}

/*compatile with avr */
#if (__CORTEX_M == 0)
static inline void _delay_loop_2(uint32_t cnt){
  do{
	__asm__ volatile ("nop");
  }while(--cnt);
}

#else
/* 1~9 cycle */
static inline void _delay_loop_2(uint32_t cnt){
  __asm__ volatile (
	"1:   subs %0,  #1  \n"
    "     bne  1b       \n"
    :"+r" (cnt)             // '%0' is cnt variable with RW constraints
    :"0"  (cnt)             // '%0' is cnt variable
  ); 
  // https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html
  // https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html#Volatile
}
	
#endif

static inline void _delay_loop_us(uint32_t us){
	_delay_loop_2(((F_CPU/1000000)*us) / LOOP_PERCYCLE);
}

#ifdef __cplusplus
}
#endif

#define  _delay_loop_1(x) _delay_loop_2(x)
#define systicCallback  HAL_SYSTICK_Callback

#endif