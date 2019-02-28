#include <stdio.h>

/* function prototypes */
int search(int value, int array[], int arraySize);

int main(void)
{
	/* input file format:
	 *   - # test cases 
	 *   	- size of array
	 *      	- array contents
	 *   	- value to search for
	 * 		- size to enter for arraySize 
	 * 			(could be different from above to ensure search terminates early)
	 */
	int i, j;
	int found = 0;
	int numTests = 0;
	int value = -1;
	int arraySize = 0;
	int searchSize = 0;
	int *array = NULL;

	/* number of tests */
	scanf("%d", &numTests);
	for (i = 0; i < numTests; ++i) {

		scanf("%d", &arraySize);
		array = (int*)malloc(arraySize*sizeof(int));

		for (j = 0; j < arraySize; ++j) {
			scanf("%d", &array[j]);
		}

		scanf("%d", &value);
		scanf("%d", &searchSize);

		/* search for value */
		found = search(value, array, searchSize);

		/* deallocate */
		free(array);
		array = NULL;
	}

	return 0;
}
