/* headers */
#define _CRT_SECURE_NO_WARNINGS
#include <DAQlib.h>
#include <stdio.h>

/* symbolic constants */
#define SIMULATOR 4

#define DISPLAY_MIN  2
#define DISPLAY_HOUR 4

#define ONE_SECOND 1000
#define ONE_MINUTE 60*ONE_SECOND

/* control function */
void clock(int hours, int minutes);

/* main function */
int main(void)
{

	int hours = 0;
	int minutes = 0;
	int success = scanf("%d:%d", &hours, &minutes);

	if (setupDAQ(SIMULATOR)) {
		clock(hours, minutes);
	}
	return 0;
}

/* writes the integer number to the displays */
void writeTime(int h, int m)
{

  /* TODO: implement writeNumber functionality */
  const static int DIGITS_TABLE[] = {
    0b11111100, 0b01100000, 0b11011010, 0b11110010, 0b01100110,
    0b10110110, 0b10111110, 0b11100000, 0b11111110, 0b11110110
  };

  /* loop until no digits left or ran out of displays */
  displayWrite(DIGITS_TABLE[m % 10], DISPLAY_MIN);
  displayWrite(DIGITS_TABLE[m / 10], DISPLAY_MIN + 1);
  displayWrite(DIGITS_TABLE[h % 10], DISPLAY_HOUR);
  if (h >= 10) {
  	displayWrite(DIGITS_TABLE[h / 10], DISPLAY_HOUR+1);
  } else {
	displayWrite(0, DISPLAY_HOUR+1);
  }

}


/* control function implementation */
void clock(int hours, int minutes)
{
	long last = millis() - ONE_MINUTE;
	minutes--;

	while (continueSuperLoop()) {

		/* wait until next minute */
		while (millis() - last < ONE_MINUTE ){}
		last += ONE_MINUTE;
		
		/* increase time */
		minutes += 1;
		if (minutes > 59) {
			minutes = 0;
			hours += 1;
			if (hours > 12) {
				hours = 1;
			}
		}

		/* write next time */
		writeTime(hours, minutes);

		/* power nap */
		delay(59*ONE_SECOND);

	}
}