

#define IR_VCC PA0
#define IR_GND PA1
#define IR_DO  PA4
#define IR_AO  PB0

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
#ifdef IR_GND
  pinMode(IR_GND, OUTPUT);
  digitalWrite(IR_GND, LOW);
#endif
#ifdef IR_VCC
  pinMode(IR_VCC, OUTPUT);
  digitalWrite(IR_VCC, HIGH);
#endif

  pinMode(IR_DO, INPUT);
  pinMode(IR_AO, INPUT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(LED_BUILTIN, digitalRead(IR_DO));
  Serial.print("D0=");
  Serial.print(digitalRead(IR_DO));
  Serial.print("  A0=");
  Serial.println(analogRead(IR_AO));
  delay(1000);
}
