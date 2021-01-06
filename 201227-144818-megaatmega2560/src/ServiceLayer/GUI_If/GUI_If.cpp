#include "GUI_If.h"
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Arduino.h>

/*****************************************************************
                    *  GLOBAL VARIABLES  * 
 *****************************************************************/

/*****************************************************************
                    *  STATIC VARIABLES  * 
 *****************************************************************/
/*****************************************************************
                    *  STATIC FUNCTIONS  * 
 *****************************************************************/

/*****************************************************************
                    *  GLOBAL FUNCTIONS  * 
 *****************************************************************/

typedef struct 

    char Sign;
    char Min[4];
    char Dir;
    char ID[4];
} Comadn_t;


typedef struct 
{
    uint8_t SlaveId; 
    uint8_t MsgType;
    char Data[8];
    char Delmiater;
} Rs485_StringFormate_t;


void Master_RxGuiCommand_Cbk(char* cmd)
{
    char Dir = ((Comadn_t*)cmd)->Dir;
    int mins = atoi(((Comadn_t*)cmd)->Min);
    int Id = atoi(((Comadn_t*)cmd)->ID);
}

void GUI_MainFunction()
{
    if (Serial.available() > 0)
    {
        String temp = Serial.readString();
        char Cmd[] = temp.c_str();
        Master_RxGuiCommand_Cbk(Cmd);
    }
}

void Gui_UpdateClock()
{

}

void GUi_UpdateSlaveStuts()
{
    
}
*/


SoftwareSerial mySerial(2, 3); // RX, TX
#define _debug
typedef struct
{
    uint8_t SlaveId;
    uint8_t MsgType;
    char Data[8];
    char Delmiater;
} Rs485_StringFormate_t;

void setup()
{
    Serial.begin(9600);
    while (!Serial);
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);
    // set the data rate for the SoftwareSerial port
    mySerial.begin(4800);
}

void loop()
{ // run over and over
    if (mySerial.available() > 0)
    {
        //#ifdef _debug
        String temp = mySerial.readString();
        Serial.println(temp);
        char* Cmd = temp.c_str();
        uint8_t SlaveId = ((Rs485_StringFormate_t *)Cmd)->SlaveId;
        Serial.println(SlaveId, DEC);
        uint8_t MsgType = ((Rs485_StringFormate_t *)Cmd)->MsgType;
        Serial.println(MsgType, DEC);
        char Data[8];
        strcpy(Data, ((Rs485_StringFormate_t *)Cmd)->Data);
        Serial.println(Data);
        char Delmiater = ((Rs485_StringFormate_t *)Cmd)->Delmiater;
        Serial.write(Delmiater);
        Serial.println();
        //#endif
    }
}
