/*
 * Program: temperature.c - reads from a temperature sensor and 
 *          displays the corresponding values
 */
#include <DAQlib.h>
#include <math.h>
#include <stdio.h>

/* simulator configuration */
#define LIGHT_TEMPERATURE_SIMULATOR 5
#define TEMPERATURE_SENSOR  0
#define PRECISION 1


/* function prototypes */
double readTemperature(void);
void   writeNumber(int number);
void   writeDouble(double d, int precision);
void   temperatureControlLoop(void);

/* main function */
int main(void)
{
	/* initialize the DAQ */
	if (setupDAQ(LIGHT_TEMPERATURE_SIMULATOR)) {
		temperatureControlLoop();
	} else {
		printf("Error: cannot initialize DAQ\n");
	}

	return 0;
}

/* reads and displays either temperature or illumination */
void temperatureControlLoop(void)
{
	/* super loop */
	while (continueSuperLoop()) {
		double celsius = readTemperature();
		writeDouble(celsius, PRECISION);
	}

}

/* symbolic constants for temperature conversion */
#define TMP_SCALE 100
#define TMP_VOFF  0.5

double convertToCelsius(double voltage)
{
	double celsius = (voltage - TMP_VOFF) * TMP_SCALE;
	return celsius;
}

double readTemperature(void) {
	return convertToCelsius(analogRead(TEMPERATURE_SENSOR));
}

/* number of displays on the DAQ */
#define NUM_DISPLAYS 8

/* a character to turn all 7SD segments off */
#define TURNOFF 0

/* a character to display the negative sign */
#define NEGATIVE 2

/*
 * displays "d" on the eight 7-segment displays to a given precision
 */
void writeDouble(double d, int precision)
{

	/* constant digits table */
	const int DIGITS_TABLE[10] = { 252, 96, 218, 242, 102,
								  182, 190, 224, 254, 246 };

	d = round(d * pow(10, precision));
	int number = (int)d;
	if (number < 0) {
		number = -number;
	}

	int digit = 0;

	/* start at the right-most 7-segment display */
	int pos = 0;

	/*
	 * extract one digit at a time until no digits remain (i.e. number == 0)
	 * or we have exhausted our LED displays (i.e. pos >= NUM_DISPLAYS ).
	 */
	do {
		digit = number % 10;
		number = number / 10;

		/* write the digit to the 7 segment-display */
		displayWrite(DIGITS_TABLE[digit] + (pos == precision), pos);

		/* determine the position for the next digit */
		pos++;
	} while (pos < (NUM_DISPLAYS - (d < 0)) && (number != 0 || pos <= precision));

	if (d < 0) {
		displayWrite(NEGATIVE, pos++);
	}

	/* turn off any displays not used above */
	while (pos < NUM_DISPLAYS) {
		displayWrite(TURNOFF, pos);
		pos++;
	}
}