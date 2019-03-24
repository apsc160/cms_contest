/* 
 * Testing file for safestrings implementation 
 * 
 * To test your solution, include both this file and your 
 * safestrings.c implementation into a single project.  Visual Studio
 * (or Xcode, or whatever IDE you use) should compile both files
 * into a single program.
 */

/* headers */
#include <stdio.h>

/* function prototypes */
int  strlen_safe(char str[], int size);
void strcat_safe(char dest[], int dsize, char src[], int ssize);
void strcpy_safe(char dest[], int dsize, char src[], int ssize);

int main(void)
{
	/* test our safe string functions */
    int len;
    char dest[100];

    /* length */
    len = strlen_safe("hello, world", 13);
    printf("%d\n", len);
    len = strlen_safe("hello, world", 5);
    printf("%d\n", len);

    /* copy */
    strcpy_safe(dest, 100, "I love apples!!", 16);
    printf("%s\n", dest);
    strcpy_safe(dest, 100, "I love apples!!", 1);
    printf("%s\n", dest);
    strcpy_safe(dest, 7, "I love apples!!", 16);
    printf("%s\n", dest);

    /* concatenate */
    strcpy_safe(dest, 14, "cats", 5);
    printf("%s\n", dest);
    strcat_safe(dest, 14, " say", 5);
    printf("%s\n", dest);
    strcat_safe(dest, 14, " meowzer", 9);
    printf("%s\n", dest);

	return 0;
}