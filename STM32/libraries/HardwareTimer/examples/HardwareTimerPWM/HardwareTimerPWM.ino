/*
* This example sets timerx / channel to 10% PWM
*
* Select your board in https://danieleff.github.io/STM32GENERIC/ "STM32 Board" menu
*
* Check timer for which pin is the default TIM1/CH1 connected
*
* Check your board pinout which pin it is.
*
* Use scope / logic analyzer to check PWM output
*
* TIM1~5/8~17/21~22 for all chip if have. by huaweiwx@sina.com  2018.5.28
*/

#include "HardwareTimer.h"
#define Timerx Timer1
int testPwmOutputPin = PA8;
int testChannel = 1;

void setup() {
    Timerx.setPrescaleFactor(65535);
    Timerx.setOverflow(99); //Period

    Timerx.setCompare(testChannel, 10);  //testChannel / 10% Duty cycle
    Timerx.setMode(testChannel, TIMER_PWM,testPwmOutputPin);

    //Timerx.setMode(testChannel, TIMER_PWM, testPwmOutputPin);      // Alternatively for non-default pin. Check chip documentation!
    //Timerx.setMode(testChannel, TIMER_OUTPUT_COMPARE_TOGGLE);      // Pin toggles when counter reaches compare (effectively 50% PWM)

    Timerx.resume(TIMER_PWM,testChannel);
}

void loop() {

}
