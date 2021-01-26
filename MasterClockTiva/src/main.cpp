#include "clock/Clock.h"
#include "Common.h"


void setup()
{
  Serial.begin(9600);
  Clock_Init();
}

void loop()
{
  Clock_UpdateRealTime();
  Serial.print(Master_Time.Hour, DEC);
  Serial.print('/');
  Serial.print(Master_Time.Minute, DEC);
  Serial.print('/');
  Serial.println(Master_Time.Second, DEC);
  delay(3000);
}