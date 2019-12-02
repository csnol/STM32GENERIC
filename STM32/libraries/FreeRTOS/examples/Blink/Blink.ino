/*
  Blink.ino
  Turns LEDs on/off use LEDClass, demo running in FreeRTOS V10.0.

  This example code is in the public domain.
  Tested for STM32GENERIC   by huaweiwx@sina.com , May 2 2017
*/

#include <FreeRTOS.h>
#include <Streaming.h>
#include <LED.h>         /*LEDClass: Led Led1/2/3/4/5/6/7 has be predefiend */

/*Check environment configuration*/
/*default*/

static void myTask1(void  __attribute__ ((unused)) *argument)
{
  /*Task1 setup*/
  uint32_t i = 0;
  Serial.begin(115200);

  /* Infinite Task1 loop */
  for (;;)
  {
  /* USER CODE BEGIN Task1 */
    Serial << "Count:" << _HEX(i) << " in myTask1\n";
    i++;
    vTaskDelay(1000);
  /* USER CODE END Task1 */
   }
}

static void myTask2(void __attribute__ ((unused)) *argument)
{
  /*Task2 setup*/
  Led.Init();
  
  /* Infinite Task2 loop */
  for (;;)
  {
  /* USER CODE BEGIN Task2 */
    Led.flash(10,490,1);
  /* USER CODE END Task2 */
  }
}

// the setup function runs once when you press reset or power the board.
void setup() {
  xTaskCreate(myTask1,                      /* Pointer to the function that implements the task. */
              NULL,                         /* Text name for the task.  This is to facilitate debugging only. */
              configMINIMAL_STACK_SIZE+100, /* Stack depth the task1 include the print func, add stack 100*/
              NULL,                         /* We are not using the task parameter. */
              tskIDLE_PRIORITY + 1,         /* This task will run at priority tskIDLE_PRIORITY + 1. */ 
              NULL);                        /* We are not using the task handle. */
  xTaskCreate(myTask2,
              NULL,
              configMINIMAL_STACK_SIZE,
              NULL,
              tskIDLE_PRIORITY,              /* led use priority as idle */
              NULL);
  vTaskStartScheduler();  //FreeRTOS start and never return!
}

/****************  default idle hook callback if configUSE_IDLE_HOOK ***************************
 * 1  STM32GENERIC loop() is call by default idle hook if enable(set configUSE_IDLE_HOOK to 1) *
 * 2  Idle loop has a very small stack (check or set configMINIMAL_STACK_SIZE)                 * 
 * 3  Loop must never block.                                                                   * 
 * 4  This default idle hook can be overload by vApplicationIdleHook()                         * 
 ***********************************************************************************************/
void loop() {
  for(;;){} //This example Not used.
}
