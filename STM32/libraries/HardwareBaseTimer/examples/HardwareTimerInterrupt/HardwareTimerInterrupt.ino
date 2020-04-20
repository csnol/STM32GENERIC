
/*
 * STM32 基本定时器 TIM6/7 库lib
 * STM32 basic timers TIM6/7 lib: HardwareBaseTimer by huaweiwx<huaweiwx@sina.com>
 *
 * This example sets basic timers(TIM6 and TIM7) software interrupt
 *
 * note: if  used freeRTOS, Timer7 is undefined 
 * 注：即使芯片有TIM7 , 如果运行了 freeRTOS 并使用了TIM7 ，该库 Timer7 就不会定义，因为freeRTOS优先使用基本定时器TIM7作为系统时钟；
 *
 * Advanced-control timers and General-purpose timers you can use the HardwareTimer lib.
 * 要使用到其他普通定时器和高级定时器TIM1~5/8~17/21~22(视所选板载芯片)的定时、PWM或脉冲捕捉等高级用途 ，可用HardwareTimer lib。 
 * 
 * 2018.5.28 huaweiwx<huaweiwx@sina.com>
*/


#if   USE_JlinkRTT 
#  include <JlinkRTT.h>
#  define mySerial jlinkRTT
#else
#  define mySerial Serial
#endif

#include "HardwareBaseTimer.h"
#define Timerx Timer7

void interrupt() {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void setup() {
    mySerial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);

    Timerx.setPeriod(1000000); // in microseconds = 1 second

    Timerx.attachInterrupt(interrupt);
    Timerx.resume();
}

void loop() {
    delay(5000);

    mySerial.println("----");

    mySerial.print("PCLK1Freq: ");
    mySerial.println(HAL_RCC_GetPCLK1Freq());
    
    mySerial.print("Timer base frequency:");
    mySerial.println(Timerx.getBaseFrequency());

    mySerial.print("Timer prescaler:");
    mySerial.println(Timerx.getPrescaleFactor());

    mySerial.print("Timer period:");
    mySerial.println(Timerx.getOverflow());
}
