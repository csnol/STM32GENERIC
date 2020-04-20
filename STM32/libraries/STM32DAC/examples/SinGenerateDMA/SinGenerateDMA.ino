/*
  sineGeneriateDMA.ino  STM32DAC demo with DMA

  PA4_DACOUT and PA5_DACOUT are predefined instances of class STM32DAC.

  huaweiwx@sina.com 2018.7.21
*/

#include "STM32DAC.h"

#define NUMS    72

static uint32_t wavedatas[NUMS]; /*dma use uint32_t array only*/

static uint32_t myfunc(int i) {
  int mul = 10000;
  int res = sin(2 * PI / NUMS * i) * mul;
  return (uint32_t) map(res, -mul, mul,  0, 0xfff);
}

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(1000);

  Serial.println("Sin generate with DMA demo...");

  for (int i = 0; i < NUMS; i++) wavedatas[i] = myfunc(i);

  PA4_DACOUT.Init();
}

// the loop routine runs over and over again forever:
void loop() {
  PA4_DACOUT.startDMA(wavedatas, NUMS);
}
