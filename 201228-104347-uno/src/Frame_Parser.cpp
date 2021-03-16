#include "Frame_Parser.h"
#include "Rs_485.h"
//ToDO: include slave_Cbk
#include "Slave.h"

extern char SlaveState;
void Frame_Parsing(const char *Data)
{
    char Frame_id = Data[0];
    switch (Frame_id)
    {
#if (CLOCK_ID != 0)
    case '#': // For Sync Watch. Master >> Slave
    {
        Slave_RxUpdateClock_CBK(Data);
#if defined(_DEBUG_SERIAL_RS485)
        uint8_t Hour = atoi(((SyncCLockFrame_t *)Data)->Hour);
        uint8_t mints = atoi(((SyncCLockFrame_t *)Data)->Minuts);
        // Serial.println(Hour, DEC);
        // Serial.println(Min, DEC);
#endif
        char data_ack[8];
        delay(50);
        sprintf(data_ack, "&%04d%c", CLOCK_ID, SlaveState);
        Rs485_Tx(data_ack);
        delay(30);
#endif
        break;
    }
    case '@':
    {
        uint8_t Slave_id = atoi(((ExamCommandFrame_t *)Data)->Slave_ID);
        uint16_t _Mins = atoi(((ExamCommandFrame_t *)Data)->mins_arr);
        uint8_t CountStyle = ((ExamCommandFrame_t *)Data)->CountStyle;
        if (Slave_id == CLOCK_ID)
        {
            Slave_RxNewCommand_CBK(_Mins, CountStyle);
            // sprintf(Data, "&%04d%c", CLOCK_ID, SlaveState);
        }
        // Serial.println(Slave_id, DEC);
        // Serial.println(Mins, DEC);
        // Serial.write(CountStyle);
        // Serial.println();
        break;
    }
#if (CLOCK_ID == 0)
    case '&': // Feedbacks       Slave  >> Master
    {
        uint8_t offest = 0;
        while (Data[offest] == '&')
        {
            uint8_t Slave_id = atoi(((FeedBackFrame_t *)(Data + offest))->Slave_ID);
            char FeedBack = ((FeedBackFrame_t *)(Data + offest))->FeedBack;
            // Serial.println(Slave_id, DEC);
            // Serial.write(FeedBack);
            // Serial.println();
            offest += 6;
        }
        break;
    }
#endif
    default:
        break;
    }
}
