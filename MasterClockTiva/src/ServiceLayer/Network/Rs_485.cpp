#include "Rs_485.h"
#include <HardwareSerial.h>
#include "Common.h"

// Obj Create for Software Serial
#define RS_485 Serial4
void Rs485_Init()
{
    pinMode(RE_DE_PIN, OUTPUT);
    RS_485.begin(BAUD_RATE_TTL);
}

void Rs485_Tx(char *Str)
{
    digitalWrite(RE_DE_PIN, ENABLE_TX);
    RS_485.print(Str);
}

RetVal_t Rs485_Rx(char *Str)
{
    RS_485.flush();
    RetVal_t ret_val = E_NOT_OK;
    digitalWrite(RE_DE_PIN, ENABLE_RX);
    if (RS_485.available() > 0)
    {
        String Temp = RS_485.readString();
        strcpy(Str, Temp.c_str());
        if (Str[0] == '&')
        {
            ret_val = E_OK;
        }
    }
    else
    {
    }
    return ret_val;
}
