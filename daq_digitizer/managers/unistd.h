#ifndef UNISTD_H_REPLACEMENT
#define UNISTD_H_REPLACEMENT

/* macro hack to replace function calls */
#define usleep(usec) __usleep(usec)
#define sleep(sec) __sleep(sec)

int __usleep(unsigned long microseconds);

unsigned int __sleep(unsigned int seconds);

#endif