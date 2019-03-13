/* TODO: include headers */
#include <DAQlib.h>
#include <stdio.h>

/* TODO: define symbolic constants */
#define SIMULATOR 1
#define LED0 0
#define NUM_LEDS 3
#define ON   1
#define OFF  0
#define ONE_SECOND 1000

/* control loop */
void timingLoop(void);

/* main function */
int main(void) 
{
	/* TODO: initialize DAQ and call control loop */
	if (setupDAQ(SIMULATOR)) {
		timingLoop();
	}

	return 0;
}

/* control function */
void timingLoop(void)
{

	/* TODO: implement control loop */
	int t = 0;
	int leds[NUM_LEDS] = {OFF, OFF, OFF};
	int intervals[NUM_LEDS] = {1, 2, 3};
	int i = 0;

	int last_time = millis();

	while (continueSuperLoop()) {

		/* delay one second */
		int now = millis();
		while (now - last_time <= ONE_SECOND) {
			now = millis();
		}
		last_time += ONE_SECOND;
		/* delay(ONE_SECOND); */ /* drifts */

		++t;
		

		/* for every LED */
		for (i=0; i<NUM_LEDS; ++i) {
			/* if we hit a toggle interval */
			if ((t % intervals[i]) == 0) {
				/* toggle light */
				leds[i] = !leds[i];
				digitalWrite(LED0 + i, leds[i]);
			}
		}
		
	}
}
