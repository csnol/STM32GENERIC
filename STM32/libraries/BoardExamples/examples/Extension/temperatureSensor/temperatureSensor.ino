/*
  temperatureSensor.ino   read chip temperature Sensor value
  use extension temperatureFahrenheit and temperatureCelsius get the temperature and prints it to the Serial Monitor or plotter
  This example code is in the public domain.
  huaweiwx@sina.com 2018.9.18
*/
// the setup routine runs once when you press reset:

void setup() {
  Serial.begin(115200);
  delay(2000);
}

// the loop routine runs over and over again forever:
void loop() {
#if 1   /*Serial print*/
  Serial.print("Temperature: ");
  Serial.print(adc.temperatureFahrenheit());
  Serial.print("(F)   ");
  Serial.print(adc.temperatureCelsius());
  Serial.print("(C)  Vref=");
  Serial.print(adc.getReference());

#ifdef  ADC_CHANNEL_VBAT 
  Serial.print("(mV)  VBAT=");
  Serial.print(adc.getVBAT());
#endif

  Serial.println("(mV)");
  delay(2000);
#else /* to serial  plotter */
  Serial.println(adc.temperatureCelsius());
  delay(100);
#endif
}
