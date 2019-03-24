/**
 * Determines the length of a string with provided array size
 * Params:
 *   str  - string to compute length of
 *   size - size of the str array
 * Return:
 *   - length of the string if terminating NUL character is found
 *   - size if the NUL character is not found in the array
 */
int strlen_safe(char str[], int size) 
{ 
	/* TODO: function implementation */
	int len = 0;
	while (str[len] != '\0' && len < size) {
		++len;
	}

	return len;
}

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
void strcpy_safe(char dest[], int dsize, char src[], int ssize) 
{
	/* TODO: function implementation */
	int len = 0;
	while (src[len] != '\0' && len < dsize-1 && len < ssize) {
		dest[len] = src[len];
		++len;
	}
	dest[len] = '\0';
}

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
void strcat_safe(char dest[], int dsize, char src[], int ssize)
{
	/* TODO: function implementation */

	/* get to end of dest */
	int len = 0;
	int i = 0;
	while (dest[len] != '\0' && len < dsize) {
		++len;
	}

	/* copy over from src */
	while (len < dsize-1 && src[i] != '\0' && i < ssize) {
		dest[len] = src[i];
		++len;
		++i;
	}

	/* terminating nul */
	if (len < dsize) {
		dest[len] = '\0';
	}
}