
#ifndef NETWORK_h
#define NETWORK_h

#include "Common.h"
#include "Master_CBK.h"
#include <Ethernet.h>
#include <EthernetUdp.h>



typedef struct 
{
    unsigned int MasterRxPort;
    unsigned int MasterTxPort;
    unsigned int BroadCasting;
} Network_Cfg_t;

extern Network_Cfg_t  Network;
extern IPAddress Network_IP;
extern byte TABLE[NUM_CLOCKS + 1][6];

void Network_Setup();
void Network_SentClockBroadCasting();
void Network_SentUniCasting(char *data, uint8_t Slave_ID);
void Network_RecieveMainFunction();

#endif
