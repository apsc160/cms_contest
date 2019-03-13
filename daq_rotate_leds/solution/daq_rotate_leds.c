/* TODO: include headers */
#include <DAQlib.h>

/* TODO: define symbolic constants */
#define SIMULATOR 2
#define LED0      0
#define NUM_LEDS  6
#define BUTTON0   0
#define BUTTON1   1
#define ON        1
#define OFF       0
#define DELAY_TIME 500

/* control loop */
void rotateLEDsLoop(void);

/* main function */
int main(void)
{
	/* TODO: initialize DAQ and call control loop */
	if (setupDAQ(SIMULATOR)) {
		rotateLEDsLoop();
	}

	return 0;
}

/* control function */
void rotateLEDsLoop(void)
{
	int state = 0;
	int prevstate = 0;
	int i = 0;
	int button0 = OFF;
	int button1 = OFF;

	/* TODO: intialize LED states */
	digitalWrite(LED0, ON);

	/* TODO: implement control loop */
	while (continueSuperLoop()) {

		/* read buttons */
		button0 = digitalRead(BUTTON0);
		button1 = digitalRead(BUTTON1);

		/* determine direction */
		if (button0 && !button1) {
			prevstate = state;
			state = (state + NUM_LEDS - 1) % NUM_LEDS;
		}
		else if (!button0 && button1) {
			prevstate = state;
			state = (state + 1) % NUM_LEDS;
		}

		/* update LEDs */
		if (button0 != button1) {
			digitalWrite(LED0 + prevstate, OFF);
			digitalWrite(LED0 + state, ON);
			delay(DELAY_TIME);
		}
	}

}
