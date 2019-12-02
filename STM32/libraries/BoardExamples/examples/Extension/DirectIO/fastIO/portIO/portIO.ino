/* PORTIO class Template
   huaweiwx@sina.com  2018.6.18
*/
#include "util/bitband.h"

//PORTIO<GPIOC_BASE,GPIO_PIN_13>portc;    /* nucler401re button pc13 */
PORTIO<GPIOC_BASE>portc;                  /* nucler401re button pc13 */
PORTIO<GPIOA_BASE,GPIO_PIN_5,OUTPUT>ledportpin;  /* nucler401re led PA5 */

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  
//  portc.setMode(INPUT); //default mode INPUT
  portc.Init();
  ledportpin.Init();
}

// the loop function runs over and over again forever
void loop() {
  ledportpin.write(GPIO_PIN_5);
  delay(500);                  // wait for 0.5 second
  
  ledportpin.write(0x00);
  delay(500);                  // wait for 0.5 second
  
  Serial.println(portc.read(),HEX); //read portc
}
