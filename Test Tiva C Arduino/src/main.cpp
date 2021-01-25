// include the library code:
#include <Arduino.h>

void setup()
{
  pinMode(RED_LED,OUTPUT);
}

void loop()
{
  digitalWrite(RED_LED,HIGH);
  delay(1000);
  digitalWrite(RED_LED,LOW);
  delay(1000);
}