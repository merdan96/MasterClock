#ifndef COMMON_h
#define COMMON_h

// Ready-made For inculding Standard Lib for Arduino
#include <Arduino.h>
// Ready-made For inculding a standrad Data types
#include <inttypes.h>
// For debugging purpose Serial monitor
#include <HardwareSerial.h>
// Ready-made Time Paramters
#include <TimeLib.h>


/*****************************************************************
    *  COMMON Defination and DATA TYPES "don't Change" * 
 *****************************************************************/
#define E_OFF                   0
#define E_ON                    1
#define MASTER_CLOCK_ID         0

typedef enum
{   
    OFFLINE,
    ONLINE,
    EXAM,
    EXAM_START,
    EXAM_PAUSED,
} ClockState_t;

typedef enum
{
    E_NOT_OK,
    E_OK
} RetVal_t;

/*****************************************************************
                    *  COMMON CONFIGURATIONS  * 
 *****************************************************************/
// Enable or Disaple Debugging through Serial.
#define _DEBUG_SERIAL           E_OFF

// Enable or Disable GUI interface.
#define _GUI_                   E_OFF

// Numbers Of Slaves Clock.
#define NUM_CLOCKS              10

// Clock-ID to be get form the IP.
#define CLOCK_ID                MASTER_CLOCK_ID

/*****************************************************************
                    *  Extern VARIABLES || Obejcts  * 
 *****************************************************************/
//Serial Obj for debugging Purpose.
extern HardwareSerial Serial;
//Main entity Of Master Time
extern tmElements_t Master_Time;

//extern ClockState_t Clock_Status[NUM_CLOCKS];


#endif
