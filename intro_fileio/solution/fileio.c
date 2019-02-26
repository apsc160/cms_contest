#include <stdio.h>

#define INPUT_FILE  "numbers.txt"
#define OUTPUT_FILE "sum.txt"

/* computes sum of integers in a file */
int fileio(void)
{
    FILE* fin = NULL;  /* input file     */
    FILE* fout = NULL; /* output file    */
    int num = 0;       /* number to read */
    int sum = 0;       /* sum            */
    
    /* TODO: read and add numbers from INPUT_FILE */
    fin = fopen(INPUT_FILE, "r");
    if (fin != NULL) {
        while (fscanf(fin, "%d", &num) == 1) {
            sum += num;
        }
        fclose(fin);
    }

    /* TODO: write sum to OUTPUT_FILE */
    fout = fopen(OUTPUT_FILE, "w");
    if (fout != NULL) {
        fprintf(fout, "%d\n", sum);
        fclose(fout);
    }

    return 0;
}
