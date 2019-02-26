/* 
 * Checkerboard.c submission file
 */

/* required headers */
#include <stdio.h>

/* function prototypes */
void printChars(int size, char c );  /* provided, DO NOT IMPLEMENT */
void printCheckerLine(int checkerWidth, int checkerCount, char c1, char c2);
void printCheckerBoard(int checkerWidth, int checkerCount, char c1, char c2);

/* prints a single line of two alternating groups of characters */
void printCheckerLine(int checkerWidth, int checkerCount, char c1, char c2)
{
	/* TODO: complete implementation */

	int i, j;
	for (i=0; i<checkerCount; ++i) {
		/* detect which character to print */
		char c = c1;
		if ((i % 2) == 1) {
			c = c2;
		}
		/* print block of character */
		for (j=0; j<checkerWidth; ++j) {
			printf("%c", c);
		}
	}

	/* print newline */
	printf("\n");
}

void printCheckerBoard(int checkerWidth, int checkerCount, char c1, char c2)
{
	/* TODO: complete implementation */
	int i, j;
	for (i=0; i<checkerCount; ++i) {

		/* detect which character to start with */
		char a = c1;
		char b = c2;
		if ((i%2) == 1) {
			a = c2;
			b = c1;
		}

		/* print block of rows */
		for (j=0; j<checkerWidth; ++j) {
			printCheckerLine(checkerWidth, checkerCount, a, b);
		}
	}

}