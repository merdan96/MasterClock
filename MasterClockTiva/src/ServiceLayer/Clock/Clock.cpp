#include "Clock.h"
#include "RTClib.h"

RTC_DS1307 rtc;

/*****************************************************************
                    *  GLOBAL VARIABLES  * 
 *****************************************************************/
// To hold The Time paramters,
tmElements_t Master_Time;

/*****************************************************************
                    *  GLOABAL FUNCTIONS  * 
 ****************************************************************/

// Function for Set Clock
void Clock_Init()
{
    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC");
    }
//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

// Re-sync Clock From USER to Clock Source.
void Clock_ReSync(tmElements_t tm)
{   
    
}

// Function for Update Time every Second
void Clock_UpdateRealTime()
{
    DateTime now = rtc.now();
    Master_Time.Hour = now.hour();
    Master_Time.Minute = now.minute();
    Master_Time.Second = now.second();
}
