//  Copyright (c) 2018 Antoine Tran Tan
//

#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>

/// The function set_timer4_interrupt defines an interface for launching
/// a user function each timestep. The period is defined (in microseconds)
/// with the first parameter and the user function is passed by reference
/// with the second parameter
void set_timer4_interrupt(uint16_t microseconds, void (& callback)(void));

#endif
