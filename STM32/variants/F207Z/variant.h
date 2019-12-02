#ifndef VARIANT_H
#define VARIANT_H

//LEDs
# ifdef ARDUINO_F207Z_HAOYUCORE
    #define BOARD_NR_LED          1 
    #define LED_BUILTIN           PF6
    #define LED_BUILTIN_MASK	  0x01
# endif

#define STM32_LED_BUILTIN_ACTIVE_HIGH

//KEYs
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

#define GPIO_CLOCKOPEN  1  /*GPIO clock had opend by FSMC_Init*/

#endif
