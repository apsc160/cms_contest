/* 
 * Testing file for vigenere implementation 
 * 
 * To test your solution, include both this file and your 
 * vigenere.c implementation into a single project.  Visual Studio
 * (or Xcode, or whatever IDE you use) should compile both files
 * into a single program.
 */

/* headers */
#include <stdio.h>
#include <string.h>

#define MAX_MESSAGE_LENGTH 250
#define MAX_KEY_LENGTH     50

/* function prototypes */
void encrypt(char plaintext[], char key[], char ciphertext[]);
void decrypt(char ciphertext[], char key[], char plaintext[]);

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
	char plaintext[MAX_MESSAGE_LENGTH];
	char ciphertext[MAX_MESSAGE_LENGTH];
	char key[MAX_KEY_LENGTH];
	char command[80];

	/* read commands from file */
	/* <command> <args> */
	while (scanf("%s", command) == 1) {
		if (strcmp(command, "encrypt") == 0) {

			scan_quoted_string(plaintext, MAX_MESSAGE_LENGTH);
			scan_quoted_string(key, MAX_KEY_LENGTH);
			encrypt(plaintext, key, ciphertext);
			printf("%s\n", ciphertext);

		} else if (strcmp(command, "decrypt") == 0) {

			scan_quoted_string(ciphertext, MAX_MESSAGE_LENGTH);
			scan_quoted_string(key, MAX_KEY_LENGTH);
			decrypt(ciphertext, key, plaintext);
			printf("%s\n", plaintext);
			
		}
	}

	return 0;
}
