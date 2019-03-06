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

  printf("Enter the DAQ setup number: ");
  scanf("%d", &setupNum);

  if ( setupDAQ(setupNum) /* TODO: setup DAQ and check if successful */ ) {
    /* TODO: call the control loop function */
    controlLoop();
  } else {
    /* TODO: print error statement */
    printf("ERROR: cannot initialize the DAQ\n");
  }

  return 0;
}

/* control loop / work function */
void controlLoop(void) 
{
  while (continueSuperLoop() /* TODO: check if DAQ available and running */) {

    /* will do something interesting here */
    printf("The DAQ is running\n");

  }
  printf("The DAQ is closing\n");
}
