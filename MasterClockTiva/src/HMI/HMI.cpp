#include "HMI.h"

extern uint8_t Display_CurrentItemIndex;
extern uint8_t Display_MaxPageItem;

void HMI_ScrollButton(uint8_t key){
    int8_t sign = (key == '+') ? 1 : -1;

    if(key == '-' && (Display_CurrentItemIndex > 1))
    {
        Display_CurrentItemIndex--;
    }
    else if(key == '+' && (Display_CurrentItemIndex < Display_MaxPageItem))
    {
        Display_CurrentItemIndex++;

    }
    else
    {

    }
}


// TO DO 