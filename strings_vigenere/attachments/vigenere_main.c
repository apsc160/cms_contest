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

#define MAX_MESSAGE_LENGTH 250
#define MAX_KEY_LENGTH     5

/* function prototypes */
void encrypt(char plaintext[], char key[], char ciphertext[]);
void decrypt(char ciphertext[], char key[], char plaintext[]);

int main(void)
{
	/* test our vigenere encryption/decryption */
    char str[MAX_MESSAGE_LENGTH];
    encrypt("THIS MESSAGE IS SECRET", "APSC", str);
    printf("%s\n", str);
    decrypt(str, "APSC", str);
    printf("%s\n", str);

    encrypt("THIS MESSAGE IS NO LONGER SECRET", "APSC", str);
    printf("%s\n", str);
    decrypt(str, "APSC", str);
    printf("%s\n", str);

	return 0;
}