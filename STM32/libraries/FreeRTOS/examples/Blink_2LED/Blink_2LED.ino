/*
  Blink_2LED.ino
  Turns 2 LEDs on/off , running in FreeRTOS V9.0/10.0

  This example code is in the public domain.
  Tested STM32 HALMX by huaweiwx@sina.com , May 2 2017
*/

#include <FreeRTOS.h>

#ifdef  LED_BUILTIN
# define LED    LED_BUILTIN
#	define LED_ON bitRead(LED_BUILTIN_MASK,0)
#else
#	define LED  13    //fixd me
#	define LED_ON 1   //fixd me
#endif

#ifdef LED1_BUILTIN
#	define LED1 LED1_BUILTIN
#	define LED1_ON bitRead(LED_BUILTIN_MASK,1)
#endif

static void myTask1(void  __attribute__ ((unused)) *argument)
{
  /*Task1 setup*/
  pinMode(LED, OUTPUT);

 
  uint32_t i = 0;
  /* USER CODE BEGIN Task1 */
  /* Infinite loop */
  for (;;)
  {
    digitalWrite(LED, LED_ON);	// turn the LED on (HIGH is the voltage level)
    vTaskDelay(50);				// wait for 50ms
    digitalToggle(LED);			// turn the LED off by making the voltage LOW
    vTaskDelay(950); 			// wait for 950ms
    i++;
    Serial << "Count:" << _HEX(i) << " in myTask1\n";   /*set USE_ARDUINOSTREAMING to 1 or include streaming.h*/
  }
  /* USER CODE END Task1 */
}

#if defined(LED1)
static void myTask2(void __attribute__ ((unused)) *argument)
{
  /*Task2 setup*/
  pinMode(LED1, OUTPUT);
  /* USER CODE BEGIN Task2 */
  /* Infinite loop */
  for (;;)
  {
    digitalWrite(LED1, LED1_ON);  // turn the LED on (HIGH is the voltage level)
    vTaskDelay(50);               // wait for 50ms
    digitalToggle(LED1);          // turn the LED off by making the voltage LOW
    vTaskDelay(200);              // wait for 2000msd
  }
  /* USER CODE END Task2 */
}
#endif

// the setup function runs once when you press reset or power the board.
void setup() {
  Serial.begin(115200);

  xTaskCreate(myTask1,                         /* Pointer to the function that implements the task. */
              NULL,                            /* Text name for the task.  This is to facilitate debugging only. */
              configMINIMAL_STACK_SIZE + 100,  /* Stack depth the task1 include the print func, add stack 100*/
              NULL,                            /* We are not using the task parameter. */
              tskIDLE_PRIORITY + 1,            /* This task will run at priority tskIDLE_PRIORITY + 1. */
              NULL);                           /* We are not using the task handle. */
#if defined(LED1)
  xTaskCreate(myTask2,
              NULL,
              configMINIMAL_STACK_SIZE,
              NULL,
              tskIDLE_PRIORITY,
              NULL);
#endif
  // osKernelStart();
  vTaskStartScheduler();  //FreeRTOS start and never return!
}

/****************  default idle hook callback if configUSE_IDLE_HOOK *******************
 * 1  STM32GENERIC loop() is default idle hook if enable(set configUSE_IDLE_HOOK to 1) *
 * 2  idle loop has a very small stack (check or set configMINIMAL_STACK_SIZE)         * 
 * 3  loop must never block.                                                           *
 * 4  This default idle hook can be overload by vApplicationIdleHook()                 * 
 ***************************************************************************************/
void loop() {
  for(;;){} //This example Not used.
}
