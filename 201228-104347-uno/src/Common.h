
#ifndef COMMON_h
#define COMMON_h

#include <inttypes.h>
#include <HardwareSerial.h>
#include <TimeLib.h>
#include "Common_Confg.h"

extern HardwareSerial Serial;
typedef enum
{
    E_NOT_OK,
    E_OK
} RetVal_t;
#endif
