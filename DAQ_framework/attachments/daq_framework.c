/* headers */
#include <DAQlib.h>
#include <stdio.h>

/* constants */
#define TRUE  1
#define FALSE 0

/* function prototypes */
void controlLoop(void);

/* main function */
int main(void) 
{
  int setupNum = 0;   /* initial DAQ configuration */

  /* TODO: prompt user for setup number */

  if ( FALSE /* TODO: setup DAQ and check if successful */ ) {
    /* TODO: call the control loop function */
  } else {
    /* TODO: print error statement */
  }

  return 0;
}

/* control loop / work function */
void controlLoop(void) 
{
  while (FALSE /* TODO: check if DAQ available and running */) {

    /* will do something interesting here later in the course */
    printf("The DAQ is running\n");

  }
  printf("The DAQ is closing\n");
}