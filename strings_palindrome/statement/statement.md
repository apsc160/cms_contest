A *palindrome* is a word or phrase that is the same forwards as backwards.  For our purposes, all of the following strings are considered palindromes:
```default
"madam"
"race car"
"Madam, I'm Adam"
"Never odd or even"
"Doc, note: I dissent. A fast never prevents a fatness. I diet on cod."
"T. Eliot, top bard, notes putrid tang emanating, is sad; I'd assign it a name: gnat dirt upset on drab pot toilet."
```
Note that only letters are considered in determining if a string is a palindrome; punctuation, spaces, and letter-case are ignored.

Complete the function
```c
int is_palindrome(char str[]);
```
that returns `TRUE` (1) if the provided string is a palindrome, or `FALSE` (0) otherwise.  The empty string `""` *is* considered a palindrome.

### Submission

Your submission should include your function implementation only.  Do not include a `main` function: that will be handled for you behind-the-scenes.

