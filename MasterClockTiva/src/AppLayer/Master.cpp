#include "AppLayer/Master.h"

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
// Static Array for holding The Clock Status.
static uint8_t Clock_HeartbeatPeriod[NUM_CLOCKS];

/*****************************************************************
                    *  STATIC VARIABLES  * 
 *****************************************************************/

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
uint8_t Last_Second = 0;
void Master_MainFunctionUpdateClock()
{
    // Call Clock To Update time.
    Clock_UpdateRealTime();
    if (Master_Time.Second != Last_Second)
    {
        if (Master_Time.Second % 15 == 0)
        {
            Network_SentClockBroadCasting();
        }
        Last_Second = Master_Time.Second;
        // Checking For The Max Heartbeat-Period every second
        Check_SlaveHeartBeat();

    }
   
}

/*****************************************************************
                    *  CALL-BACKs FUNCTIONS  * 
 *****************************************************************/

void Master_RxNotifcation_CBK(char Response_Code, uint8_t Clock_Id)
{
    switch (Response_Code)
    {
    case 'A': // That mean is Ack from Slave
        Clock_Status[Clock_Id] = ONLINE;
        Clock_HeartbeatPeriod[Clock_Id] = 0;
        break;

    case 'E': // That mean Exam Mode Is confirmed from Slave
        Clock_Status[Clock_Id] = EXAM;
        break;
    default:
        break;
    }
}

void Master_RxGuiCommand_Cbk()
{
}

void Master_HMICommand_CBK(char* command)
{
    Network_SentUniCasting(command);
}