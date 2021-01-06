#ifndef SLAVE_h
#define SLAVE_h

#include "Common.h"
#include "Display.h"

void Slave_RxUpdateClock_CBK(char* Clock_Str);
void Slave_RxNewCommand(char* Command);
void Slave_HandlerService_CBK(uint8_t Key);
void Slave_MainFunction();
#endif
