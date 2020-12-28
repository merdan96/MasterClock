#ifndef MASTER_CBK_h
#define MASTER_CBK_h
#include "Common.h"

void Master_HandlerServices_CBK(uint8_t Key);
void Master_RxNotifcation_CBK(char *Request_Code, uint8_t Clock_Id);
void Master_ScrollButton(uint8_t key);

#endif
