#ifndef MASTER_h
#define MASTER_h

#include "Common.h"
#include "Display.h"
#include "Clock.h"
#include "Network.h"
#include "Master_Cfg.h"

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


// Decalrition of Global Functions.
void Master_MainFunctionUpdateClock();
void Master_init();
void Master_UnactivateService();
void Master_ServiceDisptacher(uint8_t Key);

// Declirtion of private functuins
void Master_ReSyncCLock(uint8_t Key);


#endif
