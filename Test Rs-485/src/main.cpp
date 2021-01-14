#include <Arduino.h>
#include "Rs_485.h"

uint32_t Sys_Tick = 0, Count = 0;

void setup()
{
  // set the data rate for the SoftwareSerial port
  Rs485_Init();
}

/*
 *  check first char == # >> Clock
 * Update ,,,
 * check first char == @ >> Comand
 * check Id Is yours 
 * Serve Request
 */
// From Master 2 Slave
char Data[][10] =
    {
        "#13:55",
        "@0001U0120",
        "&0001A",
        "&0001E",
        "&0001S",
        "&0001P"};

void Network_TxBroadCasting()
{
  if (Count < 6)
  {
    Rs485_Tx(Data[Count++]);
  }
  else
  {
    Count = 0;
  }
}

void Network_RxMainFunction()
{
  Rs485_RxMainFunction();
}

void loop()
{
  // run over and over
  if (Sys_Tick % 30 == 0)
  {
    Network_TxBroadCasting();
  }
  Network_RxMainFunction();
  delay(100);
  Sys_Tick++;
}