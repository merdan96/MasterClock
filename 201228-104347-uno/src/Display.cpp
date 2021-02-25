#include "Display.h"


SevSeg sevseg; //Instantiate a seven segment controller object

void Display_init()
{
    byte numDigits = 4;
    byte digitPins[] = {6, 7, 8, 9};
    byte segmentPins[] = {10, 11, 12, 13, A2, A1, A0, A4};
    bool resistorsOnSegments = false; // 'false' means resistors are on digit pins
    byte hardwareConfig = COMMON_ANODE; // See README.md for options
    bool updateWithDelays = false; // Default 'false' is Recommended
    bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
    bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected
  
    sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
    updateWithDelays, leadingZeros, disableDecPoint);
    sevseg.setBrightness(10);
}

// Display Online Time
void Display_UpdateClock(uint32_t Clock)
{
    sevseg.setNumber(Clock, 0);
}

void Display_mainFunction()
{
    sevseg.refreshDisplay(); // Must run repeatedly
}

void Display_ExamMins(uint16_t Mins)
{
    if (Mins == 0)
    {
        sevseg.setNumber(0, 0);
        sevseg.setNumber(0, 1);
        sevseg.setNumber(0, 2);
        sevseg.setNumber(0, 3);
    }
    else
    {
        uint16_t Hour1stDigit = (Mins / 60) / 10;
        uint16_t Hour2ndDigit = (Mins / 60) % 10;
        uint16_t Min1stDigit = (Mins % 60) / 10;
        uint16_t Min2ndDigit = (Mins % 60) % 10;

        uint16_t num = Hour1stDigit*1000+ Hour2ndDigit * 100+ Min1stDigit*10 + Min2ndDigit;
        sevseg.setNumber(num, 0);
    }
}
