A [magic square](https://en.wikipedia.org/wiki/Magic_square) is an $n\times n$ arrangement of the numbers $1$ to $n^2$ such that every row, column, and the two main diagonals have the exact same sum.  For example, 

<table border="1" align="center">
	<tr><td>4</td><td>9</td><td>2</td></tr>
	<tr><td>3</td><td>5</td><td>7</td></tr>
	<tr><td>8</td><td>1</td><td>6</td></tr>
</table>

is a magic square for $n = 3$.  The square contains all values from 1 to 9, and each row, column and both diagonals add up to 15.

### Task:

You are to write a function 
```c
int isMagicSquare(int square[MAX_N][MAX_N], int n);
```
that accepts a 2D square array of numbers, along with the square size, and returns `TRUE` (1) if the array represents a magic square, or `FALSE` (0) if it does not.

You should define the following symbolic constants before your function:

```c
#define TRUE  1
#define FALSE 0
#define MAX_N 100
```

Note that the maximum value for $n$ is quite large.  To receive full marks, your program must return a correct result within 5 seconds.

Do not submit a `main` function, as this will be handled for you behind-the-scenes.

---

### Sample Usage

See the following examples:
```c
int square1[MAX_N][MAX_N] = {
		{4, 9, 2},
		{3, 5, 7},
		{9, 1, 6}};

int square2[MAX_N][MAX_N] = {
		{20,  6,  7, 17},
		{ 9, 15, 14, 12},
		{13, 11, 10, 16},
		{ 8, 18, 19, 5}	};

int square3[MAX_N][MAX_N] = {
		{17, 24,  1, 15,  8},
		{23,  5,  7, 16, 14},
		{ 4,  6, 13, 22, 20},
		{10, 12, 19,  3, 21}, 
		{11, 18, 25,  9,  2}};

int check1 = isMagicSquare(square1, 3);  /* returns TRUE */
int check2 = isMagicSquare(square2, 4);  /* returns FALSE */
int check3 = isMagicSquare(square3, 5);  /* returns FALSE */
```
The first square, `square1`, is a magic square, as previously described.

The second, `square2`, satisfies that all rows, columns, and diagonals have the same sum (50).  However, the square does not contain all numbers in the range $1, \ldots, 16$.

The third, `square3`, contains all numbers in the range $1,\ldots,25$, and every row and column have the same sum, however the two diagonals do not.

---
### Testing

To test your function at home, see the sample `magic_main.c` file in the attachments sections.  You can include this file alongside `magic.c` in your project in Visual Studio or Xcode.  Both files must belong to the project in order to be compiled together.  When multiple files are added to a project, they are compiled and linked into a single program.  

When submitting, only upload the `magic.c` file.  If you receive a compile error related to multiple definitions, it is because you included a `main(..)` when you were asked not to.


