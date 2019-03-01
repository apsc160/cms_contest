/* headers */
#include <stdio.h>

/* symbolic constants */
#define MAX_N 100
#define TRUE  1
#define FALSE 0

/* function prototype */
int isMagicSquare(int square[MAX_N][MAX_N], int n);

/* main test function */
int main(void)
{
    int square1[MAX_N][MAX_N] = {
            {4, 9, 2},
            {3, 5, 7},
            {9, 1, 6}};

    /* should print TRUE */
    int check1 = isMagicSquare(square1, 3);
    if (check1 == TRUE) {
        printf("TRUE\n");
    } else {
        printf("FALSE\n");
    }

    int square2[MAX_N][MAX_N] = {
            {20,  6,  7, 17},
            { 9, 15, 14, 12},
            {13, 11, 10, 16},
            { 8, 18, 19, 5}	};
    
    /* should print FALSE */
    int check2 = isMagicSquare(square2, 4);
    if (check2 == TRUE) {
        printf("TRUE\n");
    } else {
        printf("FALSE\n");
    }

    int square3[MAX_N][MAX_N] = {
            {17, 24,  1, 15,  8},
            {23,  5,  7, 16, 14},
            { 4,  6, 13, 22, 20},
            {10, 12, 19,  3, 21}, 
            {11, 18, 25,  9,  2}};

    /* should print FALSE */
    int check3 = isMagicSquare(square3, 5);
    if (check3 == TRUE) {
        printf("TRUE\n");
    } else {
        printf("FALSE\n");
    }

    return 0;
}
