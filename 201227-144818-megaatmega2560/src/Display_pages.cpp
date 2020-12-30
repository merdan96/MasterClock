#include "Display.h"

/*****************************************************************
                    *  GLOABAL VARIABLES  * 
 *****************************************************************/

// Golbal for holding the current displied Page.
Display_CurrentPage_t Sdisplay_CurrentPage = DEFAULT_PAGE;
uint8_t STime_counter = 0;

/*****************************************************************
                    *  EXTERN VARIABLES  * 
 *****************************************************************/

// Extern localy Lcd Obj.
extern LiquidCrystal lcd;

/*****************************************************************
                    *  STATIC FUNCTIONS  * 
 *****************************************************************/

// Display default Page
static void Display_DefaultPage()
{
    lcd.setCursor(0, 1);
    lcd.print("Clk Id : State      ");
    lcd.setCursor(0, 2);
    lcd.print("Clk 1 :  ONLINE     ");
    lcd.setCursor(0, 3);
    lcd.print("Clk 2 :  ONLINE     ");
  //  Display_ClockStatusList();
}

static void Display_ServicesPage()
{
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Enter Operation");
    lcd.setCursor(0, 2);
    lcd.print("1-Set Exam");
    lcd.setCursor(0, 3);
    lcd.print("2-Sync Clock");
}

static void Display_AskForIdPage()
{
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Enter Slave ID");
}

static void Display_AskForMinsPage()
{
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Enter Time in Minute");
}

static void Display_AskforCountStylePage()
{
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Enter Count Style");
    lcd.setCursor(0, 2);
    lcd.print("1-Count Down");
    lcd.setCursor(0, 3);
    lcd.print("2-Count UP");
}
/*****************************************************************
                    *  STATIC VARIABLES  * 
 *****************************************************************/

//Array of pointers to function return void takes uint8
static void (*Dipslay_ArryOfPages[MAX_DISPLAY_PAGES])() =
    {
        Display_DefaultPage,
        Display_ServicesPage,
        Display_AskForIdPage,
        Display_AskForMinsPage,
        Display_AskforCountStylePage,
};

/*****************************************************************
                    *  GLOBAL FUNCTIONS  * 
 *****************************************************************/

void Display_ChangePage(Display_CurrentPage_t Display_CurrentPage)
{
    Sdisplay_CurrentPage = Display_CurrentPage;
    STime_counter = 0;
#if (_DEBUG_SERIAL == E_ON)
    Serial.print("Display page num:");
    Serial.println(Sdisplay_CurrentPage, DEC);
#endif
    Dipslay_ArryOfPages[Display_CurrentPage]();
}

/* 
    * Time trigger function to handle the absence of user
    * Trigger every 1 sec.
*/
bool Page_Timeout()
{
    bool Ret_Val = 0;
    if (Sdisplay_CurrentPage != DEFAULT_PAGE)
    {
        if (STime_counter == MAX_TIME_ALLOWABLE)
        {
            Ret_Val = 1;
            Display_ChangePage(DEFAULT_PAGE);
        }
        else
        {
            STime_counter++;
        }
    }
    return Ret_Val;
}