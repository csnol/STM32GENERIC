#include "Arduino.h"
class BILED
{
  public:
    BILED(ARDUINOPIN_TypeDef bPin0, ARDUINOPIN_TypeDef bPin1): bPin0(bPin0), bPin1(bPin1) {}
    ARDUINOPIN_TypeDef bPin0;
    ARDUINOPIN_TypeDef bPin1;

    ~BILED() {
      deInit();
    }

    void Init(void) {
      pinMode(bPin0, OUTPUT);
      pinMode(bPin1, OUTPUT);
    }
    
    void deInit(void) {
      pinMode(bPin0, INPUT);
      pinMode(bPin1, INPUT);
    }
    
    uint8_t read() {
      uint8_t rtn = 0;
      if (digitalRead(bPin0)) rtn |= 1;
      if (digitalRead(bPin1)) rtn |= 2;
      return rtn;
    }
    
    void write(uint8_t val) {
      digitalWrite(bPin0, bitRead(val, 0) ? HIGH : LOW);
      digitalWrite(bPin1, bitRead(val, 1) ? HIGH : LOW);
    }
    void toggle(void) {
      digitalToggle(bPin0);
      digitalToggle(bPin1);
    }
    void off() {
      digitalWrite(bPin0, LOW);
      digitalWrite(bPin1, LOW);
    }
    void on(uint8_t val = 0) {
      write(val);
    }
};


