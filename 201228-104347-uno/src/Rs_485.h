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
#define RE_DE_PIN 2
#else
#define DI_PIN 8
#define DE_PIN 9
#define RE_PIN 10
#define RO_PIN 11
#endif

// Global API

void Rs485_Init();

void Rs485_Tx(char *Str);

RetVal_t Rs485_Rx(char *Str);

#endif