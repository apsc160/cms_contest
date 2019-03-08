/* headers */
#include <DAQlib.h>
#include <stdio.h>

/* constants */
#define TRUE  1
#define FALSE 0
#define ON    1
#define OFF   0

/* DAQ Configuration */
#define DAQ_SIMULATOR 6

/* TODO: define I/O channels for configuration */
#define BUTTON0     0
#define LED0        0
#define NUM_BUTTONS 4

/* function prototypes */
void toggleLoop(void);

/* main function */
int main(void) 
{
  /* TODO: initialize the DAQ and call control loop */
  if ( setupDAQ(DAQ_SIMULATOR)  ) {
    toggleLoop();
  } else {
    printf("ERROR: cannot initialize the DAQ\n");
  }

  return 0;
}

/* control loop */
void toggleLoop(void) 
{
  /* TODO: initialize variables for storing button/LED state */
  int i = 0;
  int leds[NUM_BUTTONS] = { OFF };
  int buttons[NUM_BUTTONS] = { OFF };
  int button = OFF;

  /* TODO: create super-loop */
  while (continueSuperLoop()) {

    /* TODO: implement toggle functionality */
    for (i = 0; i < NUM_BUTTONS; ++i) {
      /* read button state */
      button = digitalRead(BUTTON0+i);
      /* look for change from off to on */
      if (button == ON && buttons[i] == OFF) {
        /* flip LED */
        leds[i] = !leds[i];
        digitalWrite(LED0+i, leds[i]);
      }
      /* remember current button state */
      buttons[i] = button;
    }

  }
}
