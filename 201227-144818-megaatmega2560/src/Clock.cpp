#include "Clock.h"
#include <Wire.h>
#include <DS1307RTC.h>

/*****************************************************************
                    *  GLOBAL VARIABLES  * 
 *****************************************************************/
// To hold The Time paramters,
tmElements_t Master_Time;

/*****************************************************************
                    *  GLOABAL FUNCTIONS  * 
 *****************************************************************/

// Function for Set Clock
void Clock_Init()
{
    // RTC, NTP, .....
}

// Re-sync Clock From USER to Clock Source.
void Clock_ReSync()
{
#if 0
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
#if (_DEBUG_SERIAL == E_ON)
        //Serial.println("Time updated Successfuly");
#endif
    }
    else
    {
#if (_DEBUG_SERIAL == E_ON)
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
