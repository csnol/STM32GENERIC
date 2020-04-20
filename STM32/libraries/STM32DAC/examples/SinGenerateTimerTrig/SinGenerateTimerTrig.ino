/*
   Sin wave generate with TIM6 interrupt 使用定时器 TIM6 中断生成 sine 波形
   
   PA4_DACOUT and PA5_DACOUT are predefined instances of class STM32DAC.
   
   2018.7.23 huaweiwx<huaweiwx@sina.com>
*/

#include "HardwareBaseTimer.h"
#include "STM32DAC.h"

#define NUMS    72
#define HZ      50

static uint32_t wavedatas [NUMS];

static uint32_t myfunc(int i) {
  int mul = 10000;
  int res = sin(2 * PI / NUMS * i) * mul;
  return (uint32_t) map(res, -mul, mul,  0, 0xfff);
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("sine wave generate with TIM6 interrupt demo...");
  pinMode(LED_BUILTIN, OUTPUT);

  for (int i = 0; i < NUMS; i++) wavedatas[i] = myfunc(i);
  

  Timer6.setPeriod(0X7FF / HZ / NUMS); // calculate period: 1000000us/HZ/NUMS
  Timer6.resume(TIM_TRGO_UPDATE);
  
  PA4_DACOUT.Init(DAC_TRIGGER_T6_TRGO);
  
 }

void loop() {
  PA4_DACOUT.startDMA(wavedatas, NUMS);
}
