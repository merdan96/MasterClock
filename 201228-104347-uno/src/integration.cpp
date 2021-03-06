#include <Arduino.h>
#include "Common.h"
#include "Display.h"
#include "Capture.h"
#include "Slave.h"
#include "Network.h"
#include <Arduino_FreeRTOS.h>

void setup()
{
#ifdef _Debug_Serial
  Serial.begin(19200);
  while (!Serial);
#endif
  Network_Setup();
  Display_init();
  Capture_init();
}

void loop()
{
  Display_mainFunction();
  Network_RecieveMainFunction();
  Slave_MainFunction();
  Capture_MainFunction();
}

