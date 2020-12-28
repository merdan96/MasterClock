#ifndef CLOCK_h
#define CLOCK_h

#include "Common.h"



/*****************************************************************
                    *  CONFIGURATIONS  * 
 *****************************************************************/

// Config paramter Clock Source
/*  _RTC_  , _NTP_ , _GPS_   */  
#define CLOCK_SOURC     _RTC_ 


/*****************************************************************
                    *  GLOABAL FUNCTIONS  * 
 *****************************************************************/

// Function for init Clock 
void Clock_Init();
// Function for Update Time every Second
void Clock_UpdateRealTime();
// Re-sync Clock From USER to Clock Source.  
void Clock_ReSync();

#endif
