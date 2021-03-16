#include "Capture.h"
#include "Slave.h"

IRrecv irrecv(3);
decode_results results;

static char Convert_IRCode2Ascci(uint32_t Code)
{
    char Ret_Val = 0;
    if (Code != 0xFFFFFFFF)
    {
        switch (Code)
        {
        case 0xFFA25D:
            Ret_Val = '1';
            break;
        case 0xFF629D:
            Ret_Val = '2';
            break;
        case 0xFFE21D:
            Ret_Val = '3';
            break;
        case 0xFF22DD:
            Ret_Val = '4';
            break;
        case 0xFF02FD:
            Ret_Val = '5';
            break;
        case 0xFFC23D:
            Ret_Val = '6';
            break;
        case 0xFFE01F:
            Ret_Val = '7';
            break;
        case 0xFFA857:
            Ret_Val = '8';
            break;
        case 0xFF906F:
            Ret_Val = '9';
            break;
        case 0xFF6897:
            Ret_Val = '*';
            break;
        case 0xFF9867:
            Ret_Val = '0';
            break;
        case 0xFFB04F:
            Ret_Val = '#';
            break;
        case 0xFF18E7:
            Ret_Val = '+';
            break;
        case 0xFF4AB5:
            Ret_Val = '-';
            break;
        case 0xFF5AA5:
            Ret_Val = '>';
            break;
        case 0xFF10EF:
            Ret_Val = '<';
            break;
        case 0xFF38C7:
            Ret_Val = '#';
            break;
        default:
            break;
        }
    }
    return Ret_Val;
}

void Capture_init()
{
    irrecv.enableIRIn();
    //irrecv.blink13(true);
}

void Capture_MainFunction()
{
    char key = 0;

    if (irrecv.decode(&results))
    {
        key = Convert_IRCode2Ascci(results.value);
        irrecv.resume();
    }

    if (key != 0)
    {
#ifdef _Debug_Serial // for debugging purpose
        Serial.print("You pressed: ");
        Serial.println(key);
#endif
      // Do what ever
      Slave_HandlerService_CBK(key);
   
    }
}
