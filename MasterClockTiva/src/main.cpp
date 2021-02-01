#include "clock/Clock.h"
#include "Common.h"
#include "Display/Display.h"
#include "Network/Network.h"
#include "AppLayer/Master.h"
#include "Capture/Capture.h"

void setup()
{
  Serial.begin(9600);
  Clock_Init();
  Display_Init();
  Network_Setup();
  //Master_init();
}
static uint32_t Sys_Tick = 0;
void loop()
{
  if (Sys_Tick % 50 == 0)
  {
    Master_MainFunctionUpdateClock();
  }
  if (Sys_Tick % 10 == 0)
  {
    Capture_MainFunction();
  }
  Network_RecieveMainFunction();
  delay(10);
  Sys_Tick++;
}