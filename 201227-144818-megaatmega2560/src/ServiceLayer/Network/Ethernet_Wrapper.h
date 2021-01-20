
#ifndef ETHERNET_WRAPPER_h
#define ETHERNET_WRAPPER_h

#include "Common.h"
#include <Ethernet.h>
#include <EthernetUdp.h>

#define IP_OFFEST       8

typedef struct 
{
    unsigned int MasterRxPort;
    unsigned int MasterTxPort;
    unsigned int BroadCasting;
} EthernetCfg_t;

extern EthernetCfg_t  EthernetCfg;
extern IPAddress EthernetNetwork_IP;
extern byte TABLE[NUM_CLOCKS + 1][6];

void Ethernet_Setup();
void Ethernet_SentClockBroadCasting();
void Ethernet_SentUniCasting(char *data, uint8_t Slave_ID);
void Ethernet_RecieveMainFunction();

#endif
