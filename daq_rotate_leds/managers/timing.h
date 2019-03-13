/* 
 * Replacement timing functions for use in online competition
 */
#ifndef TIMING_H
#define TIMING_H

#include "Windows.h"
#include "unistd.h"
#include "time.h"

/* Arduino/DAQlib implementations */
unsigned long __millis(void);
unsigned long __micros(void);
void __delay(unsigned long ms);
void __delayMicroseconds(unsigned long us);

#endif