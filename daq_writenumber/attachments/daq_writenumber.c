/* headers */
#include <DAQlib.h>
#include <stdio.h>

/* TODO: define symbolic constants */
#define DISPLAY_SIMULATOR  4
#define DISPLAY0     0
#define NUM_DISPLAYS 8

/* function prototypes */
void writeNumber(int number);  /* function to write */
void writeNumberLoop(void);    /* control loop */

/* main function */
int main(void) 
{
  if (setupDAQ(DISPLAY_SIMULATOR)) {
    writeNumberLoop();
  } else {
    printf("ERROR: failed to initialize the DAQ\n");
  }
  return 0;
}

/* control loop */
void writeNumberLoop(void) 
{
  int number = 0;
  
  /* loop while device is on and a number is scanned */
  while (continueSuperLoop() && (scanf("%d", &number) == 1) ) {
    writeNumber(number);
  }

}

/* writes the integer number to the displays */
void writeNumber(int number)
{

  /* TODO: implement writeNumber functionality */

}
