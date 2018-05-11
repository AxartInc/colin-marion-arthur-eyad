#include <Arduino.h>
#include "include/timer.h"

uint32_t state = 0;

void automate()
{
    static int toto = 0;

    if(toto == 999)
    {
        toto = 0;
        state = state ? LOW : HIGH;
    }
    else
        toto++;
}

void setup()
{
    pinMode(13,OUTPUT);
    set_timer4_interrupt(1000,automate);
}

void loop()
{
    digitalWrite(13,state);
}
