/* headers */
#include <DAQlib.h>

/* symbolic constants */
#define SIMULATOR 2

#define GREEN  0
#define YELLOW 1
#define RED    2

#define NS_LIGHTS  0
#define EW_LIGHTS  3

#define NS_BUTTON 0
#define EW_BUTTON 1

#define ON  1
#define OFF 0
#define TRUE  1
#define FALSE 0

#define ONE_SECOND 1000

/* control function */
void traffic(void);

/* main function */
int main(void)
{
	if (setupDAQ(SIMULATOR)) {
		traffic();
	}
	return 0;
}

void setNS(int green, int yellow, int red)
{
	digitalWrite(NS_LIGHTS+GREEN, green);
	digitalWrite(NS_LIGHTS+YELLOW, yellow);
	digitalWrite(NS_LIGHTS+RED, red);
}

void setEW(int green, int yellow, int red)
{
	digitalWrite(EW_LIGHTS+GREEN, green);
	digitalWrite(EW_LIGHTS+YELLOW, yellow);
	digitalWrite(EW_LIGHTS+RED, red);
}

/* control function implementation */
void traffic(void)
{

	/* initialize NS to be green */
	setNS(ON, OFF, OFF);
	setEW(OFF, OFF, ON);

	const int YELLOW_TIME = 2 * ONE_SECOND;
	const int RED_TIME = 1 * ONE_SECOND;
	const int GREEN_TIME = 5 * ONE_SECOND;

	int state = NS_LIGHTS + GREEN;
	long start = millis();
	int waiting = FALSE;
	
	while (continueSuperLoop()) {

		long ctime = millis();

		/* waiting */
		if (state == NS_LIGHTS + GREEN 
			|| (state == EW_LIGHTS + RED)) {
			if (!waiting && digitalRead(EW_BUTTON)) {
				waiting = TRUE;
			}
		}
		else if (state == EW_LIGHTS + GREEN
			|| (state == NS_LIGHTS + RED)) {
			if (!waiting && digitalRead(NS_BUTTON)) {
				waiting = TRUE;
			}
		}

		/* NS Green */
		if (state == NS_LIGHTS + GREEN) {
			
			if (waiting && (ctime - start) >= GREEN_TIME) {
				/* next state */
				state = NS_LIGHTS + YELLOW;
				setNS(OFF, ON, OFF);
				setEW(OFF, OFF, ON);
				start = ctime;
			}
		}
		/* NS Yellow */
		else if (state == NS_LIGHTS + YELLOW) {
			if ((ctime - start) >= YELLOW_TIME) {
				/* next state */
				state = NS_LIGHTS + RED;
				setNS(OFF, OFF, ON);
				setEW(OFF, OFF, ON);
				start += YELLOW_TIME;
			}
		}
		/* NS Red */
		else if (state == NS_LIGHTS + RED) {
			if ((ctime - start) >= RED_TIME) {
				/* next state */
				state = EW_LIGHTS + GREEN;
				setNS(OFF, OFF, ON);
				setEW(ON, OFF, OFF);
				waiting = FALSE;      /* disable wait signal */
				start += RED_TIME;
			}
		}
		/* EW Green */
		else if (state == EW_LIGHTS + GREEN) {
			if (!waiting && digitalRead(NS_BUTTON)) {
				waiting = TRUE;
			}
			if (waiting && (ctime - start) >= GREEN_TIME) {
				/* next state */
				state = EW_LIGHTS + YELLOW;
				setNS(OFF, OFF, ON);
				setEW(OFF, ON, OFF);
				start = ctime;
			}
		}
		/* EW Yellow */
		else if (state == EW_LIGHTS + YELLOW) {
			if ((ctime - start) >= YELLOW_TIME) {
				/* next state */
				state = EW_LIGHTS + RED;
				setNS(OFF, OFF, ON);
				setEW(OFF, OFF, ON);
				start += YELLOW_TIME;
			}
		}
		/* EW Red */
		else if (state == EW_LIGHTS + RED) {
			if ((ctime - start) >= RED_TIME) {
				/* next state */
				state = NS_LIGHTS + GREEN;
				setNS(ON, OFF, OFF);
				setEW(OFF, OFF, ON);
				waiting = FALSE;      /* disable wait signal */
				start += RED_TIME;
			}
		}

	}
}