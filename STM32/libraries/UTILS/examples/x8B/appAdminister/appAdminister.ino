/* addAdminister.ino stm32 vdisk/mcu administer
    ---------------------------------------------------------------------------------------
   1 selected: one of  in HAL_Conf.h file option if built in: USE_SDIOSDCARD/USE_SPISDCARD/USE_SPIFLASH
   2 from the menu option selected:  Startup adr: flash(WhitRamboo xxkRAM used only) to build the project.
   ---------------------------------------------------------------------------------------
   cmd usage:
   type help or h or ? for Display list of commands.

   ---------------------------------------------------------------------------------------
   tested for F103x8/B  by huaweiwx@sina.com 2017.10
   ---------------------------------------------------------------------------------------
*/

#include <Streaming.h>
#include <cmdline.h>
char cmdline[64];
int ptr;

#include <utils.h>
#include <LED.h>

void setup() {
  Serial.begin(115200);
  Led.Init();

  //for  use SerialUSB if selected from menu
#if (MENU_USB_SERIAL || MENU_USB_IAD)
  while (!Serial.available()) {
    Led.flash(10, 990, 1);
  }
#endif

  Serial.println(F("* STM32 vdos demo v2.0 *\r\n>"));
  ptr = 0;
}

boolean stringComplete = false;  // whether the string is complete
void loop() {
  int nStatus;
  if (stringComplete) {
    if (cmdline[0] > ' ') {
      nStatus = CmdLineProcess(cmdline);
      if (nStatus == CMDLINE_BAD_CMD)
      {
        Serial.println(F("BadCmd!"));
      }
      else if (nStatus == CMDLINE_TOO_MANY_ARGS)
      {
        Serial.println(F("TooMany args!"));
      }
      else if (nStatus != 0)
      {
        Serial.print(F("Cmd rtn errCode"));
        Serial.println(nStatus);
      }
    }
    ptr = 0;
    stringComplete = false;
    Serial.print(F("\r\n>"));
  }
#if defined(STM32GENERIC)
  serialEvent();
#endif
  Led.flash(10, 90, 1);
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    cmdline[ptr++] = inChar;
    cmdline[ptr] = '\0';
    if ((inChar == '\n') || (inChar == '\r')) {
      stringComplete = true;
    }
  }
}

void print_port(char* str, uint16_t val) {
  Serial <<  str << " : ";
  for (uint8_t i = 15; i > 0; i--) {
    if (val & (1 << i)) break;
    Serial << "0";
  }
  Serial << _BIN(val) << "(0x" << _HEX(val) << ")\n";
}

//*****************************************************************************
// This function implements the "help" command.  It prints a simple list of the
// available commands with a brief description.
//*****************************************************************************
int Cmd_help(int argc, char *argv[])
{
  if (argc == 2) { //  ?[ pin/P/A/B/C/D]
    char* pstr = argv[1];
    if (isdigit(pstr[0])) {
      uint8_t pin = atoi(argv[1]);
      Serial << stm32PinName(pin) << "(" << argv[1] << "): " << digitalRead(pin) << "\n";
      return 0;
    }
    if (pstr[0] == 'P') {
      uint8_t pin = UTIL_Str2PortPin(argv[1]);
      if (pin == 0xff) {
        Serial << "err: pinName" << argv[1] << "\n";
        return 0;
      } else {
        Serial << argv[1] << "(" << pin << ") : " << digitalRead(pin) << "\n";
        return 0;
      }
    }
    if (pstr[0] == 'A') {
#if defined(STM32F1) || defined(GD32F20X)
      print_port((char*)"GPIOA->IDR", GPIOA->IDR);
      print_port((char*)"      ->CRH", GPIOA->CRH & 0xffff);
      print_port((char*)"      ->CRL", GPIOA->CRL & 0xffff);
#else
      print_port((char*)"GPIOA->IDR  ", GPIOA->IDR);
      print_port((char*)"      ->MODER", GPIOA->MODER);
#endif
      return 0;
    }
    if (pstr[0] == 'B') {
#if defined(STM32F1) || defined(GD32F20X)
      print_port((char*)"GPIOB->IDR", GPIOB->IDR);
      print_port((char*)"      ->CRH", GPIOB->CRH & 0xffff);
      print_port((char*)"      ->CRL", GPIOB->CRL & 0xffff);
#else
      print_port((char*)"GPIOB->IDR  ", GPIOB->IDR);
      print_port((char*)"      ->MODER", GPIOB->MODER);
#endif
      return 0;
    }
    if (pstr[0] == 'C') {
#if defined(STM32F1) || defined(GD32F20X)
      print_port((char*)"GPIOC->IDR", GPIOC->IDR);
      print_port((char*)"      ->CRH", GPIOC->CRH & 0xffff);
      print_port((char*)"      ->CRL", GPIOC->CRL & 0xffff);
#else
      print_port((char*)"GPIOC->IDR  ", GPIOC->IDR);
      print_port((char*)"      ->MODER", GPIOC->MODER);
#endif
      return 0;
    }
#ifdef GPIOD
    if (pstr[0] == 'D') {
#if defined(STM32F1) || defined(GD32F20X)
      print_port((char*)"GPIOD->IDR", GPIOD->IDR);
      print_port((char*)"      ->CRH", GPIOD->CRH & 0xffff);
      print_port((char*)"      ->CRL", GPIOD->CRL & 0xffff);
#else
      print_port((char*)"GPIOD->IDR  ", GPIOD->IDR);
      print_port((char*)"      ->MODER", GPIOD->MODER);
#endif
      return 0;
    }
#endif
#ifdef GPIOE
    if (pstr[0] == 'E') {
#if defined(STM32F1) || defined(GD32F20X)
      print_port((char*)"GPIOE->IDR", GPIOE->IDR);
      print_port((char*)"      ->CRH", GPIOE->CRH & 0xffff);
      print_port((char*)"      ->CRL", GPIOE->CRL & 0xffff);
#else
      print_port((char*)"GPIOE->IDR  ", GPIOE->IDR);
      print_port((char*)"      ->MODER", GPIOE->MODER);
#endif
      return 0;
    }
#endif
#ifdef GPIOF
    if (pstr[0] == 'F') {
#if defined(STM32F1) || defined(GD32F20X)
      print_port((char*)"GPIOF->IDR", GPIOF->IDR);
      print_port((char*)"      ->CRH", GPIOF->CRH & 0xffff);
      print_port((char*)"      ->CRL", GPIOF->CRL & 0xffff);
#else
      print_port((char*)"GPIOF->IDR  ", GPIOF->IDR);
      print_port((char*)"      ->MODER", GPIOF->MODER);
#endif
      return 0;
    }
#endif
#ifdef GPIOG
    if (pstr[0] == 'G') {
#if defined(STM32F1) || defined(GD32F20X)
      print_port((char*)"GPIOG->IDR", GPIOG->IDR);
      print_port((char*)"      ->CRH", GPIOG->CRH & 0xffff);
      print_port((char*)"      ->CRL", GPIOG->CRL & 0xffff);
#else
      print_port((char*)"GPIOG->IDR  ", GPIOG->IDR);
      print_port((char*)"      ->MODER", GPIOG->MODER);
#endif
      return 0;
    }
#endif
#ifdef GPIOH
    if (pstr[0] == 'H') {
#if defined(STM32F1) || defined(GD32F20X)
      print_port((char*)"GPIOH->IDR", GPIOH->IDR);
      print_port((char*)"      ->CRH", GPIOH->CRH & 0xffff);
      print_port((char*)"      ->CRL", GPIOH->CRL & 0xffff);
#else
      print_port((char*)"GPIOH->IDR  ", GPIOH->IDR);
      print_port((char*)"      ->MODER", GPIOH->MODER);
#endif
      return 0;
    }
#endif
#ifdef GPIOI
    if (pstr[0] == 'I') {
      print_port((char*)"GPIOI->IDR  ", GPIOI->IDR);
#if defined(STM32F1) || defined(GD32F20X)
      print_port((char*)"      ->CRH  ", GPIOI->CRH & 0xffff);
      print_port((char*)"      ->CRL  ", GPIOI->CRL & 0xffff);
#else
      print_port((char*)"      ->MODER", GPIOI->MODER);
#endif
      return 0;
    }
#endif
    Serial << argc << "  " <<  argv[1] << " ??\n";
  }

  tCmdLineEntry *pEntry;
  pEntry = &g_sCmdTable[0];
  Serial.println(F("\r\nAvailable commands:\r\n------------------\n"));
  while (pEntry->pcCmd)
  {
    Serial.print( pEntry->pcCmd);
    Serial.println(pEntry->pcHelp);
    pEntry++;
  }

  Serial << "\nPIN list:";
  for (uint8_t i = 0; i < sizeof(variant_pin_list) / sizeof(variant_pin_list[0]); i++)
    Serial << stm32PinName(i) << ", ";

  uint8_t leds[] = {LEDS_LIST};
  Serial << "\nLED list:\n";
  for (uint8_t i = 0; i < sizeof(leds) / sizeof(leds[0]); i++)
    Serial << "LED" << i << "_BUILTIN(" <<  stm32PinName(leds[i]) << "), ";

#ifdef KEYS_LIST
  uint8_t keys[] = {KEYS_LIST};
  Serial << "\nKEYS list:";
  for (uint8_t i = 0; i < sizeof(keys) / sizeof(keys[0]); i++)
    Serial << "BUILTIN" << i << "(" << stm32PinName(keys[i]) << "), ";
#endif

#ifdef MOSI
  Serial << "\nSPI pins:";
  Serial << "MOSI(" <<  stm32PinName(MOSI);
  Serial << "), MISO(" <<  stm32PinName(MISO);
  Serial << "), SCK(" <<  stm32PinName(SCK);
  Serial << "), SS(" <<  stm32PinName(SS) << "),";
#endif

#ifdef SDA
  Serial << "\nI2C pins:";
  Serial << "SDA:" <<  stm32PinName(SDA);
  Serial << ",SCL:" <<  stm32PinName(SCL);
#endif

#ifdef DBGMCU
  Serial << "\nMCU_ID:" << _HEX(HAL_GetDEVID());
#endif

#ifdef UID_BASE
  uint32_t UID[3];
# if defined(STM32F1)||defined(STM32F2)
  HAL_GetUID(UID);
# else
  UID[0] = HAL_GetUIDw0();
  UID[1] = HAL_GetUIDw1();
  UID[2] = HAL_GetUIDw2();
# endif
  Serial << "\nUSERID:" << _HEX(UID[0]) << " " << _HEX(UID[1]) << " " <<  _HEX(UID[2]);
#endif

  volatile uint32_t useradr;
  Serial << "\ncodes on slot:\n";
  for (int i = 0; i < (appCodeSegAddr[0] + 1); i++) {
    if (i > 0)
      useradr = FLASH_BASE + appCodeSegAddr[i] * 1024;
    else {
      useradr = USER_CODE_RAM;
    }
    Serial << i << "# addr:0x";
    if (useradr < 0x10000000) Serial << "0";
    Serial << _HEX(useradr) << " is ";
    if (UTIL_checkUserCode(useradr))
      Serial << "app.\n";
    else
      Serial << "free.\n";
  }

  return (0);
}

//exp:go 1/2/...
int Cmd_go(int argc, char *argv[])
{
  if (!(argc == 2)) return 0;
  volatile uint32_t useradr;
  Serial << "go " << argv[1] << "\n";
  int i = atoi(argv[1]);
  if (i < (appCodeSegAddr[0] + 1)) {
    if (i == 0) {
      useradr =  USER_CODE_RAM;
    } else {
      useradr = FLASH_BASE + appCodeSegAddr[i] * 1024;
    }

    if (UTIL_checkUserCode(useradr))
    {
      Serial << "check ok and goto " << _HEX(useradr) << ".....\n" << _endl;
#if (MENU_USB_SERIAL||MENU_USB_MASS_STORAGE||MENU_USB_IAD)
      USBDeviceFS.end();
#endif
      delay(1000); /*wait  serial complated */

      //    Serial1.end();  /*if open close it*/
      //    Serial2.end();  /*if open close it*/
      //    UTIL_jumpToUser(useradr);
      start_application(useradr);
    } else {
      Serial << "slot: " << argv[1] << " is unavailed!\n";
    }
  }
  return 0;
}

/*---------------------arduino func----------------------------*/
static uint8_t getpin(char* str) {
  uint8_t pin = 0xff;
  if (str[0] == 'P')    pin = UTIL_Str2PortPin(str);
  else if (UTIL_isHexStr(str)) pin = UTIL_hexNum(str);
  else if (isdigit(str[0]))  pin = atoi(str);
  return pin;
}

// This function implements the "dr" command. digital pin read input
// Usage: dr pin
static int Cmd_digitalRead(int argc, char *argv[])
{
  static uint8_t pin = 0xff;
  uint8_t tmp;
  if (argc > 1) {
    tmp = getpin(argv[1]);
    if (tmp < 0xff) pin = tmp;
  }
  if (pin == 0xff) {
    Serial << "error: pinName" << argv[1] << "\n";
    return 0;
  }
  Serial << stm32PinName(pin) << "(" << pin  << "):"  << digitalRead(pin) << "\n";
  return (0);
}

// This function implements the "dw" command. bit write to a pin output
// Usage: dw pin 0/1
int Cmd_digitalWrite(int argc, char *argv[])
{
  static uint8_t v;
  static uint8_t pin = 0xff;
  uint8_t tmp;

  if (argc > 1) {
    tmp = getpin(argv[1]);
    if (tmp < 0xff) pin = tmp;
  }
  if (pin == 0xff) {
    Serial << "err: pinName" << argv[1] << "\n";
    return 0;
  }

  if (argc > 2)
    v = atoi(argv[2]);

  if (v) {
    digitalWrite(pin, HIGH);   // turn on/off the LED
  } else {
    digitalWrite(pin , LOW);
  };

  return (0);
}

// This function implements the "dt" command. toggle pin H/L
// Usage: dt pin
static int Cmd_digitalToggle(int argc, char *argv[])
{
  static uint8_t pin = 0xff;
  uint8_t tmp;
  if (argc > 1) {
    tmp = getpin(argv[1]);
    if (tmp < 0xff) pin = tmp;
  }
  if (pin == 0xff) {
    Serial << "err: pinName" << argv[1] << "\n";
    return 0;
  }
  digitalToggle(pin);
  return (0);
}

// This function implements the "aw" command. analog pin output
// Usage: aw pin byte
static int Cmd_analogWrite(int argc, char *argv[])
{
  static uint16_t v;
  static uint8_t pin = 0xff;
  uint8_t tmp;

  if (argc > 1) {
    tmp = getpin(argv[1]);
    if (tmp < 0xff) pin = tmp;
  }
  if (pin == 0xff) {
    Serial << "err: pinName" << argv[1] << "\n";
    return 0;
  }

  if (argc > 2) {
    v = atoi(argv[2]);
  }

  analogWrite(pin, v);
  return (0);
}

// This function implements the "ar" command. analog pin read input
// Usage: ar pin
static int Cmd_analogRead(int argc, char *argv[])
{
  static uint8_t pin = 0xff;
  uint8_t tmp;
  if (argc > 1) {
    tmp = getpin(argv[1]);
    if (tmp < 0xff) pin = tmp;
  }
  if (pin == 0xff) {
    Serial << "error: pinName" << argv[1] << "\n";
    return 0;
  }
  Serial << stm32PinName(pin) << "(" << pin  << "):"  << analogRead(pin) << "\n";
  return (0);
}

/* ----------------This function implements the "pm" command. Set a pin input/output mode  --------------------------*/
// Usage: pm pin mode[0/1/2]
static int Cmd_pinMode(int argc, char *argv[])
{
  static uint8_t pin = 0xff;
  static uint8_t mode = 0;
  uint8_t tmp;
  if (argc > 1) {
    tmp = getpin(argv[1]);
    if (tmp < 0xff) pin = tmp;
  }
  if (pin == 0xff) {
    Serial << "err: pinName" << argv[1] << "\n";
    return 0;
  }

  if (argc > 2) {
    tmp = getpin(argv[2]);
    if (tmp) mode = tmp;
    else    mode = 0;
  }
  pinMode(pin , mode);
  Serial << stm32PinName(pin) << (mode ? " OUTPUT" : " INPUT") << "\n";
  return (0);
}

/*-------------  This function implements the "si" command. shiftIn ----------------------------*/
// Usage: si dpin cpin order
int Cmd_shiftin(int argc, char *argv[])
{
  uint8_t val;
  static uint8_t dpin = 0xff;
  static uint8_t cpin = 0xff;
  static uint8_t ord = 1;
  uint8_t pin;
  if (argc > 1) {
    pin = getpin(argv[1]);
    if (pin < 0xff) dpin = pin;
  }
  if (argc > 2) {
    pin = getpin(argv[2]);
    if (pin < 0xff) cpin = pin;
  }
  if (argc > 3) {
    pin = getpin(argv[3]);
    if (pin < 0xff) ord = pin;
  }

  if ((dpin == 0xff) || (cpin == 0xff)){
    Serial.println(F(" argc err!\r\n"));
  }else{
    val = shiftIn(dpin, cpin, ord);
    Serial << "\nshiftIn val=" << _HEX(val) << "\n";
  }
  return (0);
}

/*--------------  This function implements the "so" command. shiftIn---------------------------------*/
// Usage: so val dpin cpin order
int Cmd_shiftout(int argc, char *argv[])
{
  static uint8_t val = 0;
  static uint8_t dpin = 0xff;
  static uint8_t cpin = 0xff;
  static uint8_t ord = 1;
  uint8_t tmp;
  if (argc > 1) {
    tmp = getpin(argv[1]);
    if (tmp < 0xff) val = tmp;
  }
  if (argc > 2) {
    tmp = getpin(argv[2]);
    if (tmp < 0xff) dpin = tmp;
  }
  if (argc > 3) {
    tmp = getpin(argv[3]);
    if (tmp < 0xff) cpin = tmp;
  }

  if (argc > 4) {
    tmp = getpin(argv[3]);
    if (tmp < 0xff) ord = tmp;
  }

  if ((dpin == 0xff) || (cpin == 0xff)){
    Serial.println(F(" argc err!\r\n"));
  }else{
    shiftOut(dpin, cpin, ord, val);
    Serial << "shiftout " << _HEX(val) << " ok\n";
  }
  return (0);
}


tCmdLineEntry g_sCmdTable[] =
{
  { "?",      Cmd_help,          "   : help"} ,

  //go flash addr
  { "go",     Cmd_go,            "  : goto n addr running(slot#)"},

  //arduino
  { "pm",     Cmd_pinMode,       "  : pinMode" } ,
  { "dr",     Cmd_digitalRead,   "  : digitalRead(pin)" } ,
  { "dw",     Cmd_digitalWrite,  "  : digitalWrite(pin,val)" } ,
  { "dt",     Cmd_digitalToggle, "  : digitalToggle(pin)"  },
  { "aw",     Cmd_analogWrite,   "  : analogWrite(pin,val)"} ,
  { "ar",     Cmd_analogRead,    "  : analogRead(pin)"},
  { "si",     Cmd_shiftin,       "  : shiftIn([dpin cpin order])"} ,
  { "so",     Cmd_shiftout,      "  : shiftOut(val[ dpin cpin order])"},

  {  0, 0, 0 }
};
