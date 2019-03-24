The `<string.h>` header contains several useful functions for manipulating C-strings, including determining the length, copying, and appending:
```c
int   strlen(char str[]);               /* returns the length of the string           */
char* strcpy(char dest[], char src[]);  /* copies src string to dest, returning dest  */
char* strcat(char dest[], char src[]);  /* appends src onto dest, returning dest      */
```
These functions, however, are known to be *unsafe* in practice: if the provided string is not a valid C-string (i.e. does not have a terminating `'\0'` character), then the functions will continue operating outside of the bounds of allowed memory.  This can lead to memory leaks, or worse, can leave your code susceptible to [buffer overflow attacks](https://en.wikipedia.org/wiki/Buffer_overflow).  This is the main reason why Visual Studio forces you to explicitly disable security warnings if you want to use one of these functions:
```c
#define _CRT_SECURE_NO_WARNINGS
```
It is trying to coerce you into avoiding them, or to use alternate "safe" versions.

Instead, we will re-implement *safe versions* of the above functions ourselves.  Complete the implementations for the following functions:

```c
/**
 * Determines the length of a string with provided array size
 * Params:
 *   str  - string to compute length of
 *   size - size of the str array
 * Return:
 *   - length of the string if terminating NUL character is found
 *   - size if the NUL character is not found in the array
 */
int strlen_safe(char str[], int size);

/**
 * Copies a string to the destination which has a given array size.
 * If the src string is longer than dest, then only copy the characters 
 * that fit while ensuring dest is a valid C-string.  If src is not a 
 * valid C-string, then do not go past the length of the array.
 * Params:
 *   dest  - destination
 *   dsize - size of the dest array
 *   src   - source string to copy
 *   ssize - size of src array
 */
void strcpy_safe(char dest[], int dsize, char src[], int ssize);

/**
 * Appends a string to the destination which has a given array size.
 * If dest is not a valid C-string, then leave it unmodified and return.
 * If the src string does not fit on the end of dest, then only copy 
 * the characters that do fit while ensuring dest is a valid C-string.
 * Params:
 *   dest  - destination
 *   dsize - size of the dest array
 *   src   - source string to copy
 *   ssize - size of the src array
 */
void strcat_safe(char dest[], int dsize, char src[], int ssize);
```
These versions should never go past the specified array sizes.  You are not allowed to use any of the functions contained in `<string.h>`.

### Submission

Your submission should include your function implementations only.  Do not include a `main` function: that will be handled for you behind-the-scenes.

---

### Sample Usage

Consider the sequence of commands
```c
/* test our string functions */
int len;
char dest[100];

/* length */
len = strlen_safe("hello, world", 13);
printf("%d\n", len);
len = strlen_safe("hello, world", 5);
printf("%d\n", len);

/* copy */
strcpy_safe(dest, 100, "I love apples!!", 16);
printf("%s\n", dest);
strcpy_safe(dest, 100, "I love apples!!", 1);
printf("%s\n", dest);
strcpy_safe(dest, 7, "I love apples!!", 16);
printf("%s\n", dest);

/* concatenate */
strcpy_safe(dest, 14, "cats", 5);
printf("%s\n", dest);
strcat_safe(dest, 14, " say", 5);
printf("%s\n", dest);
strcat_safe(dest, 14, " meowzer", 9);
printf("%s\n", dest);
```

### Output

```default
12
5
I love apples!!
I
I love
cats
cats say
cats say meow
```

### Explanation

- The length of the string `"hello, world"` is 12 (does not include the terminating `'\0'`).
- Restricting the input size to 5, the size is returned since `'\0'` is not found within the provided bounds.
- The entire string `"I love apples!!"` is copied over to dest
- Restricting the input size to 1, only the character `'I'` is copied.
- Restricting the destination size to 7, only the six characters `"I love"` are copied over, then the dest string is terminated by `'\0'`.
- The destination string is initialized to `"cats"`.
- The string `" say"` is appended to `"cats"`
- Restricting the destination size to 14, only the `"meow"` part of `"meowzer"` fits when concatenating, leaving one last space in the array for the terminating `'\0'`.

---

### Testing

To test your functions at home, see the sample `safestrings_main.c` file in the attachments sections.  You can include this file alongside `safestrings.c` in your project in Visual Studio or Xcode.  Both files must belong to the project in order to be compiled together.  When multiple files are added to a project, they are compiled and linked into a single program.  

When submitting, only submit the `safestrings.c` file.

