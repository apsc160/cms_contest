#include <stdio.h>

#define INPUT_FILE "data.txt"

/* computes the regression line of 2D data from a file   */
int main(void)
{
    FILE*  fin = NULL;    /* input file                  */
    double n = 0;         /* number of data point        */
    double x = 0;         /* values to read              */
    double y = 0;            
    double xbar = 0;      /* mean values                 */
    double ybar = 0;      
    double m = 0;         /* slope and intercept         */
    double b = 0;           
    double m_num = 0;     /* slope numerator/denominator */
    double m_denom = 0;    

    /* TODO: read data and compute mean values from file */

    /* TODO: read data and compute regression slope/intercept */

    /* TODO: print slope and intercept to stdout */

    return 0;
}
