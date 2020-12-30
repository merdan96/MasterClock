#ifndef MASTER_h
#define MASTER_h

#include "Common.h"
#include "Display.h"
#include "Clock.h"
#include "Network.h"


/*****************************************************************
                    *  CONFIGURATIONS  * 
 *****************************************************************/
// The max period for Slave to ack after that will conside to be offline.
#define MAX_ALLOWABLE_PERIOD              5  
// The max number of Servivces that master offer.
#define MAX_SERVICES_NUM                  3
// The Max Time-out to not return main Page.   
#define SCREEN_TIME_OUT                   5

// Decalrition of Global Functions.
void Master_MainFunctionUpdateClock();
void Master_init();
void Master_UnactivateService();
void Master_ServiceDisptacher(uint8_t Key);

// Shawaya enums and data types 3la زوقك ^^
typedef enum
{
    NOT_ACTIVE,
    SLAVE_MODE_SET,
    RESYNC_CLOCK,
} Master_CurrentServiceID_t;

typedef enum
{
    COUNT_DOWN,
    COUNT_UP
} CountStyle_t;

typedef struct
{
    uint8_t Salve_ID;
    uint16_t Time_mins;
    CountStyle_t CountStyle;
} SlaveModeInfo_T;

typedef enum
{
    S_IDLE,
    GET_SLAVE_ID,
    GET_TIME_MIN,
    GET_COUNT_TYPE,
    FINAL_REQ
} SetSlaveModeSubSrvID_t;

extern ClockState_t Clock_Status[NUM_CLOCKS];

#endif
