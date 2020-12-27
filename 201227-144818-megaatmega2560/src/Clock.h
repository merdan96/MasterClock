#ifndef CLOCK_h
#define CLOCK_h

#include "Common.h"

// Config paramter Clock Source
/*
    * RTC
    * NTP
    * Gps
*/  
#define CLOCK_SOURC     _RTC_ 
//#define RTC_WRITE_ENABLE 

// Function for Set Clock 
void Clock_Init();

// Function for Update Time every Second
void Clock_UpdateRealTime();

// Re-sync Clock From USER to Clock Source.  
void Clock_ReSync();

#endif
