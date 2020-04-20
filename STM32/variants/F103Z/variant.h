
/* default variant infomations can be replaced by halConfig.h or board.txtmenu*/

#ifndef VARIANT_H
#define VARIANT_H


#if defined(ARDUINO_F103Z_UPTECH)
#  define VARIANT_PIN_LIST \
   PIN(A,0),  /* KEY1 */\
   PIN(A,1),  \
   PIN(A,2),  \
   PIN(A,3),  \
   PIN(A,4),  \
   PIN(A,5),  \
   PIN(A,6),  \
   PIN(A,7),  \
   PIN(A,8),  \
   PIN(A,9),  /* TX */\
   PIN(A,10), /* RX */\
   PIN(A,11),  /* USB D- */\
   PIN(A,12),  /* USB D+ */\
/*   PIN(A,13), SWDIO */\
/*   PIN(A,14), SWCLK */\
   PIN(A,15), \
   PIN(B,0),  /* LED3  */\
   PIN(B,1),  /* LED4  */\
   PIN(B,2),  /* BOOT1 */\
   PIN(B,3),  \
   PIN(B,4),  \
   PIN(B,5),  \
   PIN(B,6),  \
   PIN(B,7),  \
   PIN(B,8),  \
   PIN(B,9),  \
   PIN(B,10), \
   PIN(B,11), \
   PIN(B,12), \
   PIN(B,13), \
   PIN(B,14), \
   PIN(B,15), \
   PIN(C,0),  \
   PIN(C,1),  \
   PIN(C,2),  \
   PIN(C,3),  \
   PIN(C,4),  \
   PIN(C,5),  /* LED1 */\
   PIN(C,6),  /* LED2 */\
   PIN(C,7),  \
   PIN(C,8),  \
   PIN(C,9),  \
   PIN(C,10), \
   PIN(C,11), \
   PIN(C,12), \
   PIN(C,13), /* KEY0 */\
/*   PIN(C,14),   OSC32*/\
/*   PIN(C,15),   OSC32*/\
/*   PIN(D,0),    FSMC_D2*/\
/*   PIN(D,1),    FSMC_D3*/\
   PIN(D,2),  \
   PIN(D,3),  \
/*   PIN(D,4),  FSMC_NOE*/\
/*   PIN(D,5),  FSMC_NWE*/\
   PIN(D,6),  /* FSMC_NWAIT by arduino init */\
/*   PIN(D,7),  FSMC_NCE2*/\
/*   PIN(D,8),  FSMC_D13*/\
/*   PIN(D,9),  FSMC_D14*/\
/*   PIN(D,10), FSMC_D15*/\
/*   PIN(D,11), FSMC_A16/CLE*/\
/*   PIN(D,12), FSMC_A17/ALE*/\
/*   PIN(D,13), FSMC_A18*/\
/*   PIN(D,14), FSMC_D0*/\
/*   PIN(D,15), FSMC_D1*/\
/*   PIN(E,0),  FSMC_NBL0*/\
/*   PIN(E,1),  FSMC_NBL1*/\
/*   PIN(E,2),  FSMC_A23*/\
/*   PIN(E,3),  FSMC_A19*/\
/*   PIN(E,4),  FSMC_A20*/\
/*   PIN(E,5),  FSMC_A21*/\
/*   PIN(E,6),  FSMC_A22*/\
/*   PIN(E,7),  FSMC_D4*/\
/*   PIN(E,8),  FSMC_D5*/\
/*   PIN(E,9),  FSMC_D6*/\
/*   PIN(E,10), FSMC_D7*/\
/*   PIN(E,11), FSMC_D8*/\
/*   PIN(E,12), FSMC_D9*/\
/*   PIN(E,13), FSMC_D10*/\
/*   PIN(E,14), FSMC_D11*/\
/*   PIN(E,15), FSMC_D12*/\
/*   PIN(F,0),  FSMC_A0*/\
/*   PIN(F,1),  FSMC_A1*/\
/*   PIN(F,2),  FSMC_A2*/\
/*   PIN(F,3),  FSMC_A3*/\
/*   PIN(F,4),  FSMC_A4*/\
/*   PIN(F,5),  FSMC_A5*/\
   PIN(F,6),  \
   PIN(F,7),  /* KEY2 */\
   PIN(F,8),  \
   PIN(F,9),  \
   PIN(F,10), \
   PIN(F,11),  /* LED0 */\
/*   PIN(F,12), FSMC_A6*/\
/*   PIN(F,13), FSMC_A7*/\
/*   PIN(F,14), FSMC_A8*/\
/*   PIN(F,15), FSMC_A9*/\
/*   PIN(G,0),  FSMC_A10*/\
/*   PIN(G,1),  FSMC_A11*/\
/*   PIN(G,2),  FSMC_A12*/\
/*   PIN(G,3),  FSMC_A13*/\
/*   PIN(G,4),  FSMC_A14*/\
/*   PIN(G,5),  FSMC_A15*/\
/*   PIN(G,6),  FSMC_INT2*/\
   PIN(G,7),  \
   PIN(G,8),  \
/*   PIN(G,9),  FSMC_NE2*/\
/*   PIN(G,10), FSMC_NE3*/\
   PIN(G,11), \
   PIN(G,12), /*FSMC_NE4*/\
/*   PIN(G,13), FSMC_A24*/\
/*   PIN(G,14), FSMC_A25*/ \
   PIN(G,15),

#ifndef  PINA_MASK
#define  PINA_MASK  0b1000000111111111
#endif
#ifndef  PINB_MASK
#define  PINB_MASK  0b1111111111111111
#endif
#ifndef  PINC_MASK
#define  PINC_MASK  0b0011111111111111
#endif
#ifndef  PIND_MASK
#define  PIND_MASK  0b0000000001001100
#endif
#ifndef  PINE_MASK
#define  PINE_MASK  0b0000000000001000
#endif
#ifndef  PINF_MASK
#define  PINF_MASK  0b0000111111000000
#endif
#ifndef  PING_MASK
#define  PING_MASK  0b1001100110000000
#endif

#endif

/*LED*/
#ifndef LED_BUILTIN
# ifdef ARDUINO_F103Z_HAOYUCORE
    #define BOARD_NR_LED          1 
    #define LED_BUILTIN           PF6
    #define LED_BUILTIN_MASK	  0x01
# elif defined(ARDUINO_F103Z_UPTECH)
    #define BOARD_NR_LED          5 
    #define LED_BUILTIN           PF11
    #define LED1_BUILTIN          PC4
    #define LED2_BUILTIN          PC5
    #define LED3_BUILTIN          PB0
    #define LED4_BUILTIN          PB1
    #define LED5_BUILTIN          PF11
    #define LED_BUILTIN_MASK	  0x00
# endif
#endif

#ifndef LED_BUILTIN_MASK
 #define LED_BUILTIN_MASK		0x00
#endif
#define STM32_LED_BUILTIN_ACTIVE_LOW

/*KEYS*/
#if defined(ARDUINO_F103Z_UPTECH)
#define BOARD_NR_KEY 3
#define BUTTON  PC13
#define BUTTON1	PA0
#define BUTTON2	PF7
#define BUTTON_MASK         0x02
#endif

/*WKUP*/
#define SYS_WKUP1 	            PA0 /*for lowPower*/

/*SPI*/
#ifndef MOSI
 #define MOSI PA7
#endif
#ifndef MISO
 #define MISO PA6
#endif
#ifndef SCK
 #define SCK  PA5
#endif
#ifndef SS
 #define SS   PA4
#endif

/*I2C*/
#ifndef SDA
 #define SDA PB7
#endif
#ifndef SCL
 #define SCL PB6
#endif

/*usb*/
/******************** USB DIC ************************/
#ifdef ARDUINO_F103Z_HAOYUCORE
# ifndef USB_DISC_PIN
#   define USB_DISC_PIN      PF10  //103Zet6 core is PF10
# endif
#endif


#define GPIO_CLOCKOPEN  1  /*GPIO clock had opend by FSMC_Init*/

#endif
