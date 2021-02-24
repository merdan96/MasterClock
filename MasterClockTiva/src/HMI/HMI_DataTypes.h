#include "Common.h"

typedef enum
{
    NOT_ACTIVE,
    SLAVE_MODE_SET,
    RESYNC_CLOCK,
} HMI_CurrentSessionID_t;

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
} SetSlaveModeSubSessionID_t;
