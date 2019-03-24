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

/* symbolic constants */
#define MAX_MESSAGE_LENGTH 250

/* function prototypes */
void encrypt(char plaintext[], char key[], char ciphertext[]);
void decrypt(char ciphertext[], char key[], char plaintext[]);

int main(void)
{
	/* test our vigenere encryption/decryption */
    char str[MAX_MESSAGE_LENGTH];

    encrypt("THIS MESSAGE IS SECRET", "APSC", str);
    printf("%s\n", str);

    decrypt("TwAu BwUsPyG xK nD nOcYgR kGcGwV", "APSC", str);
    printf("%s\n", str);

    encrypt("Professor Plum, in the Dining Room, with the candlestick", "CLUE", str);
    printf("%s\n", str);

    decrypt("JSZV WR ESS QXLCG", "YELLOW", str);
    printf("%s\n", str);

	return 0;
}
