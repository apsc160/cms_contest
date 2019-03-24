/* headers */
#include <stdio.h>
#include <string.h>

/* function prototypes */
int  strlen_safe(char str[], int size);
void strcat_safe(char dest[], int dsize, char src[], int ssize);
void strcpy_safe(char dest[], int dsize, char src[], int ssize);

void scan_quoted_string(char* dest, int dsize) {
	char c;
	int len;

	/* quote */
	while ((scanf("%c", &c) == 1) && c != '\"') {}

	/* string until closed quote */
	len = 0;
	while ((scanf("%c", &c) == 1) && c != '\"' && len < dsize-1) {
		dest[len++] = c;
	}
	dest[len] = '\0';
}

int main(void)
{
	char command[100];
	char dest[100];
	char src[100];
	int  dsize;
	int  ssize;
	int  len;
	int  nscan;

	/* read commands from file */
	/* <command> <args> */
	while (scanf("%s", command) == 1) {
		if (strcmp(command, "strlen_safe") == 0) {

			scan_quoted_string(src, 80);
			nscan = scanf("%d", &ssize);
			len = strlen_safe(src, ssize);
			printf("%d\n", len);

		} else if (strcmp(command, "strcpy_safe") == 0) {

			scan_quoted_string(dest, 80);
			nscan = scanf("%d", &dsize);
			scan_quoted_string(src, 80);
			nscan = scanf("%d", &ssize);

			strcpy_safe(dest, dsize, src, ssize);
			printf("%s\n", dest);
			
		} else if (strcmp(command, "strcat_safe") == 0) {

			scan_quoted_string(dest, 80);
			nscan = scanf("%d", &dsize);
			scan_quoted_string(src, 80);
			nscan = scanf("%d", &ssize);

			strcat_safe(dest, dsize, src, ssize);
			printf("%s\n", dest);

		}
	}

	return 0;
}
