
#ifndef CAPTURE_h
#define CAPTURE_h

#include <Keypad.h>
#include <IRremote.h>
#include "Common.h"

//Configurations 
#define _KEYPAD_ENABLE
#define _IR_ENABLE


// Get Key and Call back "Master/Nofitication" 
void Capture_MainFunction();

// Init 
void Capture_init();


#endif
