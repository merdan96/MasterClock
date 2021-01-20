#include "Network.h"
#include <TimeLib.h>
#include "Frame_Parser.h"

#define MAX_PACKET_SIZE 10

static char Network_PacketBuffer[MAX_PACKET_SIZE];

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

void Network_SentUniCasting(char *data, uint8_t Slave_ID)
{
#ifdef _Ethernet_
#endif
#ifdef _RS_585_
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
        // Serial.print("Received packet of size ");
        // Serial.println(Network_PacketBuffer);
#ifdef _DEBUG_SERIAL // for debugging purpose
#endif
        Frame_Parsing(Network_PacketBuffer);

#if (CLOCK_ID == 0) // Master           \
                    // Call Notifcation \
                    Master_RxNotifcation_CBK(packetBuffer, (remote[3] - IP_OFFEST));
#else
        
#endif
    }
}
