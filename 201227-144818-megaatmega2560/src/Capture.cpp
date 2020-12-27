#include "Capture.h"
// Temporary include
#include "Master_CBK.h"
#include "Display.h"

// Configurations
const byte ROWS = 4; // rows
const byte COLS = 4; // columns

//define the symbols on the buttons of the keypads
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', '-'},
    {'*', '0', '#', '+'}};

//connect to the row pinouts of the keypad
byte rowPins[ROWS] = {32, 33, 34, 35};

//connect to the column pinouts of the keypad
byte colPins[COLS] = {28, 29, 30, 31};

//initialize an instance of class NewKeypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Get Key and call back the Software component "Master/Display"
IRrecv irrecv(37);
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
    irrecv.blink13(true);
}

void Capture_MainFunction()
{
    char key = 0;

#ifdef _KEYPAD_ENABLE
    key = keypad.getKey();
#endif

#ifdef _IR_ENABLE
    if (irrecv.decode(&results))
    {
        key = Convert_IRCode2Ascci(results.value);
        irrecv.resume();
    }
#endif

    if (key != NO_KEY)
    {
#ifdef _Debug_Serial 
        Serial.print("You pressed: ");
        Serial.println(key);
#endif
        /*
            * Check the key pressed 
            * if '+','-' goto Display_Scroll
            * if '#','0':'9' go to Master services
        */

        if ((key == '#') || (key == '*') ||
            ((key >= '0') && (key <= '9')))
        {
            Master_HandlerServices_CBK(key);
        }
        else if ((key == '+') || (key == '-'))
        {
            Display_ScrollSlaveStatus(key);
        }
        else
        {
            /* code */
        }
    }
}
