#define _CRT_SECURE_NO_WARNINGS

/* headers */
#include <stdio.h>

/* symbolic constants */
#define MAX_N 100
#define TRUE  1
#define FALSE 0

/* function prototype */
int isMagicSquare(int square[MAX_N][MAX_N], int n);

/*
 * Input format:
 *   - t # tests
 *      - n size of 
 *      - n x n elements of square
 */
int main(void)
{
	int i, j, t;
	int T = 0;
	int N = 0;
	int square[MAX_N][MAX_N];
	int check = FALSE;

	scanf("%d", &T);
	for (t = 0; t < T; ++t) {
		scanf("%d", &N);
		for (i = 0; i < N; ++i) {
			for (j = 0; j < N; ++j) {
				scanf("%d", &square[i][j]);
			}
		}

		check = isMagicSquare(square, N);
		if (check) {
			printf("TRUE\n");
		} else {
			printf("FALSE\n");
		}
	}

	return 0;
}