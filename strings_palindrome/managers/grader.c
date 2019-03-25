/* headers */
#include <stdio.h>

/* constants */
#define LINE_SIZE  250

/* function prototypes */
static int scanline(char line[]);
int is_palindrome(char str[]);

int main(void)
{
	char line[LINE_SIZE];

	/* read line, check if palindrome */
	while (scanline(line) >= 0) {
		if (is_palindrome(line)) {
			printf("TRUE\n");
		} else {
			printf("FALSE\n");
		}
	}

	return 0;
}

/* scans a line from standard input */
int scanline(char line[])
{
	int len = 0;         /* length of line */
	int c = getchar();   /* next character read */

	/* end of file */
	if (c == EOF) {
		return -1;
	}

	/* loop until end of line or file */
	while (c != '\n' && c != EOF) {
		line[len++] = (char)c;    /* copy character */
		c = getchar();            /* next character */
	}

	line[len] = '\0';    /* terminating NUL */

	return len;
}
