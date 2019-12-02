/* i2cEepromConfig.h  specific board iic eeprom config file

   The definitions can be changed  by  HAL_Conf.h file
*/

#ifndef __BSP_I2CEEPROM_H__
#define __BSP_I2CEEPROM_H__
#include <Arduino.h>

#ifndef  AT24CXX_TYPE
# define AT24CXX_TYPE	AT24C02
#endif

#ifndef  AT24CXX_USE_I2Cx
# define AT24CXX_USE_I2Cx 1
#endif

#if defined(AT24CXX_USE_I2Cx) && (AT24CXX_USE_I2Cx == 3)

#ifndef  AT24CXX_DEV
# define AT24CXX_DEV	I2C3 	/*can use I2C2 port or SOFT IIC*/
#endif
#ifndef  AT24CXX_SCL
# define AT24CXX_SCL	PH7
#endif
#ifndef  AT24CXX_SDA
# define AT24CXX_SDA	PC9
#endif

#elif defined(AT24CXX_USE_I2Cx) && (AT24CXX_USE_I2Cx == 2)
	
#ifndef  AT24CXX_DEV
# define AT24CXX_DEV	I2C2 	/*can use I2C2 port or SOFT IIC*/
#endif
#ifndef  AT24CXX_SCL
# define AT24CXX_SCL	PF1
#endif
#ifndef  AT24CXX_SDA
# define AT24CXX_SDA	PH5
#endif

#elif defined(AT24CXX_USE_I2Cx) && (AT24CXX_USE_I2Cx == 1) /*I2C1*/
	
#ifndef  AT24CXX_DEV
# define AT24CXX_DEV	I2C1 	/*can use I2C2 port or SOFT IIC*/
#endif
#ifndef  AT24CXX_SCL
# define AT24CXX_SCL	PB6
#endif
#ifndef  AT24CXX_SDA
# define AT24CXX_SDA	PB7
#endif
#ifndef  AT24CXX_A2A1A0
# define AT24CXX_A2A1A0  0
#endif

#else
	
#endif /*I2C3*/

#ifndef  AT24CXX_A2A1A0
# define AT24CXX_A2A1A0 0
#endif

#endif   //__BSP_I2CEEPROM_H__