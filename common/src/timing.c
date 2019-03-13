#include "timing.h"
#include <stdint.h>

/* advance by 0.1 ms every call to time function */
#define AUTO_TIME_STEP 100

/* time storage */
static struct {
	volatile unsigned long usec;
} __time_info = { 0 };

/* replacement micros from Arduino/DAQlib */
unsigned long __micros(void)
{
	/* auto-advance */
	__time_info.usec += AUTO_TIME_STEP;
	return __time_info.usec;
}

/* replacement millis from Arduino/DAQlib */
unsigned long __millis(void)
{
	return __micros()/1000;
}

/* replacement delay from Arduino/DAQlib */
void __delayMicroseconds(unsigned long us) 
{
	__time_info.usec += us;
}

/* replacement delay from Arduino/DAQlib */
void __delay(unsigned long ms)
{
	__delayMicroseconds(ms * 1000);
}

/* replacement time from time.h */
int __time(int *seconds)
{
	unsigned long us = __micros();
	int s = (int)(us/1000000);
	if (seconds) {
		*seconds = s;
	}
	return s;
}

/* replacement usleep from unistd.h */
int __usleep(unsigned long microseconds) 
{
	__delayMicroseconds(microseconds);
}

/* replacement sleep from unistd.h */
unsigned int __sleep(unsigned int seconds)
{
	__delayMicroseconds(seconds*1000000);
}

/* replacement from time.h */
int __nanosleep(const struct timespec *req, struct timespec *rem)
{
	unsigned long usec = req->tv_nsec/1000 + req->tv_sec * 1000000;
	__delayMicroseconds(usec);

	if (rem) {
		rem->tv_sec = 0;
		rem->tv_nsec = 0;
	}

	return 0;
}

/* replacement gettime */
int __clock_gettime(clockid_t clk_id, struct timespec *tp)
{
	unsigned long usec = __micros();
	unsigned long sec = usec / 1000000;
	usec = usec % 1000000;
	tp->tv_nsec = usec*1000;
	tp->tv_sec = sec;

	return 0;
}

/* replacement Sleep from Windows.h */
void __Sleep(DWORD ms)
{
	__delay(ms);
}

/* replacement system time from Windows.h */
void __GetSystemTimeAsFileTime(LPFILETIME lpSystemTimeAsFileTime)
{
	if (lpSystemTimeAsFileTime) {
		uint64_t usec = (uint64_t)__micros();
		uint64_t tsec = usec * 10;  /* 100 ns intervals */

		lpSystemTimeAsFileTime->dwHighDateTime = (unsigned long)(tsec >> 32);
		lpSystemTimeAsFileTime->dwLowDateTime = (unsigned long)(tsec & 0xFFFFFFFF);
	}
}