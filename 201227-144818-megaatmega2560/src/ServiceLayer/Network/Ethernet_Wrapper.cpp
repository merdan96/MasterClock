#include "Ethernet_Wrapper.h"
/*
// Static Paramters
static char packetBuffer[UDP_TX_PACKET_MAX_SIZE];
EthernetUDP Udp;
EthernetUDP Udp_Ntp;

IPAddress Dns_IP(8, 8, 8, 8);
IPAddress Gateway_IP(192, 168, 1, 254);
IPAddress Subnet_IP(255, 255, 255, 0);

// NTP Servers:
const char timeServer[] = "eg.pool.ntp.org"; // Syncing NTP server

const int timeZone = 2; // For Egypt

/*-------- NTP code ----------

const int NTP_PACKET_SIZE = 48;         // NTP time is in the first 48 bytes of message
byte NTP_packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

// send an NTP request to the time server at the given address
void sendNTPpacket(const char *address)
{
    // set all bytes in the buffer to 0
    memset(NTP_packetBuffer, 0, NTP_PACKET_SIZE);
    // Initialize values needed to form NTP request
    // (see URL above for details on the packets)
    NTP_packetBuffer[0] = 0b11100011; // LI, Version, Mode
    NTP_packetBuffer[1] = 0;          // Stratum, or type of clock
    NTP_packetBuffer[2] = 6;          // Polling Interval
    NTP_packetBuffer[3] = 0xEC;       // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    NTP_packetBuffer[12] = 49;
    NTP_packetBuffer[13] = 0x4E;
    NTP_packetBuffer[14] = 49;
    NTP_packetBuffer[15] = 52;
    // all NTP fields have been given values, now
    // you can send a packet requesting a timestamp:
    Udp_Ntp.beginPacket(address, 123); // NTP requests are to port 123
    Udp_Ntp.write(NTP_packetBuffer, NTP_PACKET_SIZE);
    Udp_Ntp.endPacket();
}

time_t getNtpTime()
{
    while (Udp_Ntp.parsePacket() > 0); // discard any previously received packets
    Serial.println("Transmit NTP Request");
    sendNTPpacket(timeServer);
    uint32_t beginWait = millis();
    while (millis() - beginWait < 1500)
    {
        int size = Udp_Ntp.parsePacket();
        if (size >= NTP_PACKET_SIZE)
        {
            Serial.println("Receive NTP Response");
            Udp_Ntp.read(NTP_packetBuffer, NTP_PACKET_SIZE); // read packet into the buffer
            unsigned long secsSince1900;
            // convert four bytes starting at location 40 to a long integer
            secsSince1900 = (unsigned long)NTP_packetBuffer[40] << 24;
            secsSince1900 |= (unsigned long)NTP_packetBuffer[41] << 16;
            secsSince1900 |= (unsigned long)NTP_packetBuffer[42] << 8;
            secsSince1900 |= (unsigned long)NTP_packetBuffer[43];
            return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
        }
    }
    Serial.println("No NTP Response :-(");
    return 0; // return 0 if unable to get the time
}

void Network_Setup()
{
    Ethernet.init(10);
    Network_IP[3] = CLOCK_ID + IP_OFFEST;
    Ethernet.begin(TABLE[CLOCK_ID], Network_IP, Dns_IP, Gateway_IP, Subnet_IP);
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
    Udp_Ntp.begin(1234);
}

void printDigits(int digits)
{
    // utility for digital clock display: prints preceding colon and leading 0
    Serial.print(":");
    if (digits < 10)
        Serial.print('0');
    Serial.print(digits);
}

void Ntp_UpdateTime(tmElements_t *Tm)
{
    // digital clock display of the time)
    setSyncProvider(getNtpTime);
    Serial.print(hour());
    Tm->Hour = hour();
    printDigits(minute());
    Tm->Minute = minute();
    printDigits(second());
    Tm->Second = second();
    Serial.print(" ");
    Serial.print(day());
    Tm->Day = day();
    Serial.print(" ");
    Serial.print(month());
    Tm->Month = month();
    Serial.print(" ");
    Serial.print(year());
    Tm->Year = year();
    Serial.println();
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
    Network_IP[3] = Slave_ID + IP_OFFEST;

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
#if (CLOCK_ID == 0) // Master
        // Call Notifcation
        Master_RxNotifcation_CBK(packetBuffer, (remote[3] - IP_OFFEST));
#else
        Slave_ClockUpdate_CBK();
#endif
    }
}
        */
