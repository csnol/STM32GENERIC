/*
  AD.ino STM32ADC Class demo
  This demo PA0 ADC in

  adc are predefined instances of class ADCClass.
  huaweiwx@sina.com 2018.7.21
*/

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(115200);
  adc.resolution(12);
}

// the loop routine runs over and over again forever:
void loop() {
  uint16_t val = adc.read(PA0);
  Serial.println(val);
  delay(100);
}
