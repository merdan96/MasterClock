#include "Capture/Capture.h"
#include "HMI/HMI_CBK.h"
#if (_IR_REMOTE_ == E_ON)
#include <IRremote.h>
#endif

#if (_KEY_PAD_ == E_ON)
#include <Keypad.h>
#endif

/*****************************************************************
                    *  CONFIGURATIONS  * 
 *****************************************************************/
#if (_KEY_PAD_ == E_ON)
// Keypad Configuration
const byte ROWS = 4; // rows
const byte COLS = 4; // columns

//define the symbols on the buttons of the keypads
char keys[ROWS][COLS] = {
    {'1', '4', '7', '*'},
    {'2', '5', '8', '0'},
    {'3', '6', '9', '#'},
    {'A', 'B', '-', '+'}};

byte colPins[ROWS] = {PB_6, PA_4, PA_3, PA_2}; //connect to the row pinouts of the keypad

byte rowPins[COLS] = {PC_7, PD_6, PD_7, PF_4}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
#endif

#if (_IR_REMOTE_ == E_ON)
// Get Key and call back the Software component "Master/Display"
IRrecv irrecv(37);
decode_results results;
/*****************************************************************
                    *  STATIC FUNCTIONS  * 
 *****************************************************************/

// Staic Function For converstion The Code capture from IR-Remote to ASCCI
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
#endif

/*****************************************************************
                    *  GLOBAL FUNCTIONS  * 
 *****************************************************************/

void Capture_init()
{
#if (_IR_REMOTE_ == E_ON)
    irrecv.enableIRIn();
    irrecv.blink13(true);
#endif
}

void Capture_MainFunction()
{
    char key = NO_KEY;

#if (_KEY_PAD_ == E_ON)
    key = keypad.getKey();
#endif

#if (_IR_REMOTE_ == E_ON)
    if (irrecv.decode(&results))
    {
        key = Convert_IRCode2Ascci(results.value);
        irrecv.resume();
    }
#endif

    // Check If there's key been pressed
    if (key != NO_KEY)
    {
#if (_DEBUG_SERIAL == E_ON)
        Serial.print("You pressed: ");
        Serial.println(key);
#endif
        if ((key == '+') || (key == '-'))
        {
            HMI_ScrollButton_CBK(key);
        }
        else
        {
            HMI_HandlerSession_CBK(key);
        }
    }
}
