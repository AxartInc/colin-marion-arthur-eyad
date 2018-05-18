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
    s34,
    s4,
    s5,
    s6,
    s7,
    s8,
    s9,
    s10,
    s11
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

         case fsm_state::s3:

            if (digitalRead(5) == LOW)
            {
                my_state = fsm_state::s33;
            }
            else if (digitalRead(6) == LOW)
            {
                my_state = fsm_state::s34;
            }
            else if (digitalRead(4) == LOW)
            {
                my_state = fsm_state::s4;
            }
            break;

        case fsm_state::s33:

            if (digitalRead(5) == HIGH)
            {
                my_state = fsm_state::s3;
            }

            break;

        case fsm_state::s34:

            if (digitalRead(6) == HIGH)
            {
                my_state = fsm_state::s3;
            }

            break;

        case fsm_state::s4:

            if (digitalRead(4) == HIGH)
            {
                my_state = fsm_state::s5;
            }

            break;
        
        case fsm_state::s5:

            if (digitalRead(7) == LOW)
            {
                my_state = fsm_state::s6;
            }

            break;

        case fsm_state::s6:

            if (digitalRead(7) == HIGH)
            {
                my_state = fsm_state::s7;
            }

            break;

        case fsm_state::s7:

             if (digitalRead(7) == LOW)
            {
                my_state = fsm_state::s8;
            }

            break;

        case fsm_state::s9:

             if (digitalRead(7) == HIGH)
            {
                my_state = fsm_state::s10;
            }

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
    pinMode(4, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);
    pinMode(7, INPUT_PULLUP);

    // Make the function automate() being called
    // every 1000 microseconds
    set_timer4_interrupt(1000, automate);
}

void loop()
{
    static int display_point = 0;

    static int second = 0;
    static int minute = 0;

    static int halfsecond = 2;
    static int update = 1;
    static int update2 = 1;


    delay(500);

    TimeDisp[3] = second % 10;
    TimeDisp[2] = second / 10;
    TimeDisp[1] = minute % 10;
    TimeDisp[0] = minute / 10;


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

        break;

    case fsm_state::s33:

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

        second++;
        if(second >= 59 )
        {
          minute++; 
          second=0;
        }
        
        break;

    case fsm_state::s34:

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
        
        second--;
        if(second <= 0 )
        {
          minute--;
          minute = 0; 
          second=60;
        }
        
        break; 

    case fsm_state::s5:
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

        break;
      
    case fsm_state::s7:
        if(update == 1){ 
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
        }

        if(update == 1){ 
            halfsecond--;
            if(halfsecond <= 0)
            {
                second--;
                if(second <= 0 )
                {
                    if(second == 0 && minute == 0){
                        update = 0;
                        update2 = 0;
                        second = 1;
                    }

                    minute--;
                    minute = 0; 
                    second = 60;         
                }  
                halfsecond = 2;       
            }
        }

        if(update == 0 && update2 == 0){
           update = 5;
           second = 0;
        }

        if(update == 5){
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
        }

        break;

        case fsm_state::s10:

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

        digitalWrite(13, HIGH);

        break;
    }
}
