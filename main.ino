//  Copyright (c) 2018 Antoine Tran Tan
//

#include <Arduino.h>
#include "include/TM1637.h"
#include "include/timer.h"

#define CLK 2 //pins definitions for TM1637 and can be changed to other ports
#define DIO 3

//const pour le fun
const int c = 261;
const int d = 294;
const int e = 329;
const int f = 349;
const int g = 391;
const int gS = 415;
const int a = 440;
const int aS = 455;
const int b = 466;
const int cH = 523;
const int cSH = 554;
const int dH = 587;
const int dSH = 622;
const int eH = 659;
const int fH = 698;
const int fSH = 740;
const int gH = 784;
const int gSH = 830;
const int aH = 880;

const int buzzerPin = 8;
int counter = 0;
const int ledPin1 = 12;
const int ledPin2 = 13;

static int update = 1;
static int halfsecond = 2;
static int update2 = 1;

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
            if(update == 5){
                my_state = fsm_state::s8;
            }

            break;

        case fsm_state::s8:

            if (digitalRead(7) == LOW)
                {
                my_state = fsm_state::s9;
                }

            break;

        case fsm_state::s9:

            if (digitalRead(7) == HIGH)
            {
                my_state = fsm_state::s10;
            }

            break;

        case fsm_state::s10:

            if (digitalRead(4) == LOW)
            {
                my_state = fsm_state::s11;
            }

            break;

        case fsm_state::s11:

            if (digitalRead(4) == HIGH)
            {
                update = 1;
                update2 = 1;
                halfsecond = 2;
                my_state = fsm_state::s1;
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

    pinMode(buzzerPin, OUTPUT);
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);

    // Make the function automate() being called
    // every 1000 microseconds
    set_timer4_interrupt(1000, automate);
}


void loop()
{    
    static int display_point = 0;

    static int second = 0;
    static int minute = 0;

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

        break;

        case fsm_state::s8:

        tone(8, 500, 50);

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


        case fsm_state::s10:

            tm1637.display(TimeDisp);
            tm1637.point(POINT_ON);
        
            //Play first section
            firstSection();
            
            //Play second section
            secondSection();
            
            //Variant 1
            beep(f, 250);  
            beep(gS, 500);  
            beep(f, 350);  
            beep(a, 125);
            beep(cH, 500);
            beep(a, 375);  
            beep(cH, 125);
            beep(eH, 650);
            
            delay(500);
            
            //Repeat second section
            secondSection();
            
            //Variant 2
            beep(f, 250);  
            beep(gS, 500);  
            beep(f, 375);  
            beep(cH, 125);
            beep(a, 500);  
            beep(f, 375);  
            beep(cH, 125);
            beep(a, 650);  
            
            delay(650);

            update = 1;
            update2 = 1;
            halfsecond = 2;

        break;
    }
}

void beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(buzzerPin, note, duration);
 
  //Play different LED depending on value of 'counter'
  if(counter % 2 == 0)
  {
    digitalWrite(ledPin1, HIGH);
    delay(duration);
    digitalWrite(ledPin1, LOW);
  }
  else
  {
    digitalWrite(ledPin2, HIGH);
    delay(duration);
    digitalWrite(ledPin2, LOW);
  }
 
  //Stop tone on buzzerPin
  noTone(buzzerPin);
 
  delay(50);
 
  //Increment counter
  counter++;
}

void firstSection()
{
  beep(a, 500);
  beep(a, 500);    
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);  
  beep(a, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);
 
  beep(eH, 500);
  beep(eH, 500);
  beep(eH, 500);  
  beep(fH, 350);
  beep(cH, 150);
  beep(gS, 500);
  beep(f, 350);
  beep(cH, 150);
  beep(a, 650);
 
  delay(500);
}
 
void secondSection()
{
  beep(aH, 500);
  beep(a, 300);
  beep(a, 150);
  beep(aH, 500);
  beep(gSH, 325);
  beep(gH, 175);
  beep(fSH, 125);
  beep(fH, 125);    
  beep(fSH, 250);
 
  delay(325);
 
  beep(aS, 250);
  beep(dSH, 500);
  beep(dH, 325);  
  beep(cSH, 175);  
  beep(cH, 125);  
  beep(b, 125);  
  beep(cH, 250);  
 
  delay(350);
}
