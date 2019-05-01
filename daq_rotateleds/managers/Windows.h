#ifndef WINDOWS_H_REPLACEMENT
#define WINDOWS_H_REPLACEMENT

/* macro hack to replace function calls */
#define Sleep(ms) __Sleep(ms)
#define GetSystemTimeAsFileTime(pTime) __GetSystemTimeAsFileTime(pTime)

#define DWORD unsigned long

typedef struct _FILETIME {
  DWORD dwLowDateTime;
  DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;

void __Sleep(DWORD ms);

void __GetSystemTimeAsFileTime(LPFILETIME lpSystemTimeAsFileTime);

#endif