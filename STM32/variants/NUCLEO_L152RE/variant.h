#ifndef VARIANT_H
#define VARIANT_H

//LED
#define BOARD_NR_LED    1
#define LED_BUILTIN PA5
#define LED_BUILTIN_MASK 1
#define STM32_LED_BUILTIN_ACTIVE_HIGH

//On-board user button
#define BOARD_NR_KEY	1
#define BUTTON			PC13  // 2
#define USER_BTN		BUTTON  // 2
#define BUTTON_MASK		0x00

#define MOSI PA7
#define MISO PA6
#define SCK PA5
#define SS PA4

#define SDA PB9
#define SCL PB8

#define A0 PA0
#define A1 PA1
#define A2 PA4
#define A3 PB0
#define A4 PC1
#define A5 PC0

#define VARIANT_PIN_LIST \
/* CN9 right Side    */\
   PIN(A,3 ), /* D0  */\
   PIN(A,2 ), /* D1  */\
   PIN(A,10), /* D2  */\
   PIN(B,3 ), /* D3  */\
   PIN(B,5 ), /* D4  */\
   PIN(B,4 ), /* D5  */\
   PIN(B,10), /* D6  */\
   PIN(A,8 ), /* D7  */\
/* CN5 right Side    */\
   PIN(A,9 ), /* D8  */\
   PIN(C,7 ), /* D9  */\
   PIN(B,6 ), /* D10 */\
   PIN(A,7 ), /* D11 */\
   PIN(A,6 ), /* D12 */\
   PIN(A,5 ), /* D13 */\
   PIN(B,9 ), /* D14 */\
   PIN(B,8 ), /* D15 */\
     /* ST Morpho    */\
     /* CN7 Left Side*/\
   PIN(C,10), /* D16  */\
   PIN(C,12), /* D17  */\
   PIN(A,13), /* D18  */\
   PIN(A,14), /* D19  */\
   PIN(A,15), /* D20  */\
   PIN(B,7 ), /* D21  */\
   PIN(C,13), /* D22  */\
   PIN(C,14), /* D23  */\
   PIN(C,15), /* D24  */\
 /*  PIN(H,0 ),  D25  PD0/H0/F0*/\
 /*  PIN(H,1 ),  D26  PD0/H0/F0*/\
   PIN(C,2 ), /* D27  */\
   PIN(C,3 ), /* D28  */\
 /* CN7 Right Side    */\
   PIN(C,11), /* D29  */\
   PIN(D,2 ), /* D30  */\
 /* CN10 Right Side   */\
   PIN(C,9 ), /* D31  */\
 /* CN10 Left Side    */\
   PIN(C,8 ), /* D32  */\
   PIN(C,6 ), /* D33  */\
   PIN(C,5 ), /* D34  */\
   PIN(A,12), /* D35  */\
   PIN(A,11), /* D36  */\
   PIN(B,12), /* D37  */\
   PIN(B,11), /* D38  */\
   PIN(B,2 ), /* D39  */\
   PIN(B,1 ), /* D40  */\
   PIN(B,15), /* D41  */\
   PIN(B,14), /* D42  */\
   PIN(B,13), /* D43  */\
   PIN(C,4 ), /* D44  */\
 /* CN8 lift side    */\
   PIN(A,0 ), /* A0/D45 */\
   PIN(A,1 ), /* A1/D46 */\
   PIN(A,4 ), /* A2/D47 */\
   PIN(B,0 ), /* A3/D48 */\
   PIN(C,1 ), /* A4/D49 */\
   PIN(C,0 ), /* A5/D50 */


#endif
