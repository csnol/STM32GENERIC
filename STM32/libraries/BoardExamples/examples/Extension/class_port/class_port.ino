/*
 * STM32GENERIC arduino extension sample
 * GPIOPORTClass  class pin index demo 
 
 * huaweiwx@sina.com 2018.6.2
 */
 
#include "util/bitband.h"
#define LEDbase   GPIOD_BASE
#define LEDpin   13

GPIOPORTClass<LEDbase>PD;
#define LED PD[LEDpin]

void setup() {
  // put your setup code here, to run once:
  pinMode(PD13, OUTPUT);
  Serial.begin(115200);
}


void loop() {
 // put your main code here, to run repeatedly:
  LED = 1;  // portd index 13 is PD13 
  delay(500);
  LED = 0;
  delay(500);  
}
