You are given the following function
```c
/* 
 * Prints the given character the given number of times on the screen.
 * Parameter: size - the number of characters to print 
 * Parameter: c - the character to print 
 */
void printChars(int size, char c ) 
{    
    int i; 
    /* print character size times */
    for (i=0; i<size; i++) {
        printf( "%c", c );        
    }
}
```

### Step 1

Write a function 
```c
void printCheckerLine(int checkerWidth, int checkerCount, char c1, char c2);
```
that makes use of `printChars(...)` to print a single line of `checkerWidth*checkerCount` characters, starting with `checkerWidth` instances of character `c1`, followed by `checkerWidth` instances of characters `c1`, and alternating between the two.  The function must print a newline character `'\n'` at the end of the line.  See the following example outputs:

<table width="100%" border="1">
    <tr>
        <td><code>printCheckerLine(2, 2, 'A', 'B')</code></td>
        <td><code>printCheckerLine(3, 4, 'x', 'o')</code></td>
        <td><code>printCheckerLine(1, 15, '#', '_')</code></td>
    </tr>
    <tr>
        <td>
            <pre>AABB</pre>
        </td>
        <td>
            <pre>xxxoooxxxooo</pre>
        </td>
        <td>
            <pre>#_#_#_#_#_#_#_#</pre>
        </td>
    </tr>
</table>
 

### Step 2

Write a function
```c
void printCheckerBoard(int checkerWidth, int checkerCount, char c1, char c2);
```
that uses `printCheckerLine(...)` to print a square checkerboard pattern.  See the following example outputs:

<table width="100%" border="1">
    <tr>
        <td><code>printCheckerBoard(2, 2, 'A', 'B')</code></td>
        <td><code>printCheckerBoard(3, 4, 'x', 'o')</code></td>
        <td><code>printCheckerBoard(1, 15, '#', '_')</code></td>
    </tr>
    <tr valign="top"
    >
        <td>
<pre>AABB
AABB
BBAA
BBAA</pre>
        </td>
        <td>
<pre>xxxoooxxxooo
xxxoooxxxooo
xxxoooxxxooo
oooxxxoooxxx
oooxxxoooxxx
oooxxxoooxxx
xxxoooxxxooo
xxxoooxxxooo
xxxoooxxxooo
oooxxxoooxxx
oooxxxoooxxx
oooxxxoooxxx</pre>
        </td>
        <td>
<pre>#_#_#_#_#_#_#_#
_#_#_#_#_#_#_#_
#_#_#_#_#_#_#_#
_#_#_#_#_#_#_#_
#_#_#_#_#_#_#_#
_#_#_#_#_#_#_#_
#_#_#_#_#_#_#_#
_#_#_#_#_#_#_#_
#_#_#_#_#_#_#_#
_#_#_#_#_#_#_#_
#_#_#_#_#_#_#_#
_#_#_#_#_#_#_#_
#_#_#_#_#_#_#_#
_#_#_#_#_#_#_#_
#_#_#_#_#_#_#_#</pre>
        </td>
    </tr>
</table>

### Submission

Your submission should include the *function prototype* for `printChars(...)` **(do not include its implementation)**, as well as the implementation of your two added functions `printCheckerLine(...)` and `printCheckerBoard(...)`.  Do not include a `main` function: that will be handled for you behind-the-scenes.  Since you will be using the `printf(...)` function, you must include the `<stdio.h>` header file, even though you are not submitting a `main` function.  See the attached code template `checkerboard.c`.

To test your functions at home, see the sample `checkerboard_main.c` file in the attachments sections.

---

### Sample Output

Consider the given sequence of commands
```c
/* test our print functions */
printCheckerLine(2, 2, 'A', 'B');
printCheckerLine(3, 4, 'x', 'o');
printCheckerLine(1, 15, '#', '_');

printCheckerBoard(2, 2, 'A', 'B');
printCheckerBoard(3, 4, 'x', 'o');
printCheckerBoard(1, 15, '#', '_');
```

The resulting output should match precisely the following:

```default
AABB
xxxoooxxxooo
#_#_#_#_#_#_#_#
AABB
AABB
BBAA
BBAA
xxxoooxxxooo
xxxoooxxxooo
xxxoooxxxooo
oooxxxoooxxx
oooxxxoooxxx
oooxxxoooxxx
xxxoooxxxooo
xxxoooxxxooo
xxxoooxxxooo
oooxxxoooxxx
oooxxxoooxxx
oooxxxoooxxx
#_#_#_#_#_#_#_#
_#_#_#_#_#_#_#_
#_#_#_#_#_#_#_#
_#_#_#_#_#_#_#_
#_#_#_#_#_#_#_#
_#_#_#_#_#_#_#_
#_#_#_#_#_#_#_#
_#_#_#_#_#_#_#_
#_#_#_#_#_#_#_#
_#_#_#_#_#_#_#_
#_#_#_#_#_#_#_#
_#_#_#_#_#_#_#_
#_#_#_#_#_#_#_#
_#_#_#_#_#_#_#_
#_#_#_#_#_#_#_#
```

Be sure to match all newlines and spacings.