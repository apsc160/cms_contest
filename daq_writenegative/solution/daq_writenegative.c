/* headers */
#include <DAQlib.h>
#include <stdio.h>

/* TODO: define symbolic constants */
#define DISPLAY_SIMULATOR  4
#define DISPLAY0     0
#define NUM_DISPLAYS 8

#define TRUE  1
#define FALSE 0

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
  const static int DIGITS_TABLE[] = {
    0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110,
    0b10110110, 0b10111110, 0b11100000, 0b11111110, 0b11110110
  };
  const static int MINUS = 0b00000010;
  int idx = 0;

  int negative = FALSE;
  if (number < 0) {
    negative = TRUE;
    number = -number;
  }

  /* loop until no digits left or ran out of displays */
  do {
    /* extract next digit */
    int digit = number % 10;
    number = number / 10;

    /* write to display */
    displayWrite(DIGITS_TABLE[digit], DISPLAY0 +  idx++);
  } while (number > 0 && idx < NUM_DISPLAYS - negative);

  /* sign */
  if (negative) {
    displayWrite(MINUS, idx++);
  }

  /* clear remaining displays */
  for(; idx < NUM_DISPLAYS; ++idx) {
    displayWrite(0, DISPLAY0 + idx);
  }

}
