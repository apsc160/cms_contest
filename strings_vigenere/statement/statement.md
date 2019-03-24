The [Vigenère cipher](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher) is a simple encryption technique that can be used to encrypt/decrypt a secret message.  It is a modification of the [Caesar Cipher](https://en.wikipedia.org/wiki/Caesar_cipher), where each letter is shifted by an amount that depends on a codeword.  The  original  message  is  known  as  the *plaintext*,  the  encrypted message as the *ciphertext*, and the codeword - which defines by how much to shift each letter - is the *key*.

To encrypt a message, first choose a codeword consisting of all upper-case letters.  Repeat the codeword over and over to create a codestring with length equal the length of the message.  Each letter in the codestring governs how much to shift the corresponding character in the message, with `'A'` meaning to shift by 0, and `'Z'` to shift by 25, wrapping around if necessary.

For example, consider the plaintext message `"THIS MESSAGE IS SECRET"`, and a key `"APSC"`:
```default
codestring:  APSCAPSCAPSCAPSCAPSCAP
plaintext:   THIS MESSAGE IS SECRET
ciphertext:  TWAU BWUSPYG XK STUTEI
```
Any letter in the plaintext that corresponds to an `'A'` in the codestring remains unshifted.  Since `'P'` is the 16th letter of the alphabet (index 15), every character in the plaintext corresponding to a `'P'` is shifted up by 15, wrapping around if necessary: the `'H'` becomes `'W'`, `'S'` becomes `'H'`, *et cetera*.  Any non-letters - such as spaces are punctuation - are left unmodified.  Any lower-case letter should first be converted to upper-case while encrypting or decrypting.  

We can decrypt a message by applying the reverse shift operation.  For example, with the same key as before, we may decrypt the following:
```default
codestring:  APSCAPSCAPSCAPSCAPSCAPSCAPSCAPSC
ciphertext:  TwAu BwUsPyG xK nD nOcYgR kGcGwV
plaintext:   THIS MESSAGE IS NO LONGER SECRET
```

Complete the following functions to encrypt and decrypt a secret message.

```c
/*
 * Encrypts a plaintext message using the provided key.
 */
void encrypt(char plaintext[], char key[], char ciphertext[]);

/*
 * Decrypts a ciphertext message using the provided key.
 */
void decrypt(char ciphertext[], char key[], char plaintext[]);
```
All three arguments to both functions are assumed to be valid C-strings.

### Submission

Your submission should include your function implementations only.  Do not include a `main` function: that will be handled for you behind-the-scenes.

---

### Sample Usage

Consider the sequence of commands
```c
char str[250];

encrypt("THIS MESSAGE IS SECRET", "APSC", str);
printf("%s\n", str);

decrypt("TwAu BwUsPyG xK nD nOcYgR kGcGwV", "APSC", str);
printf("%s\n", str);

encrypt("Professor Plum, in the Dining Room, with the candlestick", "CLUE", str);
printf("%s\n", str);

decrypt("JSZV WR ESS QXLCG", "YELLOW", str);
printf("%s\n", str);
```

### Output

```default
TWAU BWUSPYG XK STUTEI
THIS MESSAGE IS NO LONGER SECRET
RCIJGDMST JPWX, KY XJP HKYCRI LSQX, YTNL EBI NURFWYWVTWO
JSZV WR ESS QXLCG
```

### Explanation

Each message is either encrypted or decrypted using the Vigenère cipher and provided key.  Note that outputs are all uppercase, regardless of the case of the input.  Also, any non-letter characters, such as spaces and punctuation, are copied without conversion.

---

### Testing

To test your functions at home, see the sample `vigenere_main.c` file in the attachments sections.  You can include this file alongside `vigenere.c` in your project in Visual Studio or Xcode.  Both files must belong to the project in order to be compiled together.  When multiple files are added to a project, they are compiled and linked into a single program.  

When submitting, only submit the `vigenere.c` file.
