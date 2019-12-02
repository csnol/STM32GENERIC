/**  extRam_rw.ino   sram(sdram) r/w test pass with following  boards:
      GD32F207IKT6      (32M SDRAM)  16bits speed=3280/2960 kps
      DISCOVERY_F746NG
      WaveShare F746I   (8M SDRAM)
      DISCOVERY_F429ZI  (8M SDRAM)
      F429IG_CORE       (8M SDRAM)   16bits speed=3232/3828 kps
      F207Z_CORE        (8M PSRAM)   16bits speed=2578/2664 kps

      ARMFLY_F407ZG     (1M SRAM)    16bits speed=3297/3426 kps
      ILLUMINATI_F407ZG (1M SRAM)    16bits speed=3297/3426 kps
      HASEE_III_F103ZE  (1M SRAM)
      REDBULL_V2_F103ZE (1M SRAM)
      F103Z_CORE        (1M SRAM)    16bits speed=1630/1576 kps
      UPTECH_F103Z      (256k SRAM)  16bits speed=1628/1551 kps
*/
#include <STM32ExtRAM.h>
STM32EXTRAM& extRAM = STM32EXTRAM::getInstance();

#define RWTEST_BITS 16  /*selecte 8/16/32 bits*/
#define led LED_BUILTIN

#if RWTEST_BITS == 8
#  define TEST_TYPE uint8_t
#  define TEST_MASK 0xff
#elif RWTEST_BITS == 16 /* 16 bit */
#  define TEST_TYPE uint16_t
#  define TEST_MASK 0xffff
#elif RWTEST_BITS == 32
#  define TEST_TYPE uint32_t
#  define TEST_MASK 0xffffffff
#else
#  error !must be 8/16/32!
#endif

uint32_t size;
TEST_TYPE data;

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  size = extRAM.getRamByteLength() / sizeof(data);
  delay(200);

  Serial.print("EXTRAM SIZE: 0x");
  Serial.println(extRAM.getRamByteLength(), HEX);
  Serial.print("RW size: ");
  Serial.println(size);

  uint32_t start = millis();

  uint32_t sum = 0;
  uint32_t sum_check = 0;
  uint32_t wTickCnt, rTickCnt;

  for (uint32_t i = 0; i < size; i++) {
    data = i;
    sum += i & TEST_MASK;
    extRAM.writeData(i * sizeof(data), &data, 1) ;
  }
  wTickCnt = millis() - start;
  Serial.print(RWTEST_BITS);
  Serial.print("bits Write time: ");
  Serial.print(wTickCnt);
  Serial.println(" ms");
  start = millis();

  for (uint32_t i = 0; i < size; i++) {
    extRAM.readData(i * sizeof(data), &data, 1) ;
    sum_check += data;
  }

  rTickCnt = millis() - start;
  Serial.print(RWTEST_BITS);
  Serial.print("bits Read time: ");
  Serial.print(rTickCnt);
  Serial.println(" ms");

  Serial.print("Checksum calculated:");
  Serial.println(sum_check);

  if (sum == sum_check) {
    Serial.print("EXTRAM is working with buffer size: ");
    Serial.println(size * sizeof(data));
  } else {
    Serial.print("Checksum should be:");
    Serial.println(sum);
    Serial.println("!!! EXTRAM NOT WORKING !!!");
    //   while(1);
  }

  Serial.print("read/write speed = ");
  Serial.print(size * sizeof(data) / rTickCnt);
  Serial.print("/");
  Serial.print(size * sizeof(data) / wTickCnt);
  Serial.println("  kps");

  Serial.print("test ptr baes adr read:");
  volatile TEST_TYPE *ptr;
  ptr = (TEST_TYPE *)extRAM.getRamBaseAddress();
  Serial.println((uint32_t)ptr, HEX);
  for (uint32_t i = 0; i < 16; i++) {
    Serial.print(*ptr++, HEX);
    Serial.print(" ");
  }
  Serial.println("\n----------------- done -------------------");
}

void loop() {
  digitalToggle(led);
  delay(1000);
}
