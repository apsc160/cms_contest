#include <stdio.h>

#define INPUT_FILE "data.txt"

int regression(void);

/* generate output file and call regression */
int main(void)
{
    FILE* fout = NULL;  /* output file  */
    double x = 0;       /* values */
    double y = 0;
    int ret = 0;        /* return value */

    /* copy data to file */
    fout = fopen(INPUT_FILE, "w");
    if (fout != NULL) {
        while (scanf("%lf %lf", &x, &y) == 2) {
           fprintf(fout, "%lf %lf\n", x, y);
        }
        fclose(fout);
    }

    /* call regression program */
    ret = regression();

    /* clean-up */
    remove(INPUT_FILE);

    return ret;
}