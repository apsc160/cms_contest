Write a function
```c
int search(int value, int array[], int arraySize);
```
that searches through the provided `array` of size `arraySize` for the specified `value`.  The function should return the index of the *first* occurrence of `value` if found, or -1 if not found.  If the value is found, then your function should exit the search loop early (using either a `break` or early `return` statement).

Do not submit a `main` function, as this will be handled for you behind-the-scenes. 

---

### Sample 1:

```c
int vals1[] = {2, 3, 5, 7, 11, 13, 17, 19};
int idx1 = search(5, vals1, 8);   /* returns 2 */
```
The value `5` is found in `vals` at position `2`.

### Sample 2:

```c
int vals2[] = {1, 2, 3, 4, 4, 3, 2, 1};
int idx2 = search(4, vals2, 7);   /* returns 3 */
```
The value `4` is found in `vals` at positions `3` and `4`, though the *first* occurrence is at index `3`.

### Sample 3:

```c
int vals3[] = {2, 4, 6, 8, 10, 12};
int idx3 = search(3, vals3, 6);   /* returns -1 */
```
The value `3` is not found in `vals`, so `-1` is returned.

---

### Testing

To test your function at home, see the sample `search_main.c` file in the attachments sections.  You can include this file alongside `search.c` in your project in Visual Studio or Xcode.  Both files must belong to the project in order to be compiled together.  When multiple files are added to a project, they are compiled and linked into a single program.  

When submitting, only submit the `search.c` file.  If you receive a compile error related to multiple definitions, it is because you included a `main(..)` function when you were asked not to.
