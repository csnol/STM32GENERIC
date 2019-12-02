#ifndef VARIANT_H
#define VARIANT_H

//LED
#define BOARD_NR_LED     1
#define LED_BUILTIN      PB13
#define LED_BUILTIN_MASK 1
#define STM32_LED_BUILTIN_ACTIVE_HIGH

//On-board user button
#define BOARD_NR_KEY	1
#define BUTTON			PC13
#define USER_BTN		BUTTON
#define BUTTON_MASK		0x00

#define MOSI PA7
#define MISO PA6
#define SCK PA5
#define SS PA4

#define SDA PB9
#define SCL PB8
#define I2C1_100KHZ_TIMING 0x2000090E
#define I2C2_100KHZ_TIMING 0x2000090E
#define I2C3_100KHZ_TIMING 0x2000090E

#define A0 PA0
#define A1 PA1
#define A2 PA4
#define A3 PB0
#define A4 PC1
#define A5 PC0

#define VARIANT_PIN_LIST \
   PIN(A,3 ), /* D0  */\
   PIN(A,2 ), /* D1  */\
   PIN(A,10), /* D2  */\
   PIN(B,3 ), /* D3  */\
   PIN(B,5 ), /* D4  */\
   PIN(B,4 ), /* D5  */\
   PIN(B,10), /* D6  */\
   PIN(A,8 ), /* D7  */\
   PIN(A,9 ), /* D8  */\
   PIN(C,7 ), /* D9  */\
   PIN(B,6 ), /* D10 */\
   PIN(B,15), /* D11 */\
   PIN(B,14), /* D12 */\
   PIN(B,13), /* D13 */\
   PIN(B,9 ), /* D14 */\
   PIN(B,8 ), /* D15 */\
     /* ST Morpho    */\
     /* CN7 Left Side*/\
   PIN(C,10), /* D16 / A0 */\
   PIN(C,12), /* D17 / A1 */\
   PIN(F,11), /* D18  */\
   PIN(A,13), /* D19  */\
   PIN(A,14), /* D20  */\
   PIN(A,15), /* D21  */\
   PIN(B,7 ), /* D22  */\
   PIN(C,13), /* D23  */\
   PIN(C,14), /* D24  */\
   PIN(C,15), /* D25  */\
   PIN(F,0 ), /* D26  */\
   PIN(F,1 ), /* D27  */\
   PIN(C,2 ), /* D28  */\
   PIN(C,3 ), /* D29  */\
 /* CN7 Right Side  */\
   PIN(C,11), /* D30 */\
   PIN(D,2 ), /* D31 */\
 /* CN10 Left Side */\
   PIN(C,9 ), /* D32 */\
 /* CN10 Right side */\
   PIN(C,8 ), /* D33  */\
   PIN(C,6 ), /* D34  */\
   PIN(C,5 ), /* D35  */\
   PIN(A,12), /* D36  */\
   PIN(A,11), /* D37  */\
   PIN(B,12), /* D38  */\
   PIN(B,11), /* D39  */\
   PIN(B,2 ), /* D40  */\
   PIN(B,1 ), /* D41  */\
   PIN(A,7 ), /* D42  */\
   PIN(A,6 ), /* D43  */\
   PIN(A,5 ), /* D44  */\
   PIN(C,4 ), /* D45  */\
   PIN(A,0 ), /* D46  */\
   PIN(A,1 ), /* D47  */\
   PIN(A,4 ), /* D48  */\
   PIN(B,0 ), /* D49  */\
   PIN(C,1 ), /* D50  */\
   PIN(C,0 ), /* D51  */

#endif
