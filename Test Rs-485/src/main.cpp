#include <Arduino.h>
#include "Rs_485.h"
#include "Common.h"

uint32_t Sys_Tick = 0, Count = 0;

void setup()
{
  // set the data rate for the SoftwareSerial port
  Rs485_Init();
}

#if (CLOCK_ID == MASTER_CLOCK_ID)
/*
 * Check first char == # >> Clock
 * Update ,,,
 * check first char == @ >> Comand
 * check Id Is yours 
 * Serve Request
 */
// From Master 2 Slave
char Data[][10] =
    {
        "#13:55",     // Clock
        "@0001U0120", // Comand Exam , 4 digit ID, Count style, 4digit mins
        "&0001A",     // 4 digit ID, Ack From Slave 2 master
        "&0001E",     // 4 digit ID, Exam conf From Slave 2 master
        "&0001S",     // 4 digit ID, Exam Start From Slave 2 master
        "&0001P"};    // 4 digit ID,  Pause From Slave 2 master

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

void loop()
{
  if (Sys_Tick % 5000 == 0)
  {
    //Network_TxBroadCasting();
    Rs485_Tx(Data[0]);
  }
  if (Sys_Tick % 500 == 0)
  {
    Rs485_RxMainFunction();
  }
  delay(1);
  Sys_Tick++;
}

#elif (CLOCK_ID == 1)
void loop()
{
  Rs485_RxMainFunction();
}

#elif (CLOCK_ID == 2)
void loop()
{
  Rs485_RxMainFunction();
}
#endif