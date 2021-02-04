#include "Rs_485.h"
#include <HardwareSerial.h>

// Obj Create for Software Serial
#define RS_485 Serial1
void Rs485_Init()
{
    pinMode(DE_PIN, OUTPUT);
    pinMode(RE_PIN, OUTPUT);
    RS_485.begin(BAUD_RATE_TTL);
    RS_485.setModule(1);
    RS_485.setPins(UART1_PORTB);
}

void Rs485_Tx(char *Str)
{
    digitalWrite(DE_PIN, ENABLE_TX);
    digitalWrite(RE_PIN, ENABLE_TX);
    RS_485.print(Str);
}
uint8_t i = 0;
bool stringComplete = false;

bool Rs485_Rx(char *Str)
{
    bool ret_val = 0;
    digitalWrite(DE_PIN, ENABLE_RX);
    digitalWrite(RE_PIN, ENABLE_RX);
    while (RS_485.available())
    {
        // get the new byte:
        volatile char inChar = (char)Serial.read();
        // add it to the inputString:
        Str[i++] = inChar;
        // if the incoming character is a newline, set a flag
        // so the main loop can do something about it:
        if (inChar == '\n')
        {
            i = 0;
            String Temp = RS_485.readString();
            strcpy(Str, Temp.c_str());
            ret_val = 1;
        }
    }
    return ret_val;
}
