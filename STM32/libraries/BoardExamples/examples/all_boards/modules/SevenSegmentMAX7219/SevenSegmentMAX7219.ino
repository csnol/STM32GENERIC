//We always have to include the library
#include "LedControl.h"

/*
  Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
  pin 12 is connected to the DataIn
  pin 11 is connected to the CLK
  pin 10 is connected to LOAD
  We have only a single MAX72XX.
*/

/* for NUCLEO F401RET6 */
//#define VCC_PIN
//#define GND_PIN
#define  DI_PIN PA_5
#define  CS_PIN PA_6
#define CLK_PIN PA_7

LedControl lc = LedControl(DI_PIN, CLK_PIN, CS_PIN, 2);

/* we always wait a bit between updates of the display */
unsigned long delaytime = 1000;

void setup() {
#ifdef GND_PIN
  pinMode(GND_PIN, OUTPUT);
  digitalWrite(GND_PIN, LOW); /*GND*/
#endif
#ifdef VCC_PIN
  pinMode(VCC_PIN, OUTPUT);
  digitalWrite(VCC_PIN, HIGH); /*VCC.*/
  delay(1000);     /*wait for eeprom power ready*/
#endif
  /*
    The MAX72XX is in power-saving mode on startup,
    we have to do a wakeup call
  */
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 8);
  /* and clear the display */
  lc.clearDisplay(0);
}


/*
  This method will display the characters for the
  word "Arduino" one after the other on digit 0.
*/
void writeArduinoOn7Segment() {
  lc.setChar(0, 0, 'a', false);
  delay(delaytime);
  lc.setRow(0, 0, 0x05);
  delay(delaytime);
  lc.setChar(0, 0, 'd', false);
  delay(delaytime);
  lc.setRow(0, 0, 0x1c);
  delay(delaytime);
  lc.setRow(0, 0, 0b00010000);
  delay(delaytime);
  lc.setRow(0, 0, 0x15);
  delay(delaytime);
  lc.setRow(0, 0, 0x1D);
  delay(delaytime);
  lc.clearDisplay(0);
  delay(delaytime);
}

/*
  This method will scroll all the hexa-decimal
  numbers and letters on the display. You will need at least
  four 7-Segment digits. otherwise it won't really look that good.
*/
void scrollDigits() {
  for (int i = 0; i < 10; i++) {
    lc.setDigit(0, 7, i, false);
    lc.setDigit(0, 6, i + 1, false);
    lc.setDigit(0, 5, i + 2, false);
    lc.setDigit(0, 4, i + 3, false);
    lc.setDigit(0, 3, i + 4, false);
    lc.setDigit(0, 2, i + 5, false);
    lc.setDigit(0, 1, i + 6, false);
    lc.setDigit(0, 0, i + 7, false);
    delay(delaytime);
  }
  lc.clearDisplay(0);
  delay(delaytime);
}

void loop() {
  writeArduinoOn7Segment();
  scrollDigits();
}