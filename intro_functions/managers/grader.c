
#include <stdio.h>
#include <string.h>

void printChars(int size, char c );  /* provided, DO NOT IMPLEMENT */
void printCheckerLine(int checkerWidth, int checkerCount, char c1, char c2);
void printCheckerBoard(int checkerWidth, int checkerCount, char c1, char c2);

int main(void)
{
	char command[80];
	int checkerWidth = 0;
	int checkerHeight = 0;
	char c1, c2;

	/* read commands from file */
	/* <command> <width> <count> <c1> <c2> */
	while (scanf("%s %d %d %c %c", command, &checkerWidth, &checkerHeight, &c1, &c2) == 5) {
		if (strcmp(command, "printCheckerLine") == 0) {
			printCheckerLine(checkerWidth, checkerHeight, c1, c2);
		} else if (strcmp(command, "printCheckerBoard") == 0) {
			printCheckerBoard(checkerWidth, checkerHeight, c1, c2);
		}
	}

	return 0;
}