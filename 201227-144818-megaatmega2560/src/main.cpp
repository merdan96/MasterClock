#include "Common.h"
#include <Display.h>
#include <Capture.h>
#include <Clock.h>
#include <Master.h>
#include <Network.h>

unsigned long Sys_Tick = 0;
void setup()
{
#if (_DEBUG_SERIAL == E_ON)
  Serial.begin(9600);
  while (!Serial);
#endif
  // Network
  //Network_Setup();
  // Print Slave Status
  Capture_init();
  Master_init();
  Display_Init();
}

void loop()
{
  if ((Sys_Tick % 5) == 0)
  {
    Master_MainFunctionUpdateClock();
  //  Network_RecieveMainFunction();
  }
  Capture_MainFunction();
  delay(100);
  Sys_Tick++;
}
