/* loop_calibration.ino
   The function _delay_loop_2 time calibration
   _delay_loop_2 循环时间标定
   huaweiwx@sina.com 2019.10.18
*/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);

  Serial.print("F_CPU(mHz): ");
  Serial.println(SystemCoreClock / 1000000);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint32_t st, en;
  st = millis();

  for (uint16_t i = 1000; i; i--) { /* 1 sec */
#if 0
    delayMicroseconds(1000);
#else
//    _delay_loop_2((SystemCoreClock / 1000000 / 6) * 1000); /*1 ms for arm(1~9 cycle), F_CPU/6000000 per us */
      _delay_loop_us(1000);                        /*1 ms for arm(4~9 cycle), F_CPU/4000000 per us */
#endif
  }

  en = millis();
  Serial.println(en - st);
}
