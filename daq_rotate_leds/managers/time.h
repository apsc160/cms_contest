#ifndef TIME_H_REPLACEMENT
#define TIME_H_REPLACEMENT

/* macro hack to replace function calls */
#define time(psec) __time(psec)
#define nanosleep(req, rem) __nanosleep(req, rem)
#define clock_gettime(clk_id, tp) __clock_gettime(clk_id, tp)


#if defined(_WIN32) || defined(_WIN64)
/* clock ids */
#define clockid_t int
#define CLOCK_REALTIME              0
#define CLOCK_MONOTONIC             1
#define CLOCK_PROCESS_CPUTIME_ID    2
#define CLOCK_THREAD_CPUTIME_ID     3

/* POSIX timespec */
struct timespec {
	long tv_sec;        /* seconds */
	long tv_nsec;       /* nanoseconds */
};
#else
#include <sys/types.h>
#endif

int __time(int *seconds);

int __nanosleep(const struct timespec *req, struct timespec *rem);

int __clock_gettime(clockid_t clk_id, struct timespec *tp);

#endif