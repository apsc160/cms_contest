#include <DAQlib.h>

#define _CRT_SECURE_NO_WARNINGS  /* disable warning for scanf on Windows */
#include <stdio.h>  /* for input/output */
#include <stdlib.h> /* for malloc */
#include <stdint.h> /* for standard integer sizes */

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

/* timing */
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#else
#include <time.h>
  #ifdef __MACH__
    #include <mach/clock.h>
    #include <mach/mach.h>
  #endif
#endif
unsigned long micros(void);  /* microseconds that have passed */

#define DAQ_SETUP_INVALID   (-9999)
#define DAQ_SETUP_CUSTOM    (-1)
#define DAQ_SETUP_HARDWARE  0

/*  global variables for storing I/O data */
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
} __daq = {DAQ_SETUP_INVALID, 0, 0, NULL, 0, NULL, 0, NULL, 0, NULL, 0, NULL};

/*  set up the DAQ in a specific mode */
int setupDAQ(int setupNum) {
  int i;

  __daq.setup_number = setupNum;
  if (setupNum < -1 || setupNum > 8) {
    return FALSE;
  }

  __daq.start_time = micros();
  __daq.digital_inputs_size = 0;
  __daq.digital_outputs_size = 0;
  __daq.analog_inputs_size = 0;
  __daq.analog_outputs_size = 0;
  __daq.display_outputs_size = 0;

  switch (setupNum) {
    case DAQ_SETUP_CUSTOM: {
      /*  read settings from stdin */
      int nread = 0;
      nread = scanf("%d", &(__daq.digital_inputs_size));
      nread = scanf("%d", &(__daq.digital_outputs_size));
      nread = scanf("%d", &(__daq.analog_inputs_size));
      nread = scanf("%d", &(__daq.analog_outputs_size));
      nread = scanf("%d", &(__daq.display_outputs_size));
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

  return TRUE;
}

/*  read DAQ inputs from stdin */
static int __daq_read_inputs(void) {
  int i = 0;

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

  return TRUE;
}

/*  print DAQ outputs to stdout */
static void __daq_print_outputs(void) {

  /* setup number */
  /* printf("%d", __daq.setup_number); */
  
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
}

/*  check if DAQ has been initialized */
void __daq_check_init(void) {
  if (__daq.setup_number == DAQ_SETUP_INVALID) {
    printf("\nError in calling continueSuperLoop: DAQ is not setup --> exiting!\n\n");
    exit(-1);
  }
}

/*  check if DAQ should continue, process inputs/outputs */
int continueSuperLoop(void) {

  int success = FALSE;

  /* ensure DAQ has been initialized */
  __daq_check_init();

  /*  print current values */
  __daq_print_outputs();

  /* read next line of inputs   */
  success = __daq_read_inputs();

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

  if (channel < 0 || channel >= __daq.digital_inputs_size) {
    printf("\nError in calling digitalRead: invalid channel number %d\n", channel);
    return 0;
  }

  return __daq.digital_inputs[channel];
}

/*  write digital value to an output channel */
void digitalWrite(int channel, int val) {
  __daq_check_init();

  if (channel < 0 || channel >= __daq.digital_outputs_size) {
    printf("\nError in calling digitalWrite: invalid channel number %d\n", channel);
    return;
  }
  
  __daq.digital_outputs[channel] = val;
}

/*  read analog value from an input channel */
double analogRead(int channel) {
  __daq_check_init();

  if (channel < 0 || channel >= __daq.analog_inputs_size) {
    printf("\nError in calling analogRead: invalid channel number %d\n", channel);
    return 0;
  }

  return __daq.analog_inputs[channel];
}

/*  write analog value to an output channel */
void analogWrite(int channel, double val) {
  __daq_check_init();

  if (channel < 0 || channel >= __daq.digital_inputs_size) {
    printf("\nError in calling analogWrite: invalid channel number %d\n", channel);
  }

  __daq.analog_outputs[channel] = val;
}

/*  write a value to a seven-segment display, position 0 starts on the right */
void displayWrite(int data, int position) {
  __daq_check_init();

  if (position < 0 || position >= __daq.display_outputs_size) {
    printf("\nError in calling displayWrite: invalid position %d\n", position);
  }

  __daq.display_outputs[position] = data;
}

/***********************************************
 * TIMING
 ***********************************************/

#if defined(_WIN32) || defined(_WIN64)

/* number of microseconds that have passed */
unsigned long micros(void) {
  FILETIME ft;
  uint64_t us;

  /* no time has passed if daq not initialized */
  if (__daq.setup_number == DAQ_SETUP_INVALID) {
    return 0;
  }

  GetSystemTimeAsFileTime(&ft);
  us = (((uint64_t)ft.dwHighDateTime) << 32) | ft.dwLowDateTime;
  us = us/10;  /* 100ns to us */

  return (unsigned long)(us - __daq.start_time);
}

/* Windows implementation */
void delay(unsigned long ms) {
  Sleep(ms);
}

void delayMicroseconds(unsigned int us) {
  unsigned long us1;
  unsigned long diff;
  unsigned int ms;

  /* separate into ms*1000 + us */
  ms = us/1000;
  us = us%1000;

  /* sleep ms first */
  if (ms > 0) {
    delay(ms);
  }

  /* delay remaining microseconds */
  us1 = micros();
  diff = micros()-us1;
  while (diff < us) {
    diff = micros()-us1;
  }
}

#else

/*
 * POSIX implementation of time functions
 */
void delay(unsigned long ms) {
  /* separate seconds and remainder usec */
  unsigned int sec = (int)(ms / 1000);
  ms = ms % 1000;
  unsigned long nano = ms*1000000;
  struct timespec sleeptime;
  sleeptime.tv_sec = sec;
  sleeptime.tv_nsec = nano;
  nanosleep(&sleeptime, NULL);
}

void delayMicroseconds(unsigned int us) {
  /* separate seconds and remainder usec */
  unsigned int sec = (int)(us / 1000000);
  us = us % 1000000;
  unsigned long nano = us*1000;
  struct timespec sleeptime;
  sleeptime.tv_sec = sec;
  sleeptime.tv_nsec = nano;
  nanosleep(&sleeptime, NULL);
}

unsigned long micros(void) {
  struct timespec tv;
  uint64_t us = 0;

  /* no time has passed if daq not initialized */
  if (__daq.setup_number == DAQ_SETUP_INVALID) {
    return 0;
  }

#ifdef __MACH__
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_name_port_t self = mach_host_self();
  host_get_clock_service(self, SYSTEM_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  mach_port_deallocate(mach_task_self(), self);
  tv.tv_sec = mts.tv_sec;
  tv.tv_nsec = mts.tv_nsec;
#else
  clock_gettime(CLOCK_REALTIME, &tv);
#endif
  us = ((uint64_t)(tv.tv_sec))*1000000UL;
  us += tv.tv_nsec/1000UL;
  return (unsigned long)(us - __daq.start_time);
}

#endif /* WIN32 */

unsigned long millis(void) {
  return micros()/1000;
}