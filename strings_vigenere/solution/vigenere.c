#include <string.h>
/*
 * Encrypts a plaintext message using the provided key.
 */
void encrypt(char plaintext[], char key[], char ciphertext[])
{
	/* TODO: encryption implementation */
	int i = 0;
	int keylen = strlen(key);
	for (i = 0; plaintext[i] != '\0'; ++i) {
		int j = key[i % keylen] - 'A';
		if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
			ciphertext[i] = ((plaintext[i] - 'a' + j) % 26) + 'A';
		} else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
			ciphertext[i] = ((plaintext[i] - 'A' + j) % 26) + 'A';
		} else {
			ciphertext[i] = plaintext[i];
		}
	}
	ciphertext[i] = '\0';
}

/*
 * Decrypts a ciphertext message using the provided key.
 */
void decrypt(char ciphertext[], char key[], char plaintext[])
{
	/* TODO: decryption implementation */
	int i = 0;
	int keylen = strlen(key);
	for (i = 0; ciphertext[i] != '\0'; ++i) {
		int j = (26 - key[i % keylen] + 'A') % 26;
		if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
			plaintext[i] = ((ciphertext[i] - 'a' + j) % 26) + 'A';
		} else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
			plaintext[i] = ((ciphertext[i] - 'A' + j) % 26) + 'A';
		} else {
			plaintext[i] = ciphertext[i];
		}
	}
	plaintext[i] = '\0';
}