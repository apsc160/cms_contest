/* symbolic constants */
#define MAX_N 100
#define TRUE  1
#define FALSE 0

#include <stdio.h>

/* checks if a square is magical */
int isMagicSquare(int square[MAX_N][MAX_N], int n)
{
	/* slow n^4 check for 1 to n^2 */
	int n2 = n*n;
	for (int k = 1; k <= n2; ++k) {
		int found = FALSE;
		for (int i=0; i<n && !found; ++i) {
			for (int j=0; j<n && !found; ++j) {
				if (square[i][j] == k) {
					found = TRUE;
				}
			}
		}

		if (!found) {
			return FALSE;
		}
	}

	/* determine diagonal sums */
	int sum = 0;
	int diagsum = 0;
	for (int i=0; i<n; ++i) {
		sum += square[i][i];
		diagsum += square[i][n-i-1];
	}
	if (diagsum != sum) {
		return FALSE;
	}

	/* check row/col sums */
	for (int i=0; i<n; ++i) {
		int rowsum = 0;
		int colsum = 0;

		for (int j=0; j<n; ++j) {
			rowsum += square[i][j];
			colsum += square[j][i];
		}

		if (rowsum != sum || colsum != sum) {
			return FALSE;
		}
	}

	return TRUE;
}
