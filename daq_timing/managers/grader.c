/*=============================================================================
 * DAQlib "Terminal - Timing" Implementation (no simulator or hardware support)
 *
 * This implementation reads and writes from/to the standard I/O streams 
 * (stdin, stdout).  This is a modified version, in which inputs and outputs
 * are processed at specific times in program execution.
 * 
 * In setupDAQ(...), the setup number is printed to standard output, regardless 
 * of success or failure.  The following values are then read from standard 
 * input:
 * - process start time in seconds (double)
 * - process time interval in seconds (double) 
 * - termination time in seconds (double)
 * The simulator will then print/read outputs/inputs every "process time" 
 * until the termination time is reached.
 * 
 * At each process time, current outputs are written to 
 * stdout, and new values for device inputs are read from stdin
 * Outputs:
 *    - current process time
 *    - digital outputs
 *    - analog outputs
 *    - 7-segment display outputs (4 lines)
 * Inputs:
 *    - digital inputs
 *    - analog inputs
 *
 * In "CUSTOM" mode setupDAQ(-2), the simulator reads the following setup from 
 * standard input:
 *    - # digital input channels
 *    - # digital output channels
 *    - # analog input channels
 *    - # analog output channels
 *    - # seven-segment display components
 *
 * To disable reading of inputs entirely, set DAQ_IGNORE_INPUTS to TRUE below
 *======================================================================================*/

#include <DAQlib.h>

#define _CRT_SECURE_NO_WARNINGS  /* disable warning for scanf on Windows */
#include <stdio.h>               /* input/output */
#include <stdlib.h>              /* malloc */
#include <stdint.h>              /* standard integer sizes */
#include <math.h>                /* rounding of doubles */

/* symbolic constants */
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* ignore inputs */
#define DAQ_IGNORE_INPUTS TRUE

/* timing */
#if defined(_WIN32) || defined(_WIN64)
  /* windows includes */
  #include <Windows.h>
#else
  /* posix includes */
  #include <time.h>
  #ifdef __MACH__
  /* macos timing */
    #include <mach/clock.h>
    #include <mach/mach.h>
  #endif
#endif
unsigned long micros(void);  /* microseconds that have passed */

/* configuration numbers and ranges */
#define DAQ_SETUP_INVALID   (-9999)
#define DAQ_SETUP_CUSTOM    (-2)
#define DAQ_SETUP_HARDWARE  0
#define DAQ_SETUP_MIN       0
#define DAQ_SETUP_MAX       7

/* DAQ storage */
static struct {
  int setup_number;
  long start_time;
  int digital_inputs_size;
  int* digital_inputs;
  int digital_outputs_size;
  int* digital_outputs;
  int analog_inputs_size;
  double* analog_inputs;
  int analog_outputs_size;
  double* analog_outputs;
  int display_outputs_size;
  int* display_outputs;
  /* process time control */
  unsigned long process_time;
  unsigned long process_interval;
  unsigned long stop_time;
} __daq = {DAQ_SETUP_INVALID, 0, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, 0, 0};

/* read stop time, process interval, process start from standard input */
static int __daq_read_process_control(void)
{
  /* read times as doubles */
  double start = 0;
  double step = 0;
  double stop = 0;
  
  int nread = scanf("%lf %lf %lf", &start, &step, &stop);

  /* convert to useconds */
  __daq.stop_time = lround(stop*1000000);
  __daq.process_interval = lround(step*1000000);
  __daq.process_time = lround(start*1000000);

  /* reinitialize start time */
  __daq.start_time += micros();

  return (nread == 3);
}

/*  set up the DAQ in a specific mode */
int setupDAQ(int setupNum) {
  int i;

  /* print configuration number */
  printf("%d\n", setupNum);

  __daq.setup_number = setupNum;
  if ( ( (setupNum < DAQ_SETUP_MIN) || (setupNum > DAQ_SETUP_MAX) )
  		&& (setupNum != DAQ_SETUP_CUSTOM) ) {
    return FALSE;
  }

  __daq.start_time = micros();
  __daq.digital_inputs_size = 0;
  __daq.digital_outputs_size = 0;
  __daq.analog_inputs_size = 0;
  __daq.analog_outputs_size = 0;
  __daq.display_outputs_size = 0;

  /* configure number of inputs/outputs */
  switch (setupNum) {
    case DAQ_SETUP_CUSTOM: {
      /*  read settings from stdin */
      int nread = 0;
      nread = scanf("%d", &(__daq.digital_inputs_size));
      nread = scanf("%d", &(__daq.digital_outputs_size));
      nread = scanf("%d", &(__daq.analog_inputs_size));
      nread = scanf("%d", &(__daq.analog_outputs_size));
      nread = scanf("%d", &(__daq.display_outputs_size));
      __daq.start_time += micros();  /* restart time to ignore inputs */
      break;
    }
    case 0:  /*  2 toggle-switches, 2 potentiometers, 8 7-segment displays */
    case 5:  /*  2 toggle-switches, 1 temperature sensor, 1 photocell, 8 7-segment displays */
    case 7: {
      /*  2 toggle-switches, 2 potentiometers, 8 7-segment displays */
      __daq.digital_inputs_size = 2;
      __daq.analog_inputs_size = 2;
      __daq.display_outputs_size = 8;
      break;
    }
    case 1: {
      /*  2 toggle-switches, 3 LEDs */
      __daq.digital_inputs_size = 2;
      __daq.digital_outputs_size = 3;
      break;
    }
    case 2: {
      /*  2 push-buttons, 6 LEDs */
      __daq.digital_inputs_size = 2;
      __daq.digital_outputs_size = 6;
      break;
    }
    case 3: {
      /* 5 LEDs, slide pot*/
      __daq.digital_outputs_size = 5;
      __daq.analog_inputs_size = 1;
      break;
    }
    case 4: {
      /*  2 toggle switches, 8 7-segment displays */
      __daq.digital_inputs_size = 2;
      __daq.display_outputs_size = 8;
      break;
    }
    case 6: {
      /*  4 push-buttons, 4 LEDs */
      __daq.digital_inputs_size = 4;
      __daq.digital_outputs_size = 4;
      break;
    }
  }

  /*  build data structures to store data */
  __daq.digital_inputs = (int *) malloc(__daq.digital_inputs_size * sizeof(int));
  for (i = 0; i < __daq.digital_inputs_size; ++i) {
    __daq.digital_inputs[i] = 0;
  }
  __daq.digital_outputs = (int *) malloc(__daq.digital_outputs_size * sizeof(int));
  for (i = 0; i < __daq.digital_outputs_size; ++i) {
    __daq.digital_outputs[i] = 0;
  }
  __daq.analog_inputs = (double *) malloc(__daq.analog_inputs_size * sizeof(double));
  for (i = 0; i < __daq.analog_inputs_size; ++i) {
    __daq.analog_inputs[i] = 0;
  }
  __daq.analog_outputs = (double *) malloc(__daq.analog_outputs_size * sizeof(double));
  for (i = 0; i < __daq.analog_outputs_size; ++i) {
    __daq.analog_outputs[i] = 0;
  }
  __daq.display_outputs = (int *) malloc(__daq.display_outputs_size * sizeof(int));
  for (i = 0; i < __daq.display_outputs_size; ++i) {
    __daq.display_outputs[i] = 0;
  }

  /* read process control */
  return __daq_read_process_control();
}

/*  read DAQ inputs from stdin */
static int __daq_read_inputs(void) {
  int i = 0;

  /* ignore read time */
  long start_time = micros();
  long stop_time = start_time;

  /*  read digital inputs for next iteration */
  for (i = 0; i < __daq.digital_inputs_size; ++i) {
    if (scanf("%d", &__daq.digital_inputs[i]) != 1) {
      /*  if EOF, exit */
      return FALSE;
    }
  }

  /*  read analog inputs for next iteration */
  for (i = 0; i < __daq.analog_inputs_size; ++i) {
    if (scanf("%lf", &__daq.analog_inputs[i]) != 1) {
      /*  if EOF, exit */
      return FALSE;
    }
  }

  /* adjust time */
  stop_time = micros();
  __daq.start_time += (stop_time - start_time);

  return TRUE;
}

/*  print DAQ outputs to stdout */
static void __daq_print_outputs(void) {

  /*  digital output */
  if (__daq.digital_outputs_size > 0) {
    int i;
    for (i = 0; i < __daq.digital_outputs_size; ++i) {
      printf(" %d", __daq.digital_outputs[i]);
    }
  }

  /*  analog output */
  if (__daq.analog_outputs_size > 0) {
    int i;
    for (i = 0; i < __daq.analog_outputs_size; ++i) {
      printf(" %.2f", __daq.analog_outputs[i]);
    }
  }

  /* separate from seven-segment display */
  if (__daq.digital_outputs_size > 0 || __daq.analog_outputs_size > 0) {
    printf("\n");
  }
  
  /*  seven-segment display */
  if (__daq.display_outputs_size > 0) {
    int i, j;
    /*  each row of 7SD */
    for (j = 0; j < 4; ++j) {
      /*  each character in 7SD is 4 columns */
      printf(" ");
      for (i = 0; i < __daq.display_outputs_size; ++i) {
        int val = __daq.display_outputs[__daq.display_outputs_size - 1 - i];
        /*  print appropriate row */
        switch (j) {
          case 0: {
            /*  top characters */
            ((0x80 & val) > 0) ? printf(" _  ") : printf("    ");
            break;
          }
          case 1: {
            /*  center characters */
            ((0x04 & val) > 0) ? printf("|") : printf(" ");
            ((0x02 & val) > 0) ? printf("_") : printf(" ");
            ((0x40 & val) > 0) ? printf("| ") : printf("  ");
            break;
          }
          case 2: {
            /*  bottom characters */
            ((0x08 & val) > 0) ? printf("|") : printf(" ");
            ((0x10 & val) > 0) ? printf("_") : printf(" ");
            ((0x20 & val) > 0) ? printf("|") : printf(" ");
            ((0x01 & val) > 0) ? printf(".") : printf(" ");
            break;
          }
          case 3: {
            printf("___ ");
          }
        }
      }
      printf("\n");
    }
  }
}

/* clear memory and reset configuration */
static void __daq_terminate(void) {
  /*  free memory */
  free(__daq.digital_inputs);
  free(__daq.digital_outputs);
  free(__daq.analog_inputs);
  free(__daq.analog_outputs);
  free(__daq.display_outputs);
  __daq.digital_inputs = NULL;
  __daq.digital_outputs = NULL;
  __daq.analog_inputs = NULL;
  __daq.analog_outputs = NULL;
  __daq.display_outputs = NULL;
  __daq.digital_inputs_size = 0;
  __daq.digital_outputs_size = 0;
  __daq.analog_inputs_size = 0;
  __daq.analog_outputs_size = 0;
  __daq.display_outputs_size = 0;
  __daq.start_time = 0;
  __daq.setup_number = DAQ_SETUP_INVALID;
  __daq.stop_time = 0;
  __daq.process_interval = 0;
  __daq.process_time = 0;
}

/* advances state based on current time */
static int __daq_advance_process_control(void)
{
  unsigned long usec = micros();

  /* process data */
  int success = TRUE;
  while (success && usec >= __daq.process_time) {
    double t = __daq.process_time/1000000.0;
    printf("%.2lf", t);

    /*  print current values */
    __daq_print_outputs();

    /* read next line of inputs   */
#if !defined DAQ_IGNORE_INPUTS || DAQ_IGNORE_INPUTS == FALSE
    success = __daq_read_inputs();
#endif
    

    /* advance process */
    __daq.process_time  += __daq.process_interval;
  }

  return success;
}

/*  check if DAQ has been initialized */
void __daq_check_init(void) {
  if (__daq.setup_number == DAQ_SETUP_INVALID) {
    printf("\nError: DAQ is not setup --> exiting!\n\n");
    exit(-1);
  }
}

/*  check if DAQ should continue, process inputs/outputs */
int continueSuperLoop(void) {

  int success = FALSE;

  /* ensure DAQ has been initialized */
  __daq_check_init();

  success = __daq_advance_process_control();

    /* terminate if next process step is after stop time */
  if (__daq.process_time > __daq.stop_time) {
    success = FALSE;
  }

  /* potentially terminate */
  if (!success) {
    __daq_terminate();
    return FALSE;
  }
  
  return TRUE;
}

/*  read digital value from an input channel */
int digitalRead(int channel) {
  __daq_check_init();
  __daq_advance_process_control();

  if (channel < 0 || channel >= __daq.digital_inputs_size) {
    printf("\nError in calling digitalRead: invalid channel number %d\n", channel);
    return 0;
  }

  return __daq.digital_inputs[channel];
}

/*  write digital value to an output channel */
void digitalWrite(int channel, int val) {
  __daq_check_init();
  __daq_advance_process_control();

  if (channel < 0 || channel >= __daq.digital_outputs_size) {
    printf("\nError in calling digitalWrite: invalid channel number %d\n", channel);
    return;
  }
  
  __daq.digital_outputs[channel] = val;
}

/*  read analog value from an input channel */
double analogRead(int channel) {
  __daq_check_init();
  __daq_advance_process_control();

  if (channel < 0 || channel >= __daq.analog_inputs_size) {
    printf("\nError in calling analogRead: invalid channel number %d\n", channel);
    return 0;
  }

  return __daq.analog_inputs[channel];
}

/*  write analog value to an output channel */
void analogWrite(int channel, double val) {
  __daq_check_init();
  __daq_advance_process_control();

  if (channel < 0 || channel >= __daq.digital_inputs_size) {
    printf("\nError in calling analogWrite: invalid channel number %d\n", channel);
  }

  __daq.analog_outputs[channel] = val;
}

/*  write a value to a seven-segment display, position 0 starts on the right */
void displayWrite(int data, int position) {
  __daq_check_init();
  __daq_advance_process_control();

  if (position < 0 || position >= __daq.display_outputs_size) {
    printf("\nError in calling displayWrite: invalid position %d\n", position);
  }

  __daq.display_outputs[position] = data;
}

/***********************************************
 * TIMING
 ***********************************************/

/* replace DAQ timing */

#include "timing.h"

unsigned long millis(void) {
  return __millis();
}

/* number of microseconds that have passed */
unsigned long micros(void) {
  return __micros();
}

void delay(unsigned long ms) {
  __delay(ms);
}

void delayMicroseconds(unsigned int us) {
  __delayMicroseconds(us);
}

/******************************************************************************
 * TIMING.C
 *****************************************************************************/

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