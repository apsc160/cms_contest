/* headers */
#include <DAQlib.h>
#include <stdio.h>

/* constants */
#define TRUE  1
#define FALSE 0

/* DAQ Configuration */
#define DAQ_SIMULATOR 6

/* TODO: define I/O channels for configuration */

/* function prototypes */
void indicatorLoop(void);

/* main function */
int main(void) 
{

  if ( FALSE /* TODO: setup DAQ configuration 6 and check if successful */ ) {
    /* TODO: call the control loop function */
  } else {
    /* TODO: print error statement */
  }

  return 0;
}

/* control loop / work function */
void indicatorLoop(void) 
{
  while (FALSE /* TODO: check if DAQ available and running */) {

    /* TODO: read all four push-buttons and turn on/off corresponding LEDs */

  }

}