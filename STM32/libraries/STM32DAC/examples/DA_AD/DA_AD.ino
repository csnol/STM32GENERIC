/*
  DA_AD.ino STM32DAC demo
  This demo  PA4 DACout and PA0 ADC in, please connected the pin PA0 with PA4

  PA4_DACOUT and PA5_DACOUT are predefined instances of class STM32DAC.
  huaweiwx@sina.com 2018.7.21
*/

#include "STM32DAC.h"

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(115200);
  adc.resolution(12);  /*eq analogResolution(12) */
  PA4_DACOUT.Init();
}

static uint16_t val = 0;
// the loop routine runs over and over again forever:
void loop() {
  val += 0x10;
  val &= 0xfff;
  PA4_DACOUT = val;                  /* eq:  PA4_DACOUT.write(val); */
  delay(10);
  Serial.println(adc.read(PA0));
}
