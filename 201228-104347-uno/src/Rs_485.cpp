#include "Rs_485.h"
#include <HardwareSerial.h>
#include <SoftwareSerial.h>
#include "Common.h"
//SoftwareSerial Hamada_TestSerial(4,5);
//#define RS_485 Hamada_TestSerial
// Obj Create for Software Serial
#define RS_485 Serial


char buff[15];
int count = 0;
int FLAG = 0;

#ifndef RS_485
ISR(USART_RX_vect)
{
    buff[count++] = UDR0;
    if (count >= 6)
    {
        FLAG = 1;
    }
}
#endif

void Rs485_Init()
{
    pinMode(RE_DE_PIN, OUTPUT);
#ifdef RS_485
    RS_485.begin(BAUD_RATE_TTL);
#else
    UCSR0A |= 1 << U2X0;
    UCSR0B |= (1 << 7) | (1 << 4) | (1 << 3);
    UCSR0C |= (1 << 1) | (1 << 2);
    UBRR0L = 103; // 19200
    UBRR0H = 0;
#endif
}

void Rs485_Tx(char *Str)
{
    digitalWrite(RE_DE_PIN, ENABLE_TX);
    delay(30);
#ifdef RS_485
    RS_485.print(Str);
#else
#endif
}

RetVal_t Rs485_Rx(char *Str)
{
    RetVal_t ret_val = E_NOT_OK;
    digitalWrite(RE_DE_PIN, ENABLE_RX);
#ifdef RS_485
    if (RS_485.available() > 0)
    {
        String Temp = RS_485.readString();
        strcpy(Str, Temp.c_str());
        ret_val = E_OK;
    }
    else
    {
    }
#else
    if (FLAG)
    {
        FLAG = 0;
        ret_val = E_OK;
        strcpy(Str, buff);
        memset(buff, 0, count);
        count = 0;
    }
#endif
    return ret_val;
}
