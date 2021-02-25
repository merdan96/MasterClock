#include "Slave.h"
#include "Display.h"
#include "Network.h"

/*
typedef struct 
{
    
} StrExamComand;
*/

uint16_t Mins, Second_Elpased = 0, Mins_UpDirction = 0;
unsigned long Start_ExamTime, current_Milli;
char Dirction;
bool Exam_mode = 0;
bool Exam_Running = 0;
char Str_[8];
uint32_t last_int = 0;
void Slave_RxUpdateClock_CBK(char *Clock_Str)
{
  if (Exam_mode != 1)
  {
    char A_Clock[6];
    A_Clock[0] = Clock_Str[1];
    A_Clock[1] = Clock_Str[2];
    A_Clock[2] = Clock_Str[4];
    A_Clock[3] = Clock_Str[5];
    A_Clock[4] = 0;
    uint32_t IntegarClock = atoi(A_Clock);
    // TODO Check if integar clock less than 60
    if (last_int != IntegarClock)
    {
      last_int = IntegarClock;
      Display_UpdateClock(IntegarClock);
    }
    // Sent back ack
    // Network_SentUniCasting("Ack", 0);
  }
  else
  {
    Network_SentUniCasting(Str_, 0);
  }
}

void Slave_RxNewCommand(uint16_t mins,char ContStyle)
{
  Dirction = ContStyle;
  Mins = mins;
  Exam_Running = 0;
  if (Dirction == 'U')
  {
    Display_ExamMins(0);
    Mins_UpDirction = 0;
  }
  else
  {
    Display_ExamMins(Mins);
  }
  Exam_mode = 1;
}

void Slave_HandlerService_CBK(uint8_t Key)
{
  if (Key == '#')
  {
    Start_ExamTime = millis();
    Exam_Running = 1;
    strcpy(Str_, "START");
    Network_SentUniCasting(Str_, 0);
  }
  else if (Key == '*')
  {
    Exam_Running = 0;
    strcpy(Str_, "PAUSED");
    Network_SentUniCasting(Str_, 0);
  }
  else
  {
    /* code */
  }
}

void Slave_MainFunction()
{
  if ((Exam_mode == 1) && (Exam_Running == 1) && (current_Milli != millis()))
  {
    current_Milli = millis();
    if (((current_Milli - Start_ExamTime) % 1000) == 0) // One Second Elpased
    {
      Second_Elpased++;
      // if((Second_Elpased%60) == 0) // One Minute Elapsed
      // {
      if (Dirction == 'D')
      {
        Mins--;
        if (Mins == 0)
        {
          Exam_mode = 0;
          Exam_Running = 0;
        }
        // Serial.println(Mins, DEC);
        Display_ExamMins(Mins);
      }
      else
      {
        Mins_UpDirction++;
        if (Mins == Mins_UpDirction)
        {
          Exam_mode = 0;
          Exam_Running = 0;
        }
        // Serial.println(Mins_UpDirction, DEC);
        Display_ExamMins(Mins_UpDirction);
      }
      //  }
    }
  }
}
