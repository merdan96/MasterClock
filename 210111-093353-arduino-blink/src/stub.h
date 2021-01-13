#ifndef STUB_h
#define STUB_h
#include "Common.h"

typedef enum
{
    DEFAULT_PAGE,
    SERVICES_PAGE,
    ASK_FOR_ID_PAGE,
    ASK_FOR_MINS_PAGE,
    ASK_FOR_COUNT_STYLE_PAGE
} Display_CurrentPage_t;

void Display_Key(uint8_t key, uint8_t Index);
void Display_ChangePage(Display_CurrentPage_t Display_CurrentPage);

void Network_SentClockBroadCasting();
void Network_SentUniCasting(char *data, uint8_t Slave_ID);
void Ntp_UpdateTime(tmElements_t* Tm);
void Clock_UpdateRealTime();
void Clock_ReSync(tmElements_t tm);
void Display_Message(char*);
void Display_UpdateClock();
void Display_ClockStatusList(uint8_t);
#endif
