#ifndef CAPTURE_h
#define CAPTURE_h
#include "Common.h"
#include "HMI/HMI.h"
#include "AppLayer/Master_CBK.h"


// Test for Git in vs code  

/*****************************************************************
                    *  CONFIGURATIONS  * 
 *****************************************************************/

// Configure Keypad To be ON/OFF.
#define _KEY_PAD_        E_ON

// Configure IR_Remote To be ON/OFF.
#define _IR_REMOTE_      E_OFF


/*****************************************************************
                    *  Gloabal Functions  * 
 *****************************************************************/

// Get Key and Call back Application.
void Capture_MainFunction();

// Init the Capture 
void Capture_init();

#endif
