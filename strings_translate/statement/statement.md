Write a simple translation function
```c
/*
 * translates between languages word-for-word using the provided dictionaries
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
);
```

You may assume the following
- The maximum word size is 100
- Words consist of only letters (i.e. `a-zA-Z`)
- Words are separated by any non-letter, or the beginning/end of the string
- Word matching to the dictionary is independent of case (e.g. `"Hello"` matches dictionary word `"hello"`)
- The translated word should preserve the case of the first letter and first letter only (e.g. `"Hello"` is replaced with `"Bonjour"`, `"hello"` is replaced by `"bonjour"`, and `"HELLO"` is replaced by `"Bonjour"`)
- Words not found in the dictionary are copied directly to the output as-is, as are other characters such as punctuation
- Only complete words are translated, not partial matches (see example below)

---

### Example

```c
#define MAX_WORD_SIZE 100
#define MAX_SENTENCE_SIZE 1000
#define NUM_WORDS     10

/* define dictionaries */
const char english[NUM_WORDS][MAX_WORD_SIZE] = {
	"a", "fun", "hello", "I", "is", "love", "programming", "the", "without" "world"
}; 
const char french[NUM_WORDS][MAX_WORD_SIZE] = {
	"un", "amusante", "bonjour", "je", "est", "aime", "programmation", "le", "sans", "monde"
};

/* output */
char output1[MAX_SENTENCE_SIZE];
char output2[MAX_SENTENCE_SIZE];

translate("Hello, world!", english, french, NUM_WORDS, output1);
printf("%s\n", output1);

translate(output1, french, english, NUM_WORDS, output2);
printf("%s\n, output2);

translate("I love Lucy!!", english, french, NUM_WORDS, output1);
printf("%s\n", output1);

translate("Imagine a world without programming.", english, french, NUM_WORDS, output1);
printf("%s, output1);
```

### Output

```default
Bonjour, monde!
Hello, world!
Je aime Lucy!!
Imagine un monde sans programmation
```

### Explanation

The sentences were translated word-for-word, preserving the case of the first letter of each word.  The words `"Lucy"` and "`Imagine"` were not found in the dictionary, so were not replaced.  In particular, note that the `I` in `"Imagine"` was not replaced, even though `I` *is* in the dictionary (only entire words are replaced).  Punctuation was also copied directly to the output.