// wb32f10.ino // simple wifi boy esp32 system having 22 forth words
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "wb32v10.h" // having V as an instence of forth Virtual machine ////////////////////////////////
WB32V10 V = WB32V10();
#include "ws01.h" // having wordset 01 for base setting of number conversion ////////////////////////////
// 01. bin            ( -- )          set number conversion base B=2
// 02. oct            ( -- )          set number conversion base B=8
// 03. dec            ( -- )          set number conversion base B=10
// 04. hex            ( -- )          set number conversion base B=16
// 05. base!          ( b -- )        set number conversion base B=b
// 06. base@          ( -- B )        get number conversion base B
#include "ws02.h" // having wordset 02 for arithmetic operation /////////////////////////////////////////
// 07. +              ( a b -- a+b )  a add b
// 08. *              ( a b -- a*b )  a multiply b
// 09. -              ( a b -- a-b )  a subtract b
// 10. /              ( a b -- a/b )  a divide b
#include "ws03.h" // having wordset 03 for tools ////////////////////////////////////////////////////////
// 11. words          ( -- )          show all forth word names
//     words <string> ( -- )          show all forth word names including given string
// 12. see <name>     ( -- )          see the word of given name
// 13. dump           ( a n -- )      show n cells at address a
#include "ws04.h" // having wordset 04 for digital output ///////////////////////////////////////////////
// 14. led            ( -- LED_BUILTIN  )      give decimal LED_BUILTIN (gpio pin number of the blue led)
// 15. hi             ( pin -- )      pull up digital OUTPUT pin to electric level HIGH
// 16. lo             ( pin -- )      pull down digital OUTPUT pin to electric level LOW
// 17. toggle         ( pin -- v )    toggle digital OUTPUT pin to electric level HIGH/LOW
// 18. ms             ( n -- )        wait for n milliseconds
// 19. out            ( pin -- )      set gpio pin mode direction as OUTPUT
// 20. p!             ( v pin -- )    write v to digital OUTPUT pin (v=0 for LOW or v=1 for HIGH)
#include "ws05.h" // having wordset 05 for digital input ////////////////////////////////////////////////
// 21. inp            ( pin -- )      set gpio pin mode direction as INPUT
// 22. p@             ( pin -- v )    read v from digital INPUT pin (v=0 for LOW or v=1 for HIGH)
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200); delay(1000); // setting serial communification baud rate and waitting for ready
  Serial.printf("*********************************************\n");
  Serial.printf("* Simple STM32 System having 22 Forth Words *\n");
  Serial.printf("* By huaweiwx@sina.com  20180504            *\n");
  Serial.printf("*********************************************\n");
  V.vocInit(LAST);    // initializing vocabulary
  V.dsClear();        // clearing data stack
  pinMode(LED_BUILTIN,OUTPUT); // setting pin mode direction of gpio 16 (the blue led) as OUTPUT
  V.interpret("0x100 100 2 $20 -1 words"); // preloading 5 numbers and showing all the forth words
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  static int i=0;                   // setting index of input line
  V.showDataStack();                // showing depth, numbers, and number coversion base of data stack 
  Serial.printf("--------------------------------------------------\n");
  Serial.printf("inp %02d : ", i++); // asking for input line i
  V.waitInput();                    // waiting until input available
  char *line = V.readLine();        // reading input line (until caridge return)
  V.interpret(line);                // interpreting input line
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
