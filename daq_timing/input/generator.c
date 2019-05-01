#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[])
{

	if (argc < 4) {
		printf("\nUsage:\n\t%s <start> <step> <stop>\n\n", argv[0]);
	}

	int start = (int)round(atof(argv[1])*100);
	int step = (int)round(atof(argv[2])*100);
	int stop = (int)round(atof(argv[3])*100);
	int t;

	for (t = start; t <= stop; t += step) {
		double s = t / 100.0;
		printf("%.2f %d %d\n", s, 0, 0);
	}

	return 0;
}