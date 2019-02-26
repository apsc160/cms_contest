#include <stdio.h>

#define INPUT_FILE  "numbers.txt"
#define OUTPUT_FILE "sum.txt"

/* main program file */
int fileio(void);

/* generates input file for fileio */
int main(void)
{
    FILE* fin = NULL;  /* input file  */
    FILE* fout = NULL; /* output file */
    int num = 0;
    int ret = 0;
    
    fout = fopen(INPUT_FILE, "w");
    if (fout != NULL) {
        while (scanf("%d", &num) == 1) {
            fprintf(fout, "%d\n", num);
        }
        fclose(fout);
    }

    /* call program */
    ret = fileio();

    /* echo output file */
    fin = fopen(OUTPUT_FILE, "r");
    if (fin != NULL) {
        while (fscanf(fin, "%d", &num) == 1) {
            printf("%d\n", num);
        }
        fclose(fin);
    }

    /* clean-up */
    remove(INPUT_FILE);
    remove(OUTPUT_FILE);

    return ret;
}
