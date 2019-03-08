/* headers */
#include <DAQlib.h>
#include <stdio.h>

/* constants */
#define TRUE  1
#define FALSE 0

/* DAQ Configuration */
#define DAQ_SIMULATOR 6

/* TODO: define I/O channels for configuration */
#define BUTTON0     0
#define LED0        0
#define NUM_BUTTONS 4

/* function prototypes */
void indicatorLoop(void);

/* main function */
int main(void) 
{

  if ( setupDAQ(DAQ_SIMULATOR) /* TODO: setup DAQ configuration 6 and check if successful */ ) {
    /* TODO: call the control loop function */
    indicatorLoop();
  } else {
    /* TODO: print error statement */
    printf("ERROR: cannot initialize the DAQ\n");
  }

  return 0;
}

/* control loop / work function */
void indicatorLoop(void) 
{
  int i = 0;

  while (continueSuperLoop() /* TODO: check if DAQ available and running */) {

    /* TODO: read all four push-buttons and turn on/off corresponding LEDs */
    for (i = 0; i < NUM_BUTTONS; ++i) {
      digitalWrite(LED0+i, digitalRead(BUTTON0+i));
    }

  }

}