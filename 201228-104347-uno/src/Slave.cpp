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
void Slave_RxUpdateClock_CBK(char *Clock_Str)
{
  if (Exam_mode != 1)
  {
    char A_Clock[5];
    A_Clock[0] = Clock_Str[0];
    A_Clock[1] = Clock_Str[1];
    A_Clock[2] = Clock_Str[3];
    A_Clock[3] = Clock_Str[4];
    A_Clock[4] = 0;
    uint32_t IntegarClock = atoi(A_Clock);
    Display_UpdateClock(IntegarClock);
    // Sent back ack
    Network_SentUniCasting("Ack", 0);
  }
  else
  {
    Network_SentUniCasting(Str_, 0);
  }
}

void Slave_RxNewCommand(char *Command)
{
  Serial.println(Command);
  char mins[4] = {0};
  for (uint8_t i = 1; i < 5; i++)
  {
    if ((Command[i] == 'U') ||
        (Command[i] == 'D'))
    {
      Dirction = Command[i];
      break;
    }
    mins[i - 1] = Command[i];
  }
  Mins = atoi(mins);
  Serial.println(Mins, DEC);
  Serial.println(Dirction);
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
  strcpy(Str_, "EXAM");
  Network_SentUniCasting(Str_, 0);
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
        Serial.println(Mins, DEC);
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
        Serial.println(Mins_UpDirction, DEC);
        Display_ExamMins(Mins_UpDirction);
      }
      //  }
    }
  }
}
