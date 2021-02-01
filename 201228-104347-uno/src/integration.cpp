#include <Arduino.h>
#include "Common.h"
#include "Display.h"
#include "Capture.h"
#include "Slave.h"
#include "Network.h"
#include <Arduino_FreeRTOS.h>

// define two tasks for Blink & AnalogRead
void Task_Display_mainFunction(void *pvParameters);
void TaskNetwork_RecieveMainFunction(void *pvParameters);

void setup()
{
#ifdef _Debug_Serial
  Serial.begin(9600);
  while (!Serial)
    ;
#endif
  // Network
  Network_Setup();
  Display_init();
  Capture_init();
  // Now set up two tasks to run independently.
  // xTaskCreate(
  //     Task_Display_mainFunction, 
  //     "Display" // A name just for humans
  //     ,
  //     128 // Stack size
  //     ,
  //     NULL,
  //     3 // priority
  //     ,
  //     NULL);

  // xTaskCreate(
  //     TaskNetwork_RecieveMainFunction,
  //     "Network",
  //     128 // This stack size can be checked & adjusted by reading Highwater
  //     ,
  //     NULL, 
  //     1,
  //     NULL);
  SREG |= (1 << 7);
}

void loop()
{
  Display_mainFunction();
  Network_RecieveMainFunction();
}

void Task_Display_mainFunction(void *pvParameters)
{
  for (;;)
  {
    Display_mainFunction();
    vTaskDelay(1 / portTICK_PERIOD_MS);
  }
}

void TaskNetwork_RecieveMainFunction(void *pvParameters)
{
  for (;;)
  {
    Network_RecieveMainFunction();
    vTaskDelay(100);
  }
}