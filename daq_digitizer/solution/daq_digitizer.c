/*
 * Program: digitizer.c - 2D digitizer program
 */

/* headers */
#include <DAQlib.h>
#include <math.h>
#include <stdio.h>

/* constants */
#define ON   1
#define OFF  0

/* I/O channels */
#define ARM_BASE  0
#define ARM_ELBOW 1
#define SWITCH0   0
#define SWITCH1   1

/* display settings */
#define NUM_DISPLAYS 8
#define LEFT_OFFSET  4
#define LEFT_LENGTH  4
#define RIGHT_OFFSET 0
#define RIGHT_LENGTH 4

/* sleep time between recordings */
#define DELAY_TIME   500

/* function prototypes */
void writeNumber(int number, int length, int offset);
void digitizer(void);

/* main function */
int main(void)
{
	int setupNum = 0;
	int nread = 0;

	/* prompt user */
	printf("Enter the DAQ setup number (0 for hardware, 7 for simulator): ");
	nread = scanf("%d", &setupNum);

	/* initialize system */
	if (setupDAQ(setupNum)) {
		digitizer();
	} else {
		printf("ERROR: cannot initialize DAQ.\n");
	}

	return 0;
}

void digitizer(void)
{

	/* super loop */
	long start = millis();
	long next = start;

    while (continueSuperLoop()) {

		/* sleep */
        delay(next - millis());
		next += DELAY_TIME;

		int switch0 = digitalRead(SWITCH0);

		if (switch0 == OFF) {
			/* turn off displays */
			for (int i=0; i<NUM_DISPLAYS; ++i) {
				displayWrite(OFF, i);
			}
		} else {
			int switch1 = digitalRead(SWITCH1);

			/* read voltages and convert to millivolts */
			double basemv = 1000 * analogRead(ARM_BASE);
			double elbowmv = 1000 * analogRead(ARM_ELBOW);

			/* write to 7-segment display display */
			int leftnum = 0;
			int rightnum = 0;

			/* voltages or x,y */
			if (switch1 == OFF) {
				/* mv */
				leftnum = (int)round(basemv);
				rightnum = (int)round(elbowmv);

			} else {
				/* convert to x,y */
				const double pi = 3.14159265358979323846;
				const double mt1 = -0.0499;
				const double ot1 = 104.86;
				const double mt3 = -0.0514;
				const double ot3 = 300.98;
				const double AB = 85;
				const double BC = 85;

				double theta1 = (mt1*basemv + ot1)*pi/180.0;
				double theta3 = (mt3*elbowmv + ot3)*pi/180.0;
				double theta2 = theta1 + theta3 - pi;

				double x = AB*cos(theta1) + BC*cos(theta2);
				double y = AB*sin(theta1) + BC*sin(theta2);

				leftnum = (int)round(x);
				rightnum = (int)round(y);
			}

			if (leftnum < 0) {
				leftnum = 0;
			}
			if (rightnum < 0) {
				rightnum = 0;
			}

			/* write numbers to display */
			writeNumber(leftnum, LEFT_LENGTH, LEFT_OFFSET);
			writeNumber(rightnum, RIGHT_LENGTH, RIGHT_OFFSET);
			
		}
    }
}

/*
 * Writes a number to a set of 7-segment displays
 * Parameters:
 *     number - non-negative integer to display
 *     length - number of displays to write to
 *     offset - starting display index to write least-significant digit
 */
void writeNumber(int number, int length, int offset)
{
    /* constant digits table */
    const int DIGITS_TABLE[10] = {252, 96, 218, 242, 102,
                                  182, 190, 224, 254, 246};
    /* space to clear displays */
    const int SPACE_CHAR = 0;

    /* starting position */
    int pos = offset;
    int digit = 0;

    /* if no displays to write to, exit immediately */
    if (length == 0) {
        return;
    }

    /* extract and write one digit at a time */
    do {
        digit = number % 10;
        number = number / 10;

        displayWrite(DIGITS_TABLE[digit], pos);

        /* move to next digit */
        pos++;

        /* loop while still displays left and number is not zero */
    } while ( pos < offset + length && number != 0 );

    /* clear any remaining displays */
    while (pos < offset + length) {
        displayWrite(SPACE_CHAR, pos);
        pos++;
    }
}