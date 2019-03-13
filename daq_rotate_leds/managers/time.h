#ifndef TIME_H_REPLACEMENT
#define TIME_H_REPLACEMENT

/* macro hack to replace function calls */
#define time(psec) __time(psec)
#define nanosleep(req, rem) __nanosleep(req, rem)
#define clock_gettime(clk_id, tp) __clock_gettime(clk_id, tp)

/* macro hack to replace types */
#define timespec __timespec
#define clockid_t __clockid_t

typedef int __clockid_t;

/* clock ids */
#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME              0
#define CLOCK_MONOTONIC             1
#define CLOCK_PROCESS_CPUTIME_ID    2
#define CLOCK_THREAD_CPUTIME_ID     3
#endif

/* POSIX timespec */
struct __timespec {
	long tv_sec;        /* seconds */
	long tv_nsec;       /* nanoseconds */
};

int __time(int *seconds);

int __nanosleep(const struct __timespec *req, struct __timespec *rem);

int __clock_gettime(__clockid_t clk_id, struct __timespec *tp);

#endif