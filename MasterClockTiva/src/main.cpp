#include "clock/Clock.h"
#include "Common.h"
#include "Network/Network.h"
#include "AppLayer/Master.h"
#include "HMI/HMI.h"
void setup()
{
  Serial.begin(9600);
  Clock_Init();
  Display_Init();
  Network_Setup();
  Master_init();
  timerInit();
}
static uint32_t Sys_Tick = 0;
void loop()
{
  if (Sys_Tick % 10 == 0)
  {
    Master_MainFunctionUpdateClock();
  }
  if (Sys_Tick % 2 == 0)
  {
    HMI_MainFunction();
  }
  delay(50);
  Network_RecieveMainFunction();
  Sys_Tick++;
}