#ifndef FRAME_PARSE_H
#define FRAME_PARSE_H

#include <Arduino.h>
#include "Common.h"

/*****************************************************************
 *                   *  FRAMES  *                                *
 *****************************************************************/
typedef struct
{
    //"#13:55"    >>  Clock
    char Frame_Id;
    char Hour[2];
    char Clock_Sign;
    char Minuts[2];
} SyncCLockFrame_t;

typedef struct
{
    //@0120U0001   >>  Command
    char Frame_Id;
    char mins_arr[4];
    char CountStyle;
    char Slave_ID[4];
} ExamCommandFrame_t;

typedef struct
{
    //&0001A       >>  FeedBack
    char Frame_Id;
    char Slave_ID[4];
    char FeedBack;
} FeedBackFrame_t;

// Global API
void Frame_Parsing(const char *Data);

#endif