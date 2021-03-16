#ifndef DISPLAY_h
#define DISPLAY_h

#define SEVSEGMENT_BCD
// #define SEVSEGMENT_MUX

#include "Common.h"

#if defined(SEVSEGMENT_MUX)
#include "SevSeg.h"
#elif defined(SEVSEGMENT_BCD)
#include "bcd.h"
#endif



void Display_init();
void Display_UpdateClock(uint32_t Clock);
void Display_mainFunction();
void Display_ExamMins(uint16_t Mins);
#endif
