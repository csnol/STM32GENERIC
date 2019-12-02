/*
* This example encoder
* Select your board in https://danieleff.github.io/STM32GENERIC/ "STM32 Board" menu
* Check timer for which pin is the default TIM1/CH1 connected
* Check your board pinout which pin it is.
* Connect the testPwmPin to the previous input capture pin
* On Serial, you should see default PWM frequency
*
* TIM1~5/8~17/21~22 for all chip if have. by huaweiwx@sina.com  2018.5.28
*/

#include "HardwareTimer.h"

#define Timerx Timer2

void setup() {

    Serial.begin(115200);

    Timerx.setPrescaleFactor(0);
    Timerx.setOverflow(UINT16_MAX);
	
    Timerx.resume(TIMER_ENCODER);
}

void loop() {
    uint32_t start = Timerx.getCompare(1);
    uint32_t end;
    do {
        //Wait for next rising edge
        end = Timerx.getCompare(1);
    } while(end == start);

    uint32_t diff;
    if (end > start) {
        diff = end - start;
    } else {
        diff = (Timerx.getOverflow() - start) + end;
    }
    uint32_t timerFrequency = Timerx.getBaseFrequency() / (Timerx.getPrescaleFactor() + 1);

    Serial.print("Input frequency: ");
    Serial.print((float)timerFrequency / diff, 6);
    Serial.println(" Hz");

    delay(1000);
}
