#define TRUE  1
#define FALSE 0

/* returns TRUE if str is a palindrome, FALSE otherwise */
int is_palindrome(char str[])
{

	/* TODO: function implementation */
	int len = 0;
	int left = 0;
	int right = 0;

	/* find end of string */
	while (str[len] != '\0') {
		++len;
	}
	right = len;

	while (left < right) {
		/* advance left to next letter */
		while (left < len && !( (str[left] >= 'a' && str[left] <= 'z') || (str[left] >= 'A' && str[left] <= 'Z') ) ){
			++left;
		}

		/* advance right to previous letter */
		while (right > 0 && !( (str[right] >= 'a' && str[right] <= 'z') || (str[right] >= 'A' && str[right] <= 'Z') ) ){
			--right;
		}

		/* if both are letters, check that they are equal (ignoring case) */
		if (left < right) {
			
			char uleft = str[left];
			char uright = str[right];

			/* convert to uppercase */
			if (uleft >= 'a' && uleft <= 'z') {
				uleft = uleft - 'a' + 'A';
			}
			if (uright >= 'a' && uright <= 'z') {
				uright = uright - 'a' + 'A';
			}

			/* don't match, return FALSE */
			if (uleft != uright) {
				return FALSE;
			}

			/* advance characters */
			++left;
			--right;
		}
	}

	return TRUE;
}
