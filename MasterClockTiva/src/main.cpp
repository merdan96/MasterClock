#include "clock/Clock.h"
#include "Common.h"
#include "Display/Display.h"
#include "Network/Network.h"

void setup()
{
  Serial.begin(9600);
  Clock_Init();
  Display_Init();
  Network_Setup();
}
int count =0;
void loop()
{
  Clock_UpdateRealTime();
  Display_UpdateClock();
  if (Master_Time.Second % 15 == 0)
  {
    Network_SentClockBroadCasting();
  }
  Serial.print(Master_Time.Hour, DEC);
  Serial.print('/');
  Serial.print(Master_Time.Minute, DEC);
  Serial.print('/');
  Serial.println(Master_Time.Second, DEC);
  delay(1000);
}