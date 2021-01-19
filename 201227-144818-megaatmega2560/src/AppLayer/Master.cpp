#include "Master.h"

/* 
    * this file for declarition the Global & Static Apis
    * Master Component to handle the services Like "Resync/Change Slave mood"
    * Features : 
        - Sync slave clocks with RTC
        - ReSync RTC with NTP.
        - Publish Clock ,And change slave mood to be Exam

*/

/*****************************************************************
                    *  GLOBAL VARIABLES  * 
 *****************************************************************/
// Global Variable for holding the state of clocks.
ClockState_t Clock_Status[NUM_CLOCKS];
// Global Variable to keep the Service ID which beeing processed.
extern Master_CurrentServiceID_t Master_CurrentServiceID;

/*****************************************************************
                    *  STATIC VARIABLES  * 
 *****************************************************************/
// Static Array for holding The Clock Status.
static uint8_t Clock_HeartbeatPeriod[NUM_CLOCKS];
// Static Counter for Tracking Abstance of User.
static uint8_t TimeCount_UserAbstance = 0;
// Initilize the Service list to be false.
bool ServiceList_Status = false;

/*****************************************************************
                    *  STATIC FUNCTIONS  * 
 *****************************************************************/

// This static function For Check Slave Alive or not.
static void Check_SlaveHeartBeat()
{
    // Start looping from 1 because num 0 is the Master
    for (uint16_t LocalCounter = 1; LocalCounter <= NUM_CLOCKS; LocalCounter++)
    {
        // Cheking if it online so check it's heartbeat period
        if (Clock_Status[LocalCounter] == ONLINE)
        {
            if (Clock_HeartbeatPeriod[LocalCounter] == MAX_ALLOWABLE_PERIOD)
            {
                // if it exceed the max allowable then make it offline
                Clock_Status[LocalCounter] = OFFLINE;
            }
            else
            {
                // if it doesn't increament it's heartbeat
                Clock_HeartbeatPeriod[LocalCounter]++;
            }
        }
        else
        {
            // no need to do hear anything it should be online
            // if it ack for clk in Callback
        }
    }
}

static void Check_UserAbstance()
{
    if (TimeCount_UserAbstance == SCREEN_TIME_OUT)
    {
        // Un-activate any processing service.
        Master_UnactivateService();
        // Display Main Page.
        Display_ChangePage(DEFAULT_PAGE);
        ServiceList_Status = false;
    }
    else
    {
        TimeCount_UserAbstance++;
    }
}
/*****************************************************************
                    *  GLOBAL FUNCTIONS  * 
 *****************************************************************/
/*
    * Initalize Master if needed.
*/
void Master_init()
{
    // Initalize all Clocks to be zero & HeartBeat to be zero.
    for (uint8_t i = 0; i < NUM_CLOCKS; i++)
    {
        Clock_Status[i] = OFFLINE;
        Clock_HeartbeatPeriod[i] = 0; 
    }
}

/*
    * called every 500 ms, Fs >= 2*Fm  >> Nequist thresom.
    * update clock from Clock Source, Display, Publish clock on network.
    * check Heart beat from Clock Slaves.
*/

void Master_MainFunctionUpdateClock()
{
    // To Keep Track LastSecond.
    static uint8_t LastSecond = 0;
    // Call Clock To Update time.
    Clock_UpdateRealTime();
    // Check If new Second
    if (Master_Time.Second != LastSecond)
    {
        // Update LastSecond Elpased.
        LastSecond = Master_Time.Second;
        // Display only updated Clock.
        Display_UpdateClock();
        // Broadcast the clock to slaves.
        //Network_SentClockBroadCasting();
        // Checking For The Max Heartbeat-Period every second
        Check_SlaveHeartBeat();
        // Monitor The abcesnt of user
        Check_UserAbstance();
        // Refresh Default page if no service is working and Service List Also.
        if ((Master_CurrentServiceID == NOT_ACTIVE) &&
            (ServiceList_Status == false))
        {
            Display_ClockStatusList(1);
        }
    }
}

/*****************************************************************
                    *  CALL-BACKs FUNCTIONS  * 
 *****************************************************************/
// Call back From Capture Module. 
void Master_HandlerServices_CBK(uint8_t Key)
{
    Master_ServiceDisptacher(Key);
    TimeCount_UserAbstance = 0;
}


void Master_RxNotifcation_CBK(char *Response_Code, uint8_t Clock_Id)
{

#ifdef _DEBUG_SERIAL // for debugging purpose
    // Serial.println(Response_Code);
    // Serial.println(Clock_Id, DEC);
#endif

    switch (Response_Code[0])
    {
    case 'A': // That mean is Ack from Slave
        Clock_Status[Clock_Id] = ONLINE;
        Clock_HeartbeatPeriod[Clock_Id] = 0;
        break;

    case 'E': // That mean Exam Mode Is confirmed from Slave
        Clock_Status[Clock_Id] = EXAM;
        break;

    case 'S': // That mean is Start Exam from Slave
        Clock_Status[Clock_Id] = EXAM_START;
        break;

    case 'P': // That mean is Paused Exam from Slave
        Clock_Status[Clock_Id] = EXAM_PAUSED;
        break;

    default:
        break;
    }
}

void Master_RxGuiCommand_Cbk()
{
    
}

void Master_ScrollButton_CBK(uint8_t key)
{
    
}