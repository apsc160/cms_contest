/* headers */
#include <DAQlib.h>
#include <math.h>

/* symbolic constants */
#define SIMULATOR 3

#define SLIDER   0
#define LED0     0
#define NUM_LEDS 5

#define ON  1
#define OFF 0

/* control function */
void slider(void);

/* main function */
int main(void)
{
	if (setupDAQ(SIMULATOR)) {
		slider();
	}
	return 0;
}

/* control function implementation */
void slider(void)
{
	int i = 0;
	while (continueSuperLoop()) {
		double v = analogRead(SLIDER);
		int rv = (int)round(v);
		if (rv < 0) {
			rv = 0;
		} else if (rv > NUM_LEDS) {
			rv = NUM_LEDS;
		}

		for (i = 0; i<rv; ++i) {
			digitalWrite(LED0 + i, ON);
		}
		for (i = rv; i < NUM_LEDS; ++i) {
			digitalWrite(LED0+i, OFF);
		}
	}
}