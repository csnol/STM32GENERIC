/**  nor_test_arduino.ino   arduino style nor_test tested for this board:
      HASEE_III_F103ZE   
      REDBULL_V2_F103ZE
      F103ZE_CORE        MX29LV640EBTI 8M
      UPTECH_F103ZE      SST39VF040
   Allocate 256k ram, and write to Serial the results
*/
#include "LED.h"
#include <stm32Nor.h>

STM32NOR& myNOR = STM32NOR::getInstance();

void setup() {
  NOR_IDTypeDef  nor_id;
  Led.Init();
  Serial.begin(115200);
  delay(1000);
  while (!Serial) { /*if usbserial*/
  }

  Serial.println("NOR device test. Press any key begin...");
  while (!Serial.available()) {
    Led.flash(10, 140, 1);
  }

  myNOR.Init();
  myNOR.readID(&nor_id);


  Serial.print(nor_id.Manufacturer_Code, HEX);
  Serial.print(" ");
  Serial.print(nor_id.Device_Code1, HEX);
  Serial.print(" ");
  Serial.print(nor_id.Device_Code2, HEX);
  Serial.print(" ");
  Serial.println(nor_id.Device_Code3, HEX);

  if ( ( nor_id.Manufacturer_Code == 0x00BF ) && (nor_id.Device_Code1 == 0x2782))
  {
    Serial.println("Type = SST39VF160 2M bytes");
  }
  else if ( ( nor_id.Manufacturer_Code == 0x00BF ) && (nor_id.Device_Code1 == 0x234B))
  {
    Serial.println("Type = SST39VF1601 2M bytes");
  }
  else if ( ( nor_id.Manufacturer_Code == 0x00BF ) && (nor_id.Device_Code1 == 0x00D7))
  {
    Serial.println("Type = SST39VF040 512K  bytes");
  }
  else if ( ( nor_id.Manufacturer_Code == 0x0001 ) && (nor_id.Device_Code1 == 0x227E) &&
            ( nor_id.Device_Code2 == 0x2212 ) && ( nor_id.Device_Code3 == 0x2200 ) )
  {
    Serial.println("Type = AM29LV128ML 16M bytes");
  }
  else if ( ( nor_id.Manufacturer_Code == 0x0001 ) && ( nor_id.Device_Code1 == 0x227E ) &&
            ( nor_id.Device_Code2 == 0x2221 ) && ( nor_id.Device_Code3 == 0x2201 ) )
  {
    Serial.println("Type = S29GL128P 16M bytes");  /* 16M bytes */
  }
  else if ( ( nor_id.Manufacturer_Code == 0x0020 ) && ( nor_id.Device_Code1 == 0x227E ) &&
            ( nor_id.Device_Code2 == 0x2220 ) && ( nor_id.Device_Code3 == 0x2200 ) )
  {
    Serial.println("Type = M29DW128F 16M bytes");
  }
  else if ( ( nor_id.Manufacturer_Code == 0xC2 ) && ( nor_id.Device_Code1 == 0x22CB ) &&
            ( nor_id.Device_Code2 == 0x0 ) && ( nor_id.Device_Code3 == 0x8 ) )
  {
    Serial.println("Type = MX29LV640EBTI 8M bytes");
  }
  else  /*add me*/
  {
    Serial.println("Type = Unknow");
  }

  uint8_t data;
  uint32_t len = 16;

#if 0
  myNOR.eraseChip();
  delay(1000);

  for (uint32_t adr = 0; adr < len; adr++) {
    data = adr;
    myNOR.writeData(adr, &data) ;
    delay(5);
  }
  myNOR.returnToReadMode();
#endif

  for (uint32_t adr = 0; adr < len * 2; adr++) {
    myNOR.readData(adr, &data) ;
    Serial.print(data, HEX);
    Serial.print(" ");
  }
  Serial.println("\nread ok!\n");
}

void loop() {
  Led.flash(500, 500, 1);
}

