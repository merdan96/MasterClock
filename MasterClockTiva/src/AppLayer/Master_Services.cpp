#include "AppLayer/Master.h"
#include "AppLayer/Master_Cfg.h"


//Maximum number of array digits "0->9999"
#define MAX_BUFF_SIZE 4

// To keep service ID Which is being Processed.
Master_CurrentServiceID_t Master_CurrentServiceID = NOT_ACTIVE;

// To keep Slave Request Info.
volatile SlaveModeInfo_T SlaveModeInfo;

// To keep Sub-service ID Which Processing.
SetSlaveModeSubSrvID_t SetSlaveModeSubSrvID = GET_SLAVE_ID;

// Buffer and Buffer-index for Keep the data Captured from User.
static char Buff_[MAX_BUFF_SIZE];
static uint8_t Buff_Index = 0;

extern bool ServiceList_Status;
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
    if (SlaveId < NUM_CLOCKS)
    {
        ret_val = 1;
    }
    else
    {
    }
    return ret_val;
}

/*****************************************************************
                    *  SERVIRCES FUNCTIONS  * 
 *****************************************************************/

void Master_UnactivateService()
{
    memset(Buff_, 0, sizeof(Buff_));
    Buff_Index = 0;
    SetSlaveModeSubSrvID = GET_SLAVE_ID;
    Master_CurrentServiceID = NOT_ACTIVE;
}

/*
    * Service ID: 0 
    * To Activate Master Services Table.
    * either through Quick/Direct Call.
    * OR through choshing from table.  
*/
void Master_ActivateService(uint8_t Key)
{
    // show Service list
    switch (Key)
    {
    case '#':
    {
        // Display List
        Display_ChangePage(SERVICES_PAGE);
        ServiceList_Status = 1;
        break;
    }
    case 'B':
    {
        // Display Default Page.
        Display_ChangePage(DEFAULT_PAGE);
        ServiceList_Status = 0;
        break;
    }
    case '1': // Direct Call
    {
        Master_CurrentServiceID = SLAVE_MODE_SET;
        Display_ChangePage(ASK_FOR_ID_PAGE);
        break;
    }
    case '2':
    {
        Master_ReSyncCLock(Key);
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
void Master_SetSlaveModeSrv(uint8_t Key)
{
    uint16_t Temp;
    switch (SetSlaveModeSubSrvID)
    {
    case GET_SLAVE_ID:
    {
        Temp = NewKey_HandlerRotuine(Key);
        if (Temp != 0)
        {
            if (Temp == 0xFFFF)
            {
                ServiceList_Status = 1;
                Display_ChangePage(SERVICES_PAGE);
                Master_CurrentServiceID = NOT_ACTIVE;
            }
            else
            {
                if (Check_SlavIdValid(Temp))
                {
                    SlaveModeInfo.Salve_ID = Temp;
                    // Go to next State
                    SetSlaveModeSubSrvID = GET_TIME_MIN;
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
                SetSlaveModeSubSrvID = GET_SLAVE_ID;
            }
            else
            {
                // Capture Time in mins which required.
                SlaveModeInfo.Time_mins = Temp;
                // Go to next State.
                SetSlaveModeSubSrvID = GET_COUNT_TYPE;
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
            SetSlaveModeSubSrvID = GET_TIME_MIN;
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
#ifdef _DEBUG_SERIAL // for debugging purpose
            // Serial.println(SlaveModeInfo.Salve_ID, DEC);
            // Serial.println(SlaveModeInfo.Time_mins, DEC);
            // if (SlaveModeInfo.CountStyle == COUNT_DOWN)
            // {
            //     Serial.println("Count down");
            // }
            // else
            // {
            //     Serial.println("Count Up");
            // }
#endif
            // Local array for Sent pakage
            char Data[8];
            /*  * Make sure that you sent 8 byte not less
            * Construct The frame to be sent "@" for command indication.
            * next 4 digit for minuts and.. 
            * last char 'U' for upword 'D' for downword.
        */
            sprintf(Data, "@%d%c   ", SlaveModeInfo.Time_mins,
                    (SlaveModeInfo.CountStyle == COUNT_DOWN) ? 'D' : 'U');
            // Sent The Request frame to slave id unicasting.
            Network_SentUniCasting(Data, SlaveModeInfo.Salve_ID);
            // Go back to intializtion state for Service and sub service.
            Master_UnactivateService();
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
void Master_ReSyncCLock(uint8_t Key)
{   
    tmElements_t temp;
    //Ntp_UpdateTime(&temp);
    Clock_ReSync(temp);
}

//Array of pointers to function return void takes uint8
void (*Mater_ServiceTable[MAX_SERVICES_NUM])(uint8_t) = {
    Master_ActivateService,
    Master_SetSlaveModeSrv,
    Master_ReSyncCLock,
   // Master_BTngn
};

void Master_ServiceDisptacher(uint8_t Key)
{
#if (_DEBUG_SERIAL == E_ON)
    // Serial.print("Called in service ID:");
    // Serial.println(Master_CurrentServiceID, DEC);
#endif
    // Disptacher for Services
    Mater_ServiceTable[Master_CurrentServiceID](Key);
}
