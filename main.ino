//  Copyright (c) 2018 Antoine Tran Tan
//

#include <Arduino.h>
#include "include/TM1637.h"

#define CLK 2 //pins definitions for TM1637 and can be changed to other ports
#define DIO 3

// Declaration of a int8_t array with 4 elements
int8_t TimeDisp[] = {0, 0, 0, 0};

// Declaration of a TM1637 variable
TM1637 tm1637(CLK, DIO);

/// The class fsm_state is a type whose value is restricted to a
/// subset of values
enum class fsm_state
{
    s0,
    s1
};

// Declaration of a variable of type fsm_state
fsm_state my_state = fsm_state::s0;

void automate()
{
    static int ms = 0;

    // Update the state only every 1000 function calls
    if (ms == 999)
    {
        ms = 0;

        // Manage the state transitions from the state value
        switch (my_state)
        {
        case fsm_state::s0:

            my_state = fsm_state::s1;

            break;

        case fsm_state::s1:

            my_state = fsm_state::s0;

            break;
        }
    }
    else
    {
        ms++;
    }
}

void setup()
{
    tm1637.set();
    tm1637.init();
}

void loop()
{
    static int display_point = 0;

    delay(500);

    TimeDisp[3] = 8;
    TimeDisp[2] = 1;
    TimeDisp[1] = 0;
    TimeDisp[0] = 2;

    if (display_point == 0)
    {
        tm1637.point(POINT_ON);
        display_point = 1;
    }
    else
    {
        tm1637.point(POINT_OFF);
        display_point = 0;
    }
    tm1637.display(TimeDisp);

    // Manage the outputs from the state value
    switch (my_state)
    {
    case fsm_state::s0:

        digitalWrite(13, LOW);

        break;

    case fsm_state::s1:

        digitalWrite(13, HIGH);

        break;
    }
}
