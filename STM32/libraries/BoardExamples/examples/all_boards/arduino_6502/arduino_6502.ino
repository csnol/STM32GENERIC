#define BLINK_PIN LED_BUILTIN
uint8_t curkey = 0x55;

// Create USB serial_debug port
//USBSerial serial_debug;
#define serial_debug Serial

extern "C"  uint16_t getpc();
extern "C"  uint8_t getop();
extern "C"  void exec6502(int32_t tickcount);
extern "C"  void reset6502();
extern "C" void serout(uint8_t val) {
  serial_debug.write(val);
}
extern "C" uint8_t getkey() {
  //DEBUG
  if (serial_debug.available()) {
    curkey = serial_debug.read();
  } else {
    curkey = 0;
  }
  return (curkey);
}
extern "C" void clearkey() {
  curkey = 0;
}
extern "C" void printhex(uint16_t val) {
  serial_debug.print(val, HEX);
  serial_debug.println();
}

void setup () {
#ifdef BLINK_PIN
  // Flash the LED  3 times to prove we rebooted.
  pinMode(BLINK_PIN, OUTPUT);
  for ( int i = 0; i <= 3 ; i++)
  {
    digitalWrite(BLINK_PIN, LOW);
    delay(1000);
    digitalWrite(BLINK_PIN, HIGH);
    delay(1000);
  }
  digitalWrite(BLINK_PIN, LOW);
#endif
  serial_debug.begin (9600);
  serial_debug.println();
  reset6502();
}

void loop () {
  exec6502(100); //if timing is enabled, this value is in 6502 clock ticks. otherwise, simply instruction count.
  if (serial_debug.available()) {
    curkey = serial_debug.read() & 0x7F;
    curkey = serial_debug.read() ;
#ifdef BLINK_PIN
    digitalWrite(BLINK_PIN, LOW);
    delayMicroseconds(100);
    digitalWrite(BLINK_PIN, HIGH);
#endif
  }
}
