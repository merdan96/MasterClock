
#ifndef DISPLAY_h
#define DISPLAY_h

#include "Common.h"
#include <LiquidCrystal.h>

/*****************************************************************
                    *  CONFIGURATIONS  * 
 *****************************************************************/
// Configure Paramter for number of Pages that can be displied.
#define MAX_DISPLAY_PAGES           5
#define MAX_TIME_ALLOWABLE          15

/*****************************************************************
                    *  Enumeration   * 
 *****************************************************************/

typedef enum
{
    DEFAULT_PAGE,
    SERVICES_PAGE,
    ASK_FOR_ID_PAGE,
    ASK_FOR_MINS_PAGE,
    ASK_FOR_COUNT_STYLE_PAGE
} Display_CurrentPage_t;

/*****************************************************************
                    *  GLOABAL FUNCTIONS  * 
 *****************************************************************/

void Display_Init();
void Display_UpdateClock();
void Display_Key(uint8_t key,uint8_t Pos);
void Display_ScrollSlaveStatus(uint8_t Key);
void Display_ClockStatusList(uint8_t CurrentClockID);
void Display_ChangePage(Display_CurrentPage_t Display_CurrentPage);
void Display_Message(char* Msg);
bool Page_Timeout();

#endif
