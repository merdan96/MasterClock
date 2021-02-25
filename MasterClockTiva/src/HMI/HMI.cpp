#include "HMI.h"

/*****************************************************************
                    *  GLOBAL VARIABLES  * 
 *****************************************************************/

// For Current Scroll Item.
extern uint8_t Display_CurrentItemIndex;

// Max Allowable Scroll For the current Page.
extern uint8_t Display_MaxPageItem;

// To keep service ID Which is being Processed.
HMI_CurrentSessionID_t HMI_CurrentSessionID = NOT_ACTIVE;

// To keep Slave Request Info.
SlaveModeInfo_T SlaveModeInfo;

// To keep Sub-service ID Which Processing.
SetSlaveModeSubSessionID_t SetSlaveModeSubSessionID = GET_SLAVE_ID;

// Buffer and Buffer-index for Keep the data Captured from User.
static char Buff_[MAX_BUFF_SIZE];
static uint8_t Buff_Index = 0;

// Boolean for Make Sure To not Refresh Clock while List is exist.
bool SessionList_Status = false;

// Static Counter for Tracking Absence of User.
static uint8_t TimeCount_UserAbsence = 0;

/*****************************************************************
                    *  STATIC FUNCTIONS  * 
 *****************************************************************/

/*
    * Static Function for handle the routine of captured key
    * in every service and sub-service there's a common routine
    * Like Confirmation, Delete and New Digit key.
*/
static uint16_t NewKey_HandlerRotuine(uint8_t Key)
{

    // Return value
    uint16_t Ret_Val = 0;
    switch (Key)
    {
    case '#': // Confirmation To transit to next State.
    {
        // return the integer value which captured
        Ret_Val = atoi(Buff_);
        // Set buffer and index to zero intializtion state.
        memset(Buff_, 0, sizeof(Buff_));
        Buff_Index = 0;
        break;
    }
    case '*': // Delete the entered number as well as go back the pervoius page.
    {
        if (Buff_Index > 0)
        {
            Display_Key(' ', --Buff_Index);
            Buff_[Buff_Index] = 0;
        }
        else
        {
        }
        break;
    }
    case 'B':
    {
        Ret_Val = 0xFFFF; // this value meaning to go back pervoius page.
        Buff_Index = 0;
        break;
    }
    default: // any number is should be captured here to array.
    {
        if (Buff_Index < MAX_BUFF_SIZE)
        {
            Display_Key(Key, Buff_Index);
            Buff_[Buff_Index++] = Key;
        }
        else
        {
        }
        break;
    }
    }
    return Ret_Val;
}

// Static Function To check the Salve id is valid or not.
static bool Check_SlavIdValid(uint16_t SlaveId)
{
    bool ret_val = 0;
    // Num Clock Start From Zero-index {1,N}. As Zero is Master Clock
    if (SlaveId <= NUM_CLOCKS)
    {
        ret_val = 1;
    }
    else
    {
    }
    return ret_val;
}

/*****************************************************************
                    *  SESSION FUNCTIONS  * 
 *****************************************************************/

// Clear the session Paramters to be use again.
void HMI_UnactivateSession()
{
    memset(Buff_, 0, sizeof(Buff_));
    Buff_Index = 0;
    SetSlaveModeSubSessionID = GET_SLAVE_ID;
    HMI_CurrentSessionID = NOT_ACTIVE;
}

/*
    * Service ID: 0 
    * To Activate Master Services Table.
    * either through Quick/Direct Call.
    * OR through choshing from table.  
*/
void HMI_ActivateSession(uint8_t Key)
{
    // show Service list
    switch (Key)
    {
    case '#':
    {
        // Display List
        Display_ChangePage(SERVICES_PAGE);
        SessionList_Status = 1;
        break;
    }
    case 'B':
    {
        // Display Default Page.
        Display_ChangePage(DEFAULT_PAGE);
        SessionList_Status = 0;
        break;
    }
    case '1': // Direct Call
    {
        HMI_CurrentSessionID = SLAVE_MODE_SET;
        Display_ChangePage(ASK_FOR_ID_PAGE);
        break;
    }
    case '2':
    {
        HMI_ReSyncClockSession(Key);
        break;
    }
    default:
        break;
    }
}

/*
    * Service ID: 1 
    * To Change slave mode into EXAM through there sub serivce.
    1 Ask for Slave ID,
    2 Ask for Time Required, 
    3 Ask for Count Style.  
*/
void HMI_SetSlaveModeSession(uint8_t Key)
{
    uint16_t Temp;
    switch (SetSlaveModeSubSessionID)
    {
    case GET_SLAVE_ID:
    {
        Temp = NewKey_HandlerRotuine(Key);
        if (Temp != 0)
        {
            if (Temp == 0xFFFF)
            {
                //pressing back from open sessions return to main service page
                SessionList_Status = 1;
                Display_ChangePage(SERVICES_PAGE);
                HMI_CurrentSessionID = NOT_ACTIVE;
            }
            else
            {
                if (Check_SlavIdValid(Temp))
                {
                    SlaveModeInfo.Salve_ID = Temp;
                    // Go to next State
                    SetSlaveModeSubSessionID = GET_TIME_MIN;
                    // Display Next Page
                    Display_ChangePage(ASK_FOR_MINS_PAGE);
                }
                else
                {
                    Display_Message("Error!! Wrong ID");
                    Display_Key(' ', 0);
                    Display_Key(' ', 1);
                    Display_Key(' ', 2);
                    Display_Key(' ', 3);
                }
            }
        }
        else
        {
            /* code */
        }
        break;
    }
    case GET_TIME_MIN:
    {
        Temp = NewKey_HandlerRotuine(Key);

        if (Temp != 0)
        {
            if (Temp == 0xFFFF)
            {
                Display_ChangePage(ASK_FOR_ID_PAGE);
                SetSlaveModeSubSessionID = GET_SLAVE_ID;
            }
            else
            {
                // Capture Time in mins which required.
                SlaveModeInfo.Time_mins = Temp;
                // Go to next State.
                SetSlaveModeSubSessionID = GET_COUNT_TYPE;
                // Display Next Page For Count Style.
                Display_ChangePage(ASK_FOR_COUNT_STYLE_PAGE);
            }
        }
        else
        {
            /* code */
        }
        break;
    }
    case GET_COUNT_TYPE:
    {
        if (Key == '*')
        {
            // Go to Pervious State
            SetSlaveModeSubSessionID = GET_TIME_MIN;
            // Display Pervious Page
            Display_ChangePage(ASK_FOR_MINS_PAGE);
        }
        else
        {
            if (Key == '1')
            {
                SlaveModeInfo.CountStyle = COUNT_DOWN;
            }
            else if (Key == '2')
            {
                SlaveModeInfo.CountStyle = COUNT_UP;
            }
            else
            {
            }
            // Local array for Sent pakage
            char Data[9];

            sprintf(Data, "@%04d%c%04d", SlaveModeInfo.Time_mins,
                    (SlaveModeInfo.CountStyle == COUNT_DOWN) ? 'D' : 'U',
                    SlaveModeInfo.Salve_ID);
            Serial.println(Data);
            // Sent The Request frame to slave id unicasting.
            Master_HMICommand_CBK(Data);
            // Go back to intializtion state for Service and sub service.
            HMI_UnactivateSession();
            // Display the Default Page.
            Display_ChangePage(DEFAULT_PAGE);
        }
        break;
    }
    default:
        break;
    }
}

/*
    * Service ID: 2
    * To Resync Time with Clock Source.  
*/
void HMI_ReSyncClockSession(uint8_t Key)
{
    // tmElements_t temp;
    // //Ntp_UpdateTime(&temp);
    // Clock_ReSync(temp);
}

//Array of pointers to function return void takes uint8
void (*HMI_SessionTable[MAX_SESSION_NUM])(uint8_t) = {
    HMI_ActivateSession,
    HMI_SetSlaveModeSession,
    HMI_ReSyncClockSession

};

/*****************************************************************
                    *  CALL-BACKs FUNCTIONS  * 
 *****************************************************************/

void HMI_HandlerSession_CBK(uint8_t Key)
{
    // Disptacher for Services
    HMI_SessionTable[HMI_CurrentSessionID](Key);
    TimeCount_UserAbsence = 0;
}

void HMI_ScrollButton_CBK(uint8_t key)
{
    int8_t sign = (key == '+') ? 1 : -1;

    if (key == '-' && (Display_CurrentItemIndex > 1))
    {
        Display_CurrentItemIndex--;
    }
    else if (key == '+' && (Display_CurrentItemIndex < Display_MaxPageItem))
    {
        Display_CurrentItemIndex++;
    }
    else
    {
    }
}

static void Check_UserAbsence() //>hmi
{
    if (TimeCount_UserAbsence == SCREEN_TIME_OUT)
    {
        // Un-activate any processing service.
        HMI_UnactivateSession();
        // Display Main Page.
        Display_ChangePage(DEFAULT_PAGE);
        SessionList_Status = false;
    }
    else
    {
        TimeCount_UserAbsence++;
    }
}

uint32_t HamadaFeElBtngn = 0;
/* 
    * Called every 100 ms 
    * Check Capture 
    * User Abstant
    * 
*/
void HMI_MainFunction()
{
    Capture_MainFunction();
    Display_UpdateClock();
    if ((HamadaFeElBtngn % 10) == 0)
    {
        Check_UserAbsence();
        /*
     * Checking HMI_CurrentSessionID & SessionList_Status for both service
     * list operation selection and default page operation selection.
    */
    }
    if ((HMI_CurrentSessionID == NOT_ACTIVE) &&
        (SessionList_Status == false))
    {
        // Refresh Default page if no service is working and Service List Also.
        Display_ClockStatusList();
    }
    HamadaFeElBtngn++;
}
