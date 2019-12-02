/* fastIO.ino  fastIO macro Template
   huaweiwx@sina.com  2018.2.18
*/

#include "util/fastIO.h"

/* assign PA0 a name TestPin.  we can use functions TestPin_xxx now:
  void     TestPin_Mode(uint8_t mode)
  void     TestPin_Set(void)
  void     TestPin_Clr(void)
  void     TestPin_High(void)
  void     TestPin_Low(void)
  void     TestPin_Toggle(void)
  uint8_t  TestPin_ReadIn(void)
  uint8_t  TestPin_Read(void)
  uint8_t  TestPin_ReadOut(void)
  void     TestPin_Out(uint8_t x)
  uint8_t  TestPin_IsOutHigh(void)
  uint8_t  TestPin_IsOutLow(void)
*/

GPIO_ALIAS_ASSIGN(TestPin, A, 0); //PA0 name TestPin;

void setup()
{
  TestPin_Mode(OUTPUT); //set mode OUTPUT
}

void loop()
{
  TestPin_High(); //set
  delay(500);
  TestPin_Low();  //reset
  delay(500);
}
