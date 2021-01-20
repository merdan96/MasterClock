#include "Rs_485.h"
#include <SoftwareSerial.h>
#include "Common.h"
// Obj Create for Software Serial
SoftwareSerial RS_485(RO_PIN, DI_PIN); // RX, TXc

void Rs485_Init()
{
    // Debug
    Serial.begin(9600);
    while (!Serial)
        ;
    //
    pinMode(DE_PIN, OUTPUT);
    pinMode(RE_PIN, OUTPUT);
    RS_485.begin(BAUD_RATE_TTL);
}

void Rs485_Tx(char *Str)
{
    digitalWrite(DE_PIN, ENABLE_TX);
    digitalWrite(RE_PIN, ENABLE_TX);
    RS_485.print(Str);
}

RetVal_t Rs485_Rx(char *Str)
{ 
    RetVal_t ret_val = E_NOT_OK;
    digitalWrite(DE_PIN, ENABLE_RX);
    digitalWrite(RE_PIN, ENABLE_RX);
    if (RS_485.available() > 0)
    {
        String Temp = RS_485.readString();
        strcpy(Str,Temp.c_str());
        ret_val = E_OK;
    }
    else
    {

    }
    return ret_val;
}
