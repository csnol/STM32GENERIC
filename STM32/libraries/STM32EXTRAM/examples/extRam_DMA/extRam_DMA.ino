/**  extRam_DMA.ino   sram(sdram) DMA  test pass with following  boards:
      GD32F207IKT6     (32M SDRAM)
      DISCOVERY_F746NG
      WaveShare F746I) (8M SDRAM)
      DISCOVERY_F429ZI (8M SDRAM)
      F429IG_CORE      (8M SDRAM)
      ARMFLY_F407ZG     (1M SRAM)
      ILLUMINATI_F407ZG (1M SRAM)
      HASEE_III_F103ZE  (1M SRAM)
      REDBULL_V2_F103ZE (1M SRAM)
      F103Z_CORE        (1M SRAM)
      UPTECH_F103Z    (256k SRAM)
*/

#include <stm32_dma.h>
STM32DMA<STM32DMA<>::MEMTOMEM>dma;
//STM32DMA<>dma;

#include <STM32ExtRAM.h>
STM32EXTRAM& extRAM = STM32EXTRAM::getInstance();

#define led LED_BUILTIN

uint32_t size;
uint32_t data;
uint32_t dis[1024];

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  size = extRAM.getRamByteLength() / sizeof(data);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(1000);

  Serial.println("extRam DMA mentomen test....");
  Serial.print("EXTRAM SIZE: 0x");
  Serial.println(extRAM.getRamByteLength(), HEX);
  Serial.flush();

  uint32_t start = millis();

  uint32_t sum = 0;
  uint32_t sum_check = 0;

  for (uint32_t i = 0; i < size; i++) {
    data = i;
    sum += i;
    extRAM.writeData(i * sizeof(data), &data, 1) ;
  }

  Serial.print("Write time: ");
  Serial.print(millis() - start);
  Serial.println(" ms");
  start = millis();

  for (uint32_t i = 0; i < size; i++) {
    extRAM.readData(i * sizeof(data), &data, 1) ;
    sum_check += data;
  }

  Serial.print("Read time: ");
  Serial.print(millis() - start);
  Serial.println(" ms");

  Serial.print("Checksum should be:");
  Serial.println(sum);
  Serial.print("Checksum calculated:");
  Serial.println(sum_check);

  if (sum == sum_check) {
    Serial.print("EXTRAM is working with buffer size: ");
    Serial.println(size * sizeof(data));
  } else {
    Serial.println("!!! EXTRAM NOT WORKING !!!");
    while (1);
  }

  Serial.println("test DMA:");
  uint32_t* ptr = (uint32_t *)extRAM.getRamBaseAddress();

  dma.Init();
  if (dma.start(ptr, dis, sizeof(dis)) == HAL_OK) {
    for (uint32_t i = 0; i < sizeof(dis) / sizeof(dis[0]); i++) {
      Serial.print(dis[i], HEX);
      if ((i & 0xf) == 0xf)
        Serial.println();
      else
        Serial.print("  ");
    }
    Serial.println("\ndma test ok!");
  } else {
    Serial.println("\n!dma fault!");
  }
}

void loop() {
  digitalToggle(led);
  delay(500);
}

