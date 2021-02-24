#ifndef MASTER_CBK_h
#define MASTER_CBK_h
#include "Common.h"

/*  
    * this file for declarition the Call-backs Api
    * 
*/

void Master_RxNotifcation_CBK(char Request_Code, uint8_t Clock_Id);
// Scroll Not Done
void Master_RxGuiCommand_Cbk(char* cmd);
void Master_HMICommand_CBK(char* command);

#endif
