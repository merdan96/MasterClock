#include "Network.h"
#include "Master.h"

// Static Paramters 
static char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
EthernetUDP Udp;
char data_TX[] = "00:00:00";

void Network_Setup()
{
    Ethernet.init(10);
    Network_IP[3] = CLOCK_ID + 2;
    Ethernet.begin(TABLE[CLOCK_ID], Network_IP);
#ifdef _DEBUG_SERIAL // for debugging purpose
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware)
    {
        Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
        while (true)
        {
            delay(1); // do nothing, no point running without Ethernet hardware
        }
    }
    if (Ethernet.linkStatus() == LinkOFF)
    {
        Serial.println("Ethernet cable is not connected.");
    }
#endif
    // start UDP
    Udp.begin(Network.MasterRxPort);
}

#if (CLOCK_ID == 0) // Master
void Network_SentClockBroadCasting()
{
    data_TX[0] = '0' + Master_Time.Hour / 10;
    data_TX[1] = '0' + Master_Time.Hour % 10;
    data_TX[2] = ':';
    data_TX[3] = '0' + Master_Time.Minute / 10;
    data_TX[4] = '0' + Master_Time.Minute % 10;
    data_TX[5] = ':';
    data_TX[6] = '0' + Master_Time.Second / 10;
    data_TX[7] = '0' + Master_Time.Second % 10;
    Network_IP[3] = Network.BroadCasting;
    Udp.beginPacket(Network_IP, Network.MasterTxPort);
    Udp.write(data_TX);
    Udp.endPacket();
    
}
#endif

void Network_SentUniCasting(char *data, uint8_t Slave_ID)
{
    Network_IP[3] = Slave_ID + 2;

    if (Slave_ID != 0) // Master to Slave
    {
        Udp.beginPacket(Network_IP, Network.MasterTxPort);
    }
    else // Slave to Master
    {
        Udp.beginPacket(Network_IP, Network.MasterRxPort);
    }
    Udp.write(data);
    Udp.endPacket();
}

void Network_RecieveMainFunction()
{
    // Read New data comming to Udp
    int packetSize = Udp.parsePacket();
    if (packetSize)
    {
        IPAddress remote = Udp.remoteIP();
#ifdef _DEBUG_SERIAL // for debugging purpose
        Serial.print("Received packet of size ");
        Serial.println(packetSize);
        Serial.print("From ");
        for (int i = 0; i < 4; i++)
        {
            Serial.print(remote[i], DEC);
            if (i < 3)
            {
                Serial.print(".");
            }
        }
        Serial.print(", port ");
        Serial.println(Udp.remotePort());
#endif
        // read the packet into packetBufffer
        Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
        //Notify User Packet Is received
        /*
            * Call back
            * flag/lock
            * Call Application Call back function 
        */
#if (CLOCK_ID == 0) // Master
        // Call Notifcation 
        Master_RxNotifcation_CBK(packetBuffer,(remote[3]-2));
#else
        Slave_ClockUpdate_CBK();
#endif
    }
}
