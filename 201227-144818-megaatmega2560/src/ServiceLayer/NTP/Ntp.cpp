#include "Ntp.h"
#include "Network.h"
#include <TimeLib.h>

#define NTP_MIN_REQUEST_INTERVAL 10000
// Static Paramters
EthernetUDP Udp_Ntp;

// NTP Servers:
const char timeServer[] = "eg.pool.ntp.org"; // Syncing NTP server

const int timeZone = 2; // For Egypt

unsigned long Last_NtpRequest = 0;
/*-------- NTP code ----------*/
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
    if ((Last_NtpRequest + NTP_MIN_REQUEST_INTERVAL) >= millis())
    {
        sendNTPpacket(timeServer); // send an NTP packet to a time server
        // wait to see if a reply is available
        delay(1000);
        if (Udp_Ntp.parsePacket())
        {
            // We've received a packet, read the data from it
            Udp_Ntp.read(NTP_packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

            // the timestamp starts at byte 40 of the received packet and is four bytes,
            // or two words, long. First, extract the two words:

            unsigned long highWord = word(NTP_packetBuffer[40], NTP_packetBuffer[41]);
            unsigned long lowWord = word(NTP_packetBuffer[42], NTP_packetBuffer[43]);
            // combine the four bytes (two words) into a long integer
            // this is NTP time (seconds since Jan 1 1900):
            unsigned long secsSince1900 = highWord << 16 | lowWord;
            Serial.print("Seconds since Jan 1 1900 = ");
            Serial.println(secsSince1900);

            // now convert NTP time into everyday time:
            Serial.print("Unix time = ");
            // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
            const unsigned long seventyYears = 2208988800UL;
            // subtract seventy years:
            unsigned long epoch = secsSince1900 - seventyYears + timeZone * SECS_PER_HOUR;
            
            // print Unix time:
            Serial.println(epoch);

            // print the hour, minute and second:
            Serial.print("The UTC time is ");      // UTC is the time at Greenwich Meridian (GMT)
            Serial.print((epoch % 86400L) / 3600); // print the hour (86400 equals secs per day)
            Serial.print(':');
            if (((epoch % 3600) / 60) < 10)
            {
                // In the first 10 minutes of each hour, we'll want a leading '0'
                Serial.print('0');
            }
            Serial.print((epoch % 3600) / 60); // print the minute (3600 equals secs per minute)
            Serial.print(':');
            if ((epoch % 60) < 10)
            {
                // In the first 10 seconds of each minute, we'll want a leading '0'
                Serial.print('0');
            }
            Serial.println(epoch % 60); // print the second
        }
        else
        {
            // Ntp No respone
            Serial.println("Ntp No respone");
        }
        // Capture time to wait ten seconds before asking for the time again
        Last_NtpRequest = millis();
    }
    else
    {
        // Wait 10 sec to ask again
        Serial.println("Wait 10 sec to ask again");
    }
}


