#ifndef BCD_h
#define BCD_h
#include <Arduino.h>

#define MAX_NUM_DIGITS 4

void bcd_init(uint8_t* digitPins, uint8_t numDigits);
uint8_t bcd_setNumber(uint16_t number, uint8_t index);

#endif