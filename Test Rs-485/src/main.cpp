#include <Arduino.h>
#include "Rs_485.h"

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
//char Data[] = "#13:55";
//char Data[] = "@0001U0120";

// // From Slave 2 Masters
char Data[] = "&0001A"; // Ack for being online.
// char Data[] = "&0001E"; // Exam meaning not yet started.
// char Data[] = "&0001S"; // Start meaning exam started.
// char Data[] = "&0001P"; // Paused meaing it stopped now.

void loop()
{
  // run over and over
  Rs485_Tx(Data);
  //Rs485_RxMainFunction();
  delay(1000);
}