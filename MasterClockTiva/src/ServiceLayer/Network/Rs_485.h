#ifndef RS_485_H
#define RS_485_H

#include <Arduino.h>
#include "Common.h"


/*****************************************************************
                    *  CONFIGURATIONS  * 
 *****************************************************************/
// Baud rate for Uart
#define BAUD_RATE_TTL 19200
#define ENABLE_TX HIGH
#define ENABLE_RX LOW
#if (CLOCK_ID != 0)
#define DI_PIN 2
#define DE_PIN 3
#define RE_PIN 4
#define RO_PIN 5
#else
#define RE_DE_PIN PC_6

#endif

// Global API

void Rs485_Init();

void Rs485_Tx(char *Str);

RetVal_t Rs485_Rx(char *Str);

#endif