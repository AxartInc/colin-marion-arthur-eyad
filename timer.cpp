//  Copyright (c) 2018 Antoine Tran Tan
//

#include <Arduino.h>
#include "include/timer.h"

void do_nothing(){}

void (*timer4_interrupt)() = &do_nothing;

void set_timer4_interrupt(uint16_t microseconds, void(& callback)(void))
{
    timer4_interrupt = &callback;

    // Disable Timer4 interrupt before setting up
    NVIC_DisableIRQ(TC4_IRQn);
    NVIC_ClearPendingIRQ(TC4_IRQn);
    REG_TC4_INTFLAG |= TC_INTFLAG_MC1 | TC_INTFLAG_MC0 | TC_INTFLAG_OVF;        // Clear the interrupt flags

    // Set up the generic clock (GCLK4) used to clock timers
    REG_GCLK_GENDIV = GCLK_GENDIV_DIV(3) |          // Divide the 48MHz clock source by divisor 3: 48MHz/3=16MHz
                      GCLK_GENDIV_ID(4);            // Select Generic Clock (GCLK) 4
    while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

    REG_GCLK_GENCTRL = GCLK_GENCTRL_IDC |           // Set the duty cycle to 50/50 HIGH/LOW
                        GCLK_GENCTRL_GENEN |        // Enable GCLK4
                        GCLK_GENCTRL_SRC_DFLL48M |  // Set the 48MHz clock source
                        GCLK_GENCTRL_ID(4);         // Select GCLK4
    while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

    // Feed GCLK4 to TC4 and TC5
    REG_GCLK_CLKCTRL = GCLK_CLKCTRL_CLKEN |         // Enable GCLK4 to TC4 and TC5
                        GCLK_CLKCTRL_GEN_GCLK4 |    // Select GCLK4
                        GCLK_CLKCTRL_ID_TC4_TC5;    // Feed the GCLK4 to TC4 and TC5
    while (GCLK->STATUS.bit.SYNCBUSY);              // Wait for synchronization

    REG_TC4_CTRLA |= TC_CTRLA_MODE_COUNT16;          // Set the counter to 16-bit mode
    while (TC4->COUNT16.STATUS.bit.SYNCBUSY);        // Wait for synchronization

    REG_TC4_COUNT16_CC0 = microseconds;                      // Set the TC4 CC0 register to some arbitary value
    while (TC4->COUNT16.STATUS.bit.SYNCBUSY);        // Wait for synchronization

    TC4->COUNT16.CTRLA.reg |= TC_CTRLA_WAVEGEN_MFRQ; // Set TC4 mode as match frequency
    while (TC4->COUNT16.STATUS.bit.SYNCBUSY);        // Wait for synchronization

    REG_TC4_INTENSET = TC_INTENSET_MC0;                       // Enable TC4 interrupts
    REG_TC4_INTENCLR = TC_INTENCLR_MC1 | TC_INTENCLR_OVF;     // Disable TC4 interrupts
    
    REG_TC4_CTRLA |= TC_CTRLA_PRESCALER_DIV16 |     // Set prescaler to 16, 16MHz/16 = 1MHz
                        TC_CTRLA_ENABLE;            // Enable TC4
    while (TC4->COUNT16.STATUS.bit.SYNCBUSY);       // Wait for synchronization

    NVIC_SetPriority(TC4_IRQn, 0); // Set the Nested Vector Interrupt Controller (NVIC) priority for TC4 to 0 (highest)
    NVIC_EnableIRQ(TC4_IRQn);      // Connect TC4 to Nested Vector Interrupt Controller (NVIC)
    while (TC4->COUNT16.STATUS.bit.SYNCBUSY);        // Wait for synchronization
}

void TC4_Handler() // Interrupt Service Routine (ISR) for timer TC4
{
    // Check for match counter 0 (MC0) interrupt
    if (TC4->COUNT16.INTFLAG.bit.MC0 && TC4->COUNT16.INTENSET.bit.MC0)             
    {
        timer4_interrupt();
        REG_TC4_INTFLAG = TC_INTFLAG_MC0;         // Clear the MC0 interrupt flag
    }
}
