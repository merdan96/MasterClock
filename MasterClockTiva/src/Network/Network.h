
#ifndef NETWORK_h
#define NETWORK_h
#include "Rs_485.h"

/*****************************************************************
                    *  CONFIGURATIONS  * 
 *****************************************************************/
#define _RS_585_

void Network_Setup();
void Network_SentClockBroadCasting();
void Network_SentUniCasting(char *data);
void Network_RecieveMainFunction();

#endif
