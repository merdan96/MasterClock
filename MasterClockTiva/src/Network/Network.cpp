#include <TimeLib.h>
#include "Frame_Parser.h"
#include "Network.h"
#include "AppLayer/Master_CBK.h"
#include "Frame_Parser.h"

#define MAX_PACKET_SIZE 10

static uint8_t Slave_id;
static char FeedBack;
static char Network_PacketBuffer[MAX_PACKET_SIZE];

void Frame_Parsing(const char *Data)
{
    char Frame_id = Data[0];
    switch (Frame_id)
    {
    case '#': // For Sync Watch. Master >> Slave
    {
        uint8_t Hour = atoi(((SyncCLockFrame_t *)Data)->Hour);
        uint8_t Min = atoi(((SyncCLockFrame_t *)Data)->Minuts);
        Serial.println(Hour, DEC);
        Serial.println(Min, DEC);
#if (CLOCK_ID != 0)
        char Data[8];
        char SlaveState = 'A';
        delay((CLOCK_ID * 50));
        sprintf(Data, "&000%d%c", CLOCK_ID, SlaveState);
        Rs485_Tx(Data);
#endif
        break;
    }
    case '@': //  Master >> Slave
    {
        Slave_id = atoi(((ExamCommandFrame_t *)Data)->Slave_ID);
        uint8_t Mins = atoi(((ExamCommandFrame_t *)Data)->Mins);
        uint8_t CountStyle = ((ExamCommandFrame_t *)Data)->CountStyle;
        Serial.println(Slave_id, DEC);
        Serial.println(Mins, DEC);
        Serial.write(CountStyle);
        Serial.println();
        break;
    }
    case '&': // Feedbacks       Slave  >> Master
    {
        uint8_t offest = 0;
        while (Data[offest] == '&')
        {
            Slave_id = atoi(((FeedBackFrame_t *)(Data + offest))->Slave_ID);
            FeedBack = ((FeedBackFrame_t *)(Data + offest))->FeedBack;
            Serial.println(Slave_id, DEC);
            Serial.write(FeedBack);
            Serial.println();
            Master_RxNotifcation_CBK(FeedBack, Slave_id);
            offest += 6;
        }
        break;
    }
    default:
        break;
    }
}

void Network_Setup()
{
#ifdef _Ethernet_

#endif
#ifdef _RS_585_
    Rs485_Init();
#endif
}

#if (CLOCK_ID == 0) // Master
void Network_SentClockBroadCasting()
{
    char data_TX[6];
    data_TX[0] = '#';
    data_TX[1] = '0' + Master_Time.Hour / 10;
    data_TX[2] = '0' + Master_Time.Hour % 10;
    data_TX[3] = ':';
    data_TX[4] = '0' + Master_Time.Minute / 10;
    data_TX[5] = '0' + Master_Time.Minute % 10;
    data_TX[6] = 0;

#ifdef _Ethernet_
#endif
#ifdef _RS_585_
    Rs485_Tx(data_TX);
#endif
}
#endif

void Network_SentUniCasting(char *data)
{
#ifdef _Ethernet_
#endif
#ifdef _RS_585_
    Rs485_Tx(data);
#endif
}

void Network_RecieveMainFunction()
{
    RetVal_t RetVal;
    /*
        * Rx Packet from either Ethernet, Rs_485.
        * Parse packet. 
        * Notify application for received packet.
    */
#ifdef _Ethernet_

#endif
#ifdef _RS_585_
    RetVal = Rs485_Rx(Network_PacketBuffer);

#endif
    if (RetVal == E_OK)
    {
#ifdef _DEBUG_SERIAL // for debugging purpose
        Serial.print("Received packet of size ");
        Serial.println(Network_PacketBuffer);
#endif
        Frame_Parsing(Network_PacketBuffer);

#if (CLOCK_ID == 0)
#else
        Slave_ClockUpdate_CBK();
#endif
    }
}
