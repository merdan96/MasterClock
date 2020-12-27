
#ifndef DISPLAY_h
#define DISPLAY_h
#include "Common.h"
#include "LiquidCrystal.h"

typedef enum
{
    DEFAULT_PAGE,
    SERVICES_PAGE,
    ASK_FOR_ID_PAGE,
    ASK_FOR_MINS_PAGE,
    ASK_FOR_COUNT_STYLE_PAGE
} Display_CurrentPage_t;

// Extern 
extern Display_CurrentPage_t Display_CurrentPage;

void Display_UpdateClock();
void Display_Key(uint8_t key,uint8_t Pos);
void Display_ScrollSlaveStatus(uint8_t Key);
void Display_ClockStatusList();
void Display_ChangePage(Display_CurrentPage_t Display_CurrentPage);
void Display_Message(char* Msg);
void Display_Init();
void Display_ServicesPage();
bool Display_IsMaxPeriodElpased();
#endif
