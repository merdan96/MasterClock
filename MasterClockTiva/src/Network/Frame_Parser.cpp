#include "Frame_Parser.h"

void Frame_Parsing(const char *Data)
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
#if (CLOCK_ID != 0)
        char Data[8];
        char SlaveState = 'A';
        delay((CLOCK_ID * 50));
        sprintf(Data, "&000%d%c", CLOCK_ID, SlaveState);
        Rs485_Tx(Data);
#endif
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
        uint8_t offest = 0;
        while (Data[offest] == '&')
        {
            uint8_t Slave_id = atoi(((FeedBackFrame_t *)(Data + offest))->Slave_ID);
            char FeedBack = ((FeedBackFrame_t *)(Data + offest))->FeedBack;
            Serial.println(Slave_id, DEC);
            Serial.write(FeedBack);
            Serial.println();
            offest += 6;
        }
        break;
    }
    default:
        break;
    }
}
