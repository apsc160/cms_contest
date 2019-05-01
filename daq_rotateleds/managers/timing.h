/* 
 * Replacement timing functions for use in online competition
 */
#ifndef TIMING_H
#define TIMING_H

#include "Windows.h"
#include "unistd.h"
#include "time.h"
#include <stdint.h>

/* Arduino/DAQlib implementations */
unsigned long __millis(void);
uint64_t __micros(void);
void __delay(unsigned long ms);
void __delayMicroseconds(uint64_t us);

#endif