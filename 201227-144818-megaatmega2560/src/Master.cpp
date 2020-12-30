#include "Master.h"

#define SCREEN_TIME_OUT     5
/*****************************************************************
                    *  GLOBAL VARIABLES  * 
 *****************************************************************/
// Global Variable for holding the state of clocks.
ClockState_t Clock_Status[NUM_CLOCKS] = {0};

/*****************************************************************
                    *  STATIC VARIABLES  * 
 *****************************************************************/
// Initalize all Clocks to be zero
static uint8_t Clock_HeartbeatPeriod[NUM_CLOCKS] = {0};
static uint8_t TimeCount_UserAbstance = 0;
/*****************************************************************
                    *  STATIC FUNCTIONS  * 
 *****************************************************************/

static void Check_SlaveHeartBeat()
{
    // Start looping from 1 because num 0 is the Master
    for (uint16_t LocalCounter = 1; LocalCounter < NUM_CLOCKS; LocalCounter++)
    {
        // Cheking if it online so check it's heartbeat period
        if (Clock_Status[LocalCounter] == ONLINE)
        {
            if (Clock_HeartbeatPeriod[LocalCounter] == MAX_ALLOWABLE_PERIOD)
            {
                // if it exceed the max allowable then make it offlinex
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
/*****************************************************************
                    *  GLOBAL FUNCTIONS  * 
 *****************************************************************/
/*
    * Initalize Master if needed.
*/
void Master_init()
{
}

/*
    * called every 500 ms, Fs >= 2*Fm  >> Nequist thresom.
    * update clock from Clock Source.
    * Update clock on display.
    * Publish clock on network.
    * check Heart beat from Clock Slaves.
*/
void Master_MainFunctionUpdateClock()
{
    // To Keep Track LastSecond.
    static uint8_t LastSecond = 0;
    // Call Clock To Update time.
    Clock_UpdateRealTime();
    if (Master_Time.Second != LastSecond) // New Second Elpased.
    {
        LastSecond = Master_Time.Second;
        // Display only updated Clock.
        Display_UpdateClock();
        // Broadcast the clock to slaves.
        Network_SentClockBroadCasting();
        // Checking For The Max Heartbeat-Period every second
        Check_SlaveHeartBeat();
        // Monitor The abcesnt of user
        if (TimeCount_UserAbstance == SCREEN_TIME_OUT)
        {
            // Un-activate any processing service.
            Master_UnactivateService();
            // Display Main Page.
            Display_ChangePage(DEFAULT_PAGE);
        }
        else
        {
            TimeCount_UserAbstance++;
        }
        
    }
}

void Master_HandlerServices_CBK(uint8_t Key)
{
    Master_ServiceDisptacher(Key);
    TimeCount_UserAbstance = 0;
}

void Master_RxNotifcation_CBK(char *Request_Code, uint8_t Clock_Id)
{

#ifdef _DEBUG_SERIAL // for debugging purpose
    Serial.println(Request_Code);
    Serial.println(Clock_Id, DEC);
#endif

    switch (Request_Code[0])
    {
    case 'A': // That mean is Ack from Slave
        Clock_Status[Clock_Id] = ONLINE;
        Clock_HeartbeatPeriod[Clock_Id] = 0;
        break;

    case 'S': // That mean is Start-Exam from Slave
        Clock_Status[Clock_Id] = ONLINE;
        Clock_HeartbeatPeriod[Clock_Id] = 0;
        break;

    default:
        break;
    }
}
