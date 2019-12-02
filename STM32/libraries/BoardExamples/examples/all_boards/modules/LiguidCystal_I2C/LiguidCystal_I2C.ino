/*NUCLEO F401 USE hardware LiquidCrestal_I2C 1602/2004 demo*/
#include <LiquidCrystal.h>

#define  USE_WARESOFT  1
#define LCD_SCL        PB_8
#define LCD_SDA        PB_9
//#define VCC_PIN      PB_10
//#define GND_PIN      PB_11

#if USE_WARESOFT
#include "WireSoft.h"
#define TOWIRE  TwoWireSoft
TwoWireSoft i2c(LCD_SDA, LCD_SCL);
#else
#include "Wire.h"
#define TOWIRE TwoWire
TwoWire  i2c;
#endif

//LiquidCrystal_I2C<TOWIRE> lcd(i2c, 0x27);        // set the LCD address to 0x27 (0x20~0x27)
LiquidCrystal_I2C<TOWIRE> lcd(i2c);                // default address to 0x27

void setup() {

#ifdef    GND_PIN
  pinMode(GND_PIN, OUTPUT);
  digitalWrite(GND_PIN, LOW);
#endif
#ifdef    VCC_PIN
  pinMode(VCC_PIN, OUTPUT);
  digitalWrite(VCC_PIN, HIGH);
#endif

  // initialize the LCD
  lcd.Init(20, 4);  // initialize LCD and set up the number of columns and rows,default is (16,2)

  // Turn on the blacklight and print a message.
  lcd.setBacklight(true);
  lcd.print("Hello, world!");

  lcd.setCursor(0, 1);
  lcd.print("nucleo f401");
}

void loop()
{
  // Do nothing here...
}
