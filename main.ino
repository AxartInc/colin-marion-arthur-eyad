//  Copyright (c) 2018 Antoine Tran Tan
//

#include <Arduino.h>
#include "include/TM1637.h"
#include "include/timer.h"

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
    s1,
    s2,
    s3,
    s33,
    s34
};


// Declaration of a variable of type fsm_state
fsm_state my_state = fsm_state::s1;

void automate()
{
    static int ms = 0;

    // Update the state only every 100 function calls
    if (ms == 99)
    {
        ms = 0;

        // Manage the state transitions from the state value
        switch (my_state)
        {
        case fsm_state::s1:

            if (digitalRead(4) == LOW)
            {
                my_state = fsm_state::s2;
            }

            break;

        case fsm_state::s2:

            if (digitalRead(4) == HIGH)
            {
                my_state = fsm_state::s3;
            }

            break;

/*         case fsm_state::s3:

            if (digitalRead(5) == HIGH)
            {
                my_state = fsm_state::s33;
            }
            if (digitalRead(6) == HIGH)
            {
                my_state = fsm_state::s34;
            }
            break;

        case fsm_state::s33:

            if (digitalRead(5) == LOW)
            {
                my_state = fsm_state::s3;
            }

            break;

        case fsm_state::s34:

            if (digitalRead(6) == LOW)
            {
                my_state = fsm_state::s3;
            }

            break;*/
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
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);

    // Make the function automate() being called
    // every 1000 microseconds
    set_timer4_interrupt(1000, automate);
}

void loop()
{
    static int display_point = 0;

    delay(500);

    TimeDisp[3] = 0;
    TimeDisp[2] = 0;
    TimeDisp[1] = 0;
    TimeDisp[0] = 0;


    // Manage the outputs from the state value
    switch (my_state)
    {
    case fsm_state::s1:
        if (display_point == 0)
        {
            tm1637.display(TimeDisp);
            tm1637.point(POINT_ON);
            display_point = 1;
        }
        else
        {
            tm1637.point(POINT_OFF);
            display_point = 0;
        } 

        digitalWrite(13, LOW);

        break;

    case fsm_state::s3:

         if (display_point == 0)
        {
            tm1637.display(TimeDisp);
            tm1637.point(POINT_ON);
            display_point = 1;
        }
        else
        {
            tm1637.clearDisplay();
            tm1637.point(POINT_OFF);
            display_point = 0;
        } 

        digitalWrite(13, HIGH);

        break;
    }
}
