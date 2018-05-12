#include <Arduino.h>
#include "include/timer.h"

/// The class fsm_state is a type whose value is restricted to a 
/// subset of values
enum class fsm_state 
{
    s0, s1
};

// Declaration of a variable of type fsm_state
fsm_state my_state = fsm_state::s0;

void automate()
{
    static int ms = 0;

    // Update the state only every 1000 function calls
    if(ms == 999)
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
    pinMode(13,OUTPUT);

    // Make the function automate() being called 
    // every 1000 microseconds
    set_timer4_interrupt(1000,automate);
}

void loop()
{
    // Manage the outputs from the state value
    switch (my_state)
    {
        case fsm_state::s0:

            digitalWrite(13,LOW);

            break;

        case fsm_state::s1:

            digitalWrite(13, HIGH);

            break;
    }
}
