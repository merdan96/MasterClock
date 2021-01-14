#ifndef RS_485_H
#define RS_485_H

#include <Arduino.h>


/*****************************************************************
                    *  CONFIGURATIONS  * 
 *****************************************************************/
// Baud rate for Uart
#define BAUD_RATE_TTL       4800
#define CONTROL_PIN         4 
#define ENABLE_TX           HIGH
#define ENABLE_RX           LOW
#define TX_PIN              3
#define RX_PIN              2      


// Global API 

void Rs485_Init();

void Rs485_Tx(char* Str);

void Rs485_RxMainFunction();


#endif