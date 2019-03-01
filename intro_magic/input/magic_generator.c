#include <stdio.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0

/* generates magic square of odd order */
int generate_odd(int* square, int n)
{
	int n2 = n*n;
	int i = 0;
	int x = (n-1)/2;
	int y = 0;

	/* initialize with zeroes */
	for (i = 0; i < n2; ++i) {
		square[i] = 0;
	}

	/* NE pattern starting with center-top */
	for (i = 0; i < n2; ++i) {
		/* shift down until next empty square */
		if (square[x * n + y] != 0) {
			x = (x + n - 1) % n;
			y = (y + 2) % n;
		}
		/* fill in square */
		square[x * n + y] = i + 1;
		x = (x + 1) % n;
		y = (y + n - 1) % n;
	}

	return TRUE;
}

/* generates magic square of doubly-even order */
int generate_doubly_even(int* square, int n)
{
	int i, j;
	int n2 = n*n;
	int a = n/4;
	int b = 3*a;

	/* fill square with ordered numbers */
    for ( i = 0; i<n; i++)  {
        for ( j = 0; j<n; j++) {
            square[i + n*j] = i + n*j + 1;
		}
    }

	/* swap values at corners and following pattern */
    for ( i = 0; i < a; i++) {
        for ( j = 0; j < a; j++) {
            square[i + n*j] = (n2 + 1) - square[i + n*j];
			square[i + n*(j + b)] = (n2 + 1) - square[i + n*(j + b)];
			square[i + b + n*j] = (n2 + 1) - square[i + b + n*j];
			square[i + b + n*(j + b)] = (n2 + 1) - square[i + b + n*(j + b)];
		}
    }
 
    for ( i = a; i < b; i++) {
        for ( j = a; j< b; j++) {
            square[i + n*j] = (n2 + 1) - square[i + n*j];
		}
    } 

	return TRUE;
}

/* generates magic squares */
int main(int argc, char* argv[])
{
	int n = 0;
	int* square = NULL;
	int success = FALSE;

	if (argc < 2) {
		printf("Usage:\n\t%s <size>", argv[0]);
		return 1;
	}

	n = atoi(argv[1]);

	square = (int*)malloc(n*n*sizeof(int));
	
	if ((n % 2) == 1) {
		/* generate odd square */
		success = generate_odd(square, n);
	} else if ( (n % 4) == 0) {
		/* generate doubly-even square */
		success = generate_doubly_even(square, n);
	} else {
		printf("singly even not implemented\n");
	}

	/* print square */
	if (success) {
		int i = 0, j = 0;
		printf("%d\n", n);
		for (i = 0; i < n; ++i) {
			for (j = 0; j < n; ++j) {
				printf(" %3d", square[i+j*n]);
			}
			printf("\n");
		}
	}

	/* clean up */
	free(square);
	square = NULL;

	return 0;
}

