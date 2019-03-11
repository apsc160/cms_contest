#include <stdio.h>

int base7(int d) {
	int s = 0;
	int e = 1;
	int digit = 0;
	while (d > 0) {
		digit = d % 7;
		d = d / 7;
		s = s + digit * e;
		e = e * 10;
	}

	return s;
}

int main(void) 
{
	int v = 0;
	while (scanf("%d", &v) == 1) {
		int s = base7(v);
		printf("%d\n", s);
	}

	return 0;
}