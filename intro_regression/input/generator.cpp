#include <iostream>
#include <random>
#include <string>

/* Generates linear regression data */
int main(int argc, char* argv[])
{
    if (argc < 5) {
        std::cout << "Usage: " << std::endl << "\t" << argv[0] << " <npoints> <m> <b> <gaussian_std> [<xmin> <xmax>]" << std::endl;
        return -1;
    }

    int npoints = std::stoi(argv[1]);
    double m = std::stod(argv[2], NULL);
    double b = std::stod(argv[3], NULL);
    double gaussian_std = std::stod(argv[4], NULL);
    double xmin = 0;
    double xmax = 1;

    /* custom min/max x values */
    if (argc >= 7) {
        xmin  = std::stod(argv[5], NULL);
        xmax  = std::stod(argv[6], NULL);
    }

    /* generate data */
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_real_distribution<double> x_dist(xmin, xmax);
    std::normal_distribution<double> err_dist(0, gaussian_std);

    for (int i=0; i<npoints; ++i) {
        double x = x_dist(generator);
        double err = err_dist(generator);
        double y = m*x + b + err;

        std::cout << x << " " << y << std::endl;
    }

    return 0;
}