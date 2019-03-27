/* headers */
#include <stdio.h>

/* constants */
#define LINE_SIZE     250
#define MAX_WORD_SIZE 100
#define MAX_NUM_WORDS 20

/* function prototypes */
void translate(
	char input[], 
	char fromDictionary[][MAX_WORD_SIZE],
	char toDictionary[][MAX_WORD_SIZE],
	int dictionarySize, 
	char output[]
);

int main(void)
{
	char line[LINE_SIZE];
	char output[LINE_SIZE];
	int nwords = 0;
	int nread = 0;
	int i = 0;

	char fromDict[MAX_NUM_WORDS][MAX_WORD_SIZE];
	char toDict[MAX_NUM_WORDS][MAX_WORD_SIZE];

	/* read dictionary - numWords, {fromWord toWord} pairs */
	nread = scanf("%d", &nwords);
	for (i = 0; i<nwords; ++i) {
		nread = scanf("%s", fromDict[i]);
		nread = scanf("%s", toDict[i]);
	}

	/* newline */
	nread = scanf("\n");

	/* lines-to-translate */
	while (scanf("%[^\n]\n", line) != EOF) {
		/* translate */
		translate(line, fromDict, toDict, nwords, output);
		printf("%s\n", output);
	}

	return 0;
}
