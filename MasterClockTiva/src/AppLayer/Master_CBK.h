#ifndef MASTER_CBK_h
#define MASTER_CBK_h
#include "Common.h"

/*  
    * this file for declarition the Call-backs Api
    * 
*/

void Master_HandlerServices_CBK(uint8_t Key);
void Master_RxNotifcation_CBK(char Request_Code, uint8_t Clock_Id);
// Scroll Not Done
void Master_ScrollButton_CBK(uint8_t key);
void Master_RxGuiCommand_Cbk(char* cmd);

#endif
