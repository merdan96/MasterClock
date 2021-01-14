#include "Rs_485.h"
#include <SoftwareSerial.h>
#include "Common.h"
// Obj Create for Software Serial
SoftwareSerial RS_485(RX_PIN, TX_PIN); // RX, TXc

/*****************************************************************
 *                   *  FRAMES  *                                *
 *****************************************************************/
typedef struct
{
    char Frame_Id;
    char Hour[2];
    char Clock_Sign;
    char Minuts[2];
} SyncCLockFrame_t;

typedef struct
{
    char Frame_Id;
    char Slave_ID[4];
    char CountStyle;
    char Mins[4];
} ExamCommandFrame_t;

typedef struct
{
    char Frame_Id;
    char Slave_ID[4];
    char FeedBack;
} FeedBackFrame_t;

static void Frame_Parsing(const char *Data)
{
    char Frame_id = Data[0];
    switch (Frame_id)
    {
    case '#': // For Sync Watch. Master >> Slave
    {
        uint8_t Hour = atoi(((SyncCLockFrame_t *)Data)->Hour);
        uint8_t Min = atoi(((SyncCLockFrame_t *)Data)->Minuts);
        Serial.println(Hour, DEC);
        Serial.println(Min, DEC);
        break;
    }
    case '@':
    {
        uint8_t Slave_id = atoi(((ExamCommandFrame_t *)Data)->Slave_ID);
        uint8_t Mins = atoi(((ExamCommandFrame_t *)Data)->Mins);
        uint8_t CountStyle = ((ExamCommandFrame_t *)Data)->CountStyle;
        Serial.println(Slave_id, DEC);
        Serial.println(Mins, DEC);
        Serial.write(CountStyle);
        Serial.println();
        break;
    }
    case '&': // Feedbacks       Slave  >> Master
    {
        uint8_t Slave_id = atoi(((FeedBackFrame_t *)Data)->Slave_ID);
        char FeedBack    = ((FeedBackFrame_t *)Data)->FeedBack;
        Serial.println(Slave_id, DEC);
        Serial.write(FeedBack);
        Serial.println();
        break;
    }
    default:
        break;
    }
}

void Rs485_Init()
{
    // Debug
    Serial.begin(9600);
    while (!Serial);
    //
    pinMode(CONTROL_PIN, OUTPUT);
    RS_485.begin(BAUD_RATE_TTL);
}

void Rs485_Tx(char *Str)
{
    if (digitalRead(CONTROL_PIN) != ENABLE_TX)
    {
        digitalWrite(CONTROL_PIN, ENABLE_TX);
    }
    RS_485.print(Str);
}

void Rs485_RxMainFunction()
{
    if (digitalRead(CONTROL_PIN) != ENABLE_RX)
    {
        digitalWrite(CONTROL_PIN, ENABLE_RX);
    }

    if (RS_485.available() > 0)
    {
        String Temp = RS_485.readString();
        Serial.println(Temp);
        Frame_Parsing(Temp.c_str());
    }
}
