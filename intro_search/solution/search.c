/**
 * Searches through the array to find the index of the first occurrence
 * of a specified value.  Returns -1 if value is not found.
 */
int search(int value, int array[], int arraySize) 
{
	int i;
	for (i = 0; i < arraySize; ++i) {
		if (array[i] == value) {
			return i;
		}
	}

    return -1;
}
