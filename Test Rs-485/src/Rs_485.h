#ifndef RS_485_H
#define RS_485_H

#include <Arduino.h>


/*****************************************************************
                    *  CONFIGURATIONS  * 
 *****************************************************************/

// Baud rate for Uart
#define BAUD_RATE_TTL       9600
#define ENABLE_TX           HIGH
#define ENABLE_RX           LOW
#define DI_PIN              2
#define DE_PIN              3      
#define RE_PIN              4      
#define RO_PIN              5



// Global API 

void Rs485_Init();

void Rs485_Tx(char* Str);

void Rs485_RxMainFunction();


#endif