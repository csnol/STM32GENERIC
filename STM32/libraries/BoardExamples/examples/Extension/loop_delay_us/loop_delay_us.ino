/*
  for _delay_loop_us time test
  by  huawei <huaweiwx@sina.com>   2019.9.10
*/

void setup() {
  Serial.begin(115200);  /*set param: 115200bps 8N1 (default 115200bps 8N1) */
}

//Measuring toggle frequency with an oscilloscope:
void loop() {
  uint32_t timers = getTimers(999);
  Serial.print("Timer elapsed:");
  Serial.print(timers);
  Serial.println(" us\n");
  delay(1000);
}

uint32_t getTimers(uint32_t count) {
  uint32_t timeBegan, timeElapsed;
  timeBegan = micros();
  _delay_loop_us(count);
  timeElapsed = (micros() - timeBegan); // Time taken to do nothing but increment a variable
  return timeElapsed;
}

