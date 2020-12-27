#include "Clock.h"
#include <Wire.h>
#include <DS1307RTC.h>

/* 
    * Struct to save time parametes 
    * uint8_t Second; 
    * uint8_t Minute; 
    * uint8_t Hour; 
    * uint8_t Wday;   // day of week, sunday is day 1
    * uint8_t Day;
    * uint8_t Month; 
    * uint8_t Year;   
*/
tmElements_t Master_Time;

// Function for Set Clock
void Clock_Init()
{
    // RTC, NTP, .....
}

void Clock_ReSync()
{
#ifdef RTC_WRITE_ENABLE
    // Update RTC
    if (RTC.write(Master_Time))
    {
    }
#endif
}
// Function for Update Time every Second
void Clock_UpdateRealTime()
{
#if (CLOCK_SOURC == _RTC_)
    if (RTC.read(Master_Time))
    {
#ifdef _Debug_Serial
//        Serial.println("Time updated Successfuly");
#endif
    }
    else
    {
#ifdef _Debug_Serial
        if (RTC.chipPresent())
        {
            Serial.println("The DS1307 is stopped.  Please run the SetTime");
            Serial.println("example to initialize the time and begin running.");
            Serial.println();
        }
        else
        {
            Serial.println("DS1307 read error!  Bus failed || Slave Doesn't Exist.");
            Serial.println();
        }
#endif
    }
#elif (CLOCK_SOURC == _NTP_)
    ay habel
#endif
}
