/* headers */
#include <stdio.h>

/* function prototypes */
int search(int value, int array[], int arraySize);

/* main function */
int main(void)
{
	/* sample 1 */
	int vals1[] = {2, 3, 5, 7, 11, 13, 17, 19};
	int idx1 = search(5, vals1, 8);
	printf("%d\n", idx1);

	/* sample 2 */
	int vals2[] = {1, 2, 3, 4, 4, 3, 2, 1};
	int idx2 = search(4, vals2, 7);
	printf("%d\n", idx2);

	/* sample 3 */
	int vals3[] = {2, 4, 6, 8, 10, 12};
	int idx3 = search(3, vals3, 6);
	printf("%d\n", idx3);

	return 0;
}
