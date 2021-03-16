#include "Display.h"

#if defined(SEVSEGMENT_MUX)
SevSeg sevseg; //Instantiate a seven segment controller object
#elif defined(SEVSEGMENT_BCD)
#endif

void Display_init()
{
#if defined(SEVSEGMENT_MUX)

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
#elif defined(SEVSEGMENT_BCD)
    uint8_t digitPins[] = { 53, 47, 49, 51,     /* digit 0 digtial pins */
                            45, 39, 41, 43,     /* digit 1 digtial pins */
                            37, 31, 33, 35,     /* digit 2 digtial pins */
                            29, 23, 25, 27};    /* digit 3 digtial pins */
    uint8_t numDigits = 4;
    bcd_init(&digitPins[0], numDigits);
#endif
}

// Display Online Time
void Display_UpdateClock(uint32_t Clock)
{
#if defined(SEVSEGMENT_MUX)
    sevseg.setNumber(Clock, 0);
#elif defined(SEVSEGMENT_BCD)
    bcd_setNumber(Clock, 0);
    
#endif
}

void Display_mainFunction()
{
#if defined(SEVSEGMENT_MUX)
    sevseg.refreshDisplay(); // Must run repeatedly
#elif defined(SEVSEGMENT_BCD)

#endif
}

void Display_ExamMins(uint16_t Mins)
{
    if (Mins == 0)
    {
#if defined(SEVSEGMENT_MUX)
        sevseg.setNumber(0, 0);
        sevseg.setNumber(0, 1);
        sevseg.setNumber(0, 2);
        sevseg.setNumber(0, 3);
#elif defined(SEVSEGMENT_BCD)
        bcd_setNumber(0, 0);
#endif
    }
    else
    {
        uint16_t Hour1stDigit = (Mins / 60) / 10;
        uint16_t Hour2ndDigit = (Mins / 60) % 10;
        uint16_t Min1stDigit = (Mins % 60) / 10;
        uint16_t Min2ndDigit = (Mins % 60) % 10;

        uint16_t num = Hour1stDigit*1000+ Hour2ndDigit * 100+ Min1stDigit*10 + Min2ndDigit;
#if defined(SEVSEGMENT_MUX)        
        sevseg.setNumber(num, 0);
#elif defined(SEVSEGMENT_BCD)
        bcd_setNumber(num, 0);
#endif
    }
}
