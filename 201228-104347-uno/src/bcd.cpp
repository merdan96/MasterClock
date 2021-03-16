#include "bcd.h"

static uint8_t _digitPins[MAX_NUM_DIGITS * 4];
static uint8_t _numDigits;

void bcd_init(uint8_t* digitPins, uint8_t numDigits){
    // _digitPins = digitPins;
    _numDigits = numDigits;
    for(uint8_t i = 0;i < (_numDigits * 4);i++){
        _digitPins[i] = digitPins[i];
        pinMode(_digitPins[i], OUTPUT);
        digitalWrite(_digitPins[i], LOW);
    }
}

uint8_t bcd_setNumber(uint16_t number, uint8_t index){
    
    for(int i = 0;i < (_numDigits * 4);i++){
        digitalWrite(_digitPins[i], LOW);
    }
    uint8_t i = index * 4;
    if(i > ((_numDigits - 1) * 4)){ /* error index out of range */
        return -1;
    }
    do{
        uint8_t number_temp = number % 10;
        
        for(uint8_t end = (i + 4);i < end;i++){
            digitalWrite(_digitPins[i], number_temp%2);
            number_temp /= 2;
        }
        number /= 10;
    }
    while(number != 0);
    return 0;
}