/* 
 * Testing file for checkboard implementation 
 * 
 * To test your solution, include both this file and your 
 * checkerboard.c implementation into a single project.  Visual Studio
 * (or Xcode, or whatever IDE you use) should compile both files
 * into a single program.
 */

/* headers */
#include <stdio.h>

/* function prototypes */
void printChars(int size, char c );
void printCheckerLine(int checkerWidth, int checkerCount, char c1, char c2);
void printCheckerBoard(int checkerWidth, int checkerCount, char c1, char c2);

/* print a group of a single character */
void printChars(int size, char c )
{
    int i; 
    /* print character size times */
    for (i=0; i<size; i++) {
        printf( "%c", c );        
    }
}

int main(void)
{
	/* test our print functions */
	printCheckerLine(2, 2, 'A', 'B');
    printCheckerLine(3, 4, 'x', 'o');
    printCheckerLine(1, 15, '#', '_');

	printCheckerBoard(2, 2, 'A', 'B');
    printCheckerBoard(3, 4, 'x', 'o');
    printCheckerBoard(1, 15, '#', '_');

	return 0;
}