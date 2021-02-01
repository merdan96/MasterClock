#include "Display.h"

// Configuration For Lcd
LiquidCrystal lcd(PD_2, PE_4, PD_1, PB_1, PD_0, PB_0);

// Internal Variables
uint8_t MaxCurrent_ClockId = 2;

static void print2digits(int number)
{
    if (number >= 0 && number < 10)
    {
        lcd.write('0');
    }
    lcd.print(number);
}

/*****************************************************************
                    *  GLOABAL FUNCTIONS  * 
 *****************************************************************/

void Display_Init()
{
    lcd.begin(20, 4);
    Display_ChangePage(DEFAULT_PAGE);
}
// Display Online Time
void Display_UpdateClock()
{
    // To be in the middle
    lcd.setCursor(6, 0);
    print2digits(Master_Time.Hour);
    lcd.write(':');
    print2digits(Master_Time.Minute);
    lcd.write(':');
    print2digits(Master_Time.Second);
}

void Display_Key(uint8_t Key, uint8_t Pos)
{
    lcd.setCursor(Pos, 2);
    lcd.write(Key);
}

void Display_ScrollSlaveStatus(uint8_t Key)
{
    if (Key == '+')
    {
        // First Line
        lcd.setCursor(0, 2);
        lcd.print(String("Clock ") + String(MaxCurrent_ClockId) +
                  String(": Defult"));
        MaxCurrent_ClockId++;
        // Seconds Line
        lcd.setCursor(0, 3);
        lcd.print(String("Clock ") + String(MaxCurrent_ClockId) +
                  String(": Defult"));
    }
    else if (Key == '-')
    {
        if (MaxCurrent_ClockId >= 3)
        {
            // First Line
            lcd.setCursor(0, 3);
            lcd.print(String("Clock ") + String(MaxCurrent_ClockId - 1) +
                      String(": Defult"));
            MaxCurrent_ClockId--;
            // Seconds Line
            lcd.setCursor(0, 2);
            lcd.print(String("Clock ") + String(MaxCurrent_ClockId - 1) +
                      String(": Defult"));
        }
    }
    else
    {
        /* code */
    }
}

void Display_ClockStatusList(uint8_t CurrentClockID)
{
    // // Hold ClockId
    // uint8_t ClockId;
    // // Max value for this loop will be 2 As it's only two line in LCD
    // for (int LoopCounter = 0; LoopCounter < 2; LoopCounter++)
    // {
    //     // ClockId  = first clock Id + the line num.
    //     ClockId = CurrentClockID + LoopCounter;
    //     lcd.setCursor(0, (2 + LoopCounter));
    //     lcd.print(String("Clk ") + String(ClockId));
    //     switch (Clock_Status[ClockId])
    //     {
    //     case OFFLINE:
    //         lcd.print(": OFFLINE    ");
    //         break;
    //     case ONLINE:
    //         lcd.print(": ONLINE     ");
    //         break;
    //     case EXAM:
    //         lcd.print(": EXAM       ");
    //         break;
    //     case EXAM_START:
    //         lcd.print(": EXAM START ");
    //         break;
    //     case EXAM_PAUSED:
    //         lcd.print(": EXAM PAUSED");
    //         break;
    //     default:
    //         break;
    //     }
    // }
}

void Display_Message(char *Msg)
{
    lcd.setCursor(0, 3);
    lcd.print(Msg);
}
