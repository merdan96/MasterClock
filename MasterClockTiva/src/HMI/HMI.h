#ifndef HMI_H
#define HMI_H
#include "Common.h"
#include "ServiceLayer/Display/Display.h"
#include "ServiceLayer/Capture/Capture.h"
#include "HMI/HMI_Cfg.h"
#include "HMI_DataTypes.h"

//Maximum number of array digits "0->9999"
#define MAX_BUFF_SIZE 4

void HMI_MainFunction();
void HMI_UnactivateSession();
void HMI_ReSyncClockSession(uint8_t Key);

#endif