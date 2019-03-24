/* disable string.h functions */

#define strlen_s __strlen_s
#define strcat_s __strcat_s
#define strcpy_s __strcpy_s

int strcmp(const char* lhs, const char* rhs);