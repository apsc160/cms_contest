#define MAX_WORD_SIZE 100
#define TRUE  1
#define FALSE 0

int is_letter(char c) {
	return ( (c >= 'a' && c <= 'z') || (c >=  'A' && c <= 'Z') );
}

char to_lower(char c) {
	if (c >= 'A' && c <= 'Z') {
		c = c - 'A' + 'a';
	}
	return c;
}

char to_upper(char c) {
	if (c >= 'a' && c <= 'z') {
		c = c - 'a' + 'A';
	}
	return c;
}

char is_upper(char c) {
	if (c >= 'A' && c <= 'Z') {
		return TRUE;
	}
	return FALSE;
}

/* finds a word in the dictionary, -1 if not found */
int findWord(char str[], int word_start, int word_end, char dict[][MAX_WORD_SIZE], int dsize)
{
	int i = 0;
	int j = 0;
	int wlen = word_end - word_start;

	/* check every word in dictionary */
	for (i = 0; i < dsize; ++i) {
		int match = TRUE;

		/* check if word matches */
		for (j = 0; j < wlen && dict[i][j] != '\0'; ++j) {
			if (to_lower(str[word_start+j]) != to_lower(dict[i][j])) {
				match = FALSE;
				break;
			}
		}

		/* check for ending */
		if (j < wlen || dict[i][j] != '\0') {
			match = FALSE;
		}

		if (match) {
			return i;
		}
	}

	return -1;
}

/*
 * Translates between languages word-for-word using the provided dictionaries
 *
 * Params:
 *    input - input sentence to translate
 *    fromDictionary - dictionary for input words
 *    toDictionary - dictionary of corresponding foreign words
 *    dictionarySize - number of words in the dictionary
 *    output - translated output sentence
 */
void translate(
	char input[], 
	char fromDictionary[][MAX_WORD_SIZE],
	char toDictionary[][MAX_WORD_SIZE],
	int dictionarySize, 
	char output[]
)
{

	/* TODO: translation */
	int word_start = 0;
	int word_end = 0;
	int out_pos = 0;
	int word_idx = 0;
	int i = 0;

	/* loop until end of string */
	while (input[word_start] != '\0') {

		/* advance to next letter */
		while (!is_letter(input[word_start])) {
			output[out_pos++] = input[word_start];
			++word_start;
		}

		/* advance to end of word */
		word_end = word_start;
		while (is_letter(input[word_end])) {
			++word_end;
		}

		/* look for word in dictionary */
		word_idx = findWord(input, word_start, word_end, fromDictionary, dictionarySize);
		if (word_idx < 0) {
			/* copy directly */
			for (i = word_start; i < word_end; ++i) {
				output[out_pos++] = input[i];
			}
		} else {
			/* translate */
			for (i = 0; toDictionary[word_idx][i] != '\0'; ++i) {
				if (i == 0 && is_upper(input[word_start])) {
					output[out_pos++] = to_upper(toDictionary[word_idx][i]);
				} else {
					output[out_pos++] = to_lower(toDictionary[word_idx][i]);
				}
			}
		}

		/* advance to next character */
		word_start = word_end;
	}

	/* terminate string */
	output[out_pos] = '\0';

}