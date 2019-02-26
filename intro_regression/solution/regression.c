#include <stdio.h>

#define INPUT_FILE "data.txt"

/* computes the regression line of 2D data from a file   */
int regression(void)
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
    fin = fopen(INPUT_FILE, "r");
    if (fin != NULL) {
        while (fscanf(fin, "%lf %lf", &x, &y) == 2) {
            xbar += x;
            ybar += y;
            ++n;
        }
        xbar /= n;
        ybar /= n;

        fclose(fin);
    }

    /* TODO: read data and compute regression slope/intercept */
    fin = fopen(INPUT_FILE, "r");
    if (fin != NULL) {
        while (fscanf(fin, "%lf %lf", &x, &y) == 2) {
            m_num += (x-xbar)*(y-ybar);
            m_denom += (x-xbar)*(x-xbar);
            ++n;
        }
        fclose(fin);
    }

    /* TODO: print slope and intercept to stdout */
    m = m_num/m_denom;
    b = ybar - m*xbar;

    printf("%.2lf %.2lf\n", m, b);

    return 0;
}