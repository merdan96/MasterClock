
#ifndef COMMON_h
#define COMMON_h
// Ready-made For inculding a standrad Data types
#include <inttypes.h>
// For debugging purpose Serial monitor
#include <HardwareSerial.h>
// Ready-made Time Paramters 
#include <TimeLib.h>
// Custom file for common configurations 
#include "Common_Confg.h"



//Serial Obj for debugging Purpose. 
extern HardwareSerial Serial;

//Main entity Of Master Time  
extern tmElements_t Master_Time;




#endif
