#ifndef VARIANT_H
#define VARIANT_H

#define  BOARD_NR_LED 3
#define  LED_BUILTIN  		PB0
#define  LED_GREEN          LED_BUILTIN
#ifdef ARDUINO_NUCLEO_H743ZI2
#define  LED1_BUILTIN 		PE1
#define  LED_YELLOW         LED1_BUILTIN  // LD2
#else
#define  LED1_BUILTIN 		PB7
#define  LED_BLUE           LED1_BUILTIN  // LD2
#endif
#define  LED2_BUILTIN 		PB14
#define  LED_BUILTIN_MASK	0x07
#define  STM32_LED_BUILTIN_ACTIVE_HIGH

#define  BOARD_NR_KEY        1
#define  BUTTON              PC13 
#define  BUTTON_MASK         0x01

/*wkup_pins def*/
#ifdef PWR_WAKEUP_PIN1
#define  SYS_WKUP1 PA0
#endif
#ifdef PWR_WAKEUP_PIN2
#define  SYS_WKUP2 PC13
#endif
#ifdef PWR_WAKEUP_PIN3
#define  SYS_WKUP3 PE6 /* manually updated */
#endif
#ifdef PWR_WAKEUP_PIN4
#define  SYS_WKUP4 PA2
#endif
#ifdef PWR_WAKEUP_PIN5
#define  SYS_WKUP5 PC5
#endif


#define MOSI PA7
#define MISO PA6
#define SCK  PA5
#define SS   PA4

#define SDA  PB9
#define SCL  PB8

#define I2C1_100KHZ_TIMING 0x20404768
#define I2C2_100KHZ_TIMING 0x20404768
#define I2C3_100KHZ_TIMING 0x20404768
#define I2C4_100KHZ_TIMING 0x20404768


#endif
