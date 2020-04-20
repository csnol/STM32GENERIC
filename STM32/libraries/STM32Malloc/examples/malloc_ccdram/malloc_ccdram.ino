/*
   CCMDATARAM tested on F407/429
*/
#include <STM32Malloc.h>

MALLOCClass memManager((uint8_t*)CCMDATARAM_BASE, (uint32_t)(CCMDATARAM_END-CCMDATARAM_BASE+1));  /* menager ccram 64k f407/429 */

#define led LED_BUILTIN

uint16_t* data = NULL;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  delay(1000);
  Serial.println("init... ");

  if ( memManager.Init() != HAL_OK) {
    Serial.println("error!");
    while (1);
  }

  Serial.println("OK!");
  data = (uint16_t *) memManager.alloc(0x2);

  if (data == NULL) {
    Serial.println("alloc error!");
    while (1);
  } else {
    Serial.print("loc at: ");
    Serial.print((uint32_t)data, HEX);
    Serial.print("   perused:");
    Serial.println(memManager.perused());
    delay(3000);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  *data += 1;
  Serial.println(*data, HEX);
  digitalToggle(led);
  delay(1000);
}
