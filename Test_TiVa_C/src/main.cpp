#include <Arduino.h>
#include "UART.h"
#include "Rs_485.h"

char Buff[] = "#13:00";
char CommingByte[10];
static uint8_t count = 0;

void setup()
{
  // put your setup code here, to run once:
  pinMode(PB_3, OUTPUT);
  digitalWrite(PB_3, 1);
  Serial4.begin(19200);
  Serial.begin(19200);
}

void loop()
{
  if (millis() % 3000 == 0)
  {
    digitalWrite(PB_3, 1);
    delay(30);
    Buff[2] = '0' + count;
    count++;
    Serial4.print(Buff);
    delay(30);
    digitalWrite(PB_3, 0);
    if (count == 9)
    {
      count = 0;
    }
  }
  if (Serial4.available() > 0)
  {
    String str = Serial4.readString();
    Serial.println(str);
  }
}
