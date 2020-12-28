#include "Display.h"

// Configuration For Lcd
const int rs = 27, en = 26, d4 = 25, d5 = 24, d6 = 23, d7 = 22;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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
}
// Display Online Time
void Display_UpdateClock()
{
    // To be in the middle
    lcd.setCursor(5, 0);
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

void Display_ClockStatusList()
{
    // Max value for this loop will be 2 As it's only two line
    for (int LoopCounter = 0; LoopCounter < 2; LoopCounter++)
    {
        uint8_t Local_CurrentClockId = (MaxCurrent_ClockId + LoopCounter - 1);
        lcd.setCursor(0, (2+LoopCounter));
        lcd.print(String("Clock ") + String(Local_CurrentClockId));
        if (Clock_Status[Local_CurrentClockId] == ONLINE)
        {
            lcd.print(": ONLINE ");
        }
        else if (Clock_Status[Local_CurrentClockId] == OFFLINE)
        {
            lcd.print(": OFFLINE");
        }
        else if (Clock_Status[Local_CurrentClockId] == EXAM)
        {
            lcd.print(":  EXAM  ");
        }
        else
        {
            /* code */
        }
        
    }
}

void Display_Message(char* Msg)
{
    lcd.setCursor(0, 3);
    lcd.print(Msg);
}

