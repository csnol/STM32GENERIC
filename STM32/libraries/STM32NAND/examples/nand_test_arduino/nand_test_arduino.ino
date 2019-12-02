/*  nand_test.ino arduino style nandflash.
      This boards tested:
       ARMFLY_F407ZG       HY27UF082G2A
       HASEE_III_F103ZE    K9F1G08U0A
       REDBULL_V2_F103ZE   K9F1208U0C
       STM32F103ZE_CORE    K9F1208U0B
       UPTECH_F103ZE       K9F1208U0B
*/

#include "LED.h"
#include <stm32Nand.h>
STM32NAND& myNAND = STM32NAND::getInstance();

#define led1 LED_BUILTIN
void setup() {
  NAND_IDTypeDef  nand_id;
  Led.Init();
  Serial.begin(115200);
  delay(1000);
  while (!Serial) {};

  Serial.print("NAND device test,Press any key begin...");
  while (!Serial.available()) {
    Led.flash(10, 140, 1);
  }


  uint8_t status;
  myNAND.Init();
  status = myNAND.readID(&nand_id);

  if (status != HAL_OK) {
    Serial.println(" read err!");
    return;
  }
  else Serial.print(" read OK!\nID = ");

  Serial.print(nand_id.Maker_Id, HEX);
  Serial.print(" ");
  Serial.print(nand_id.Device_Id, HEX);
  Serial.print(" ");
  Serial.print(nand_id.Third_Id, HEX);
  Serial.print(" ");
  Serial.println(nand_id.Fourth_Id, HEX);

  if ( ( nand_id.Maker_Id == 0xAD ) && (nand_id.Device_Id == 0xF1) &&
       ( nand_id.Third_Id == 0x80 ) && ( nand_id.Fourth_Id == 0x1D))
  {
    Serial.println("Type = HY27UF081G2A 128M bytes");
  }
  else if ( ( nand_id.Maker_Id == 0xAD) && (nand_id.Device_Id == 0xDA))
  {
    Serial.println("Type = HY27UF082G2A  256M bytes");
  }
  else if ( ( nand_id.Maker_Id == 0xEC ) && ( nand_id.Device_Id == 0xF1 ) &&
            ( nand_id.Third_Id == 0x80 ) && ( nand_id.Fourth_Id == 0x15) )
  {
    Serial.println("Type = K9F1G08U0A 128M bytes");
  }
  else if ( ( nand_id.Maker_Id == 0xEC ) && ( nand_id.Device_Id == 0xF1 ) &&
            ( nand_id.Third_Id == 0x00 ) && ( nand_id.Fourth_Id == 0x95 ) )
  {
    Serial.println("Type = K9F1G08U0B 128M bytes");
  }
  else if ( ( nand_id.Maker_Id == 0xEC ) && ( nand_id.Device_Id == 0x76 ) &&
            ( nand_id.Third_Id == 0x5A ) && ( nand_id.Fourth_Id == 0x3F ) )
  {
    Serial.println("Type = K9F1208U0C 128M bytes");
  }
  else  /*add me*/
  {
    Serial.println("Type = Unknow");
  }
  Serial.println("done!\n");
}

void loop() {
  Led.flash(500, 500, 1);
}

