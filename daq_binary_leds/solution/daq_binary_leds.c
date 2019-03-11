/* headers */
#include <DAQlib.h>
#include <stdio.h>

/* TODO: define symbolic constants */
#define SIMULATOR_2  2
#define LED0         0
#define NUM_LEDS     6

/* function prototypes */
void binaryLEDsLoop(void);

/* main function */
int main(void) 
{

  /* TODO: initialize the DAQ and call control loop */
  if (setupDAQ(SIMULATOR_2)) {
    binaryLEDsLoop();
  }

  return 0;
}

/* control loop */
void binaryLEDsLoop(void) 
{
  int value = 0;
  int i = 0;

  /* TODO: implement binary LEDs loop functionality */
  while (continueSuperLoop()) {

    /* prompt user */
    printf("Enter an integer in the range [0 - 63]: ");
    scanf("%d", &value);

    /* error condition */
    if (value < 0 || value > 63) {
      printf("Invalid integer\n");
      value = 0;
    }

    /* display binary representation */
    for (i = NUM_LEDS; i --> 0; ) {
      digitalWrite(LED0 + i, value & 1);
      value = value / 2;
    }

  }

}
