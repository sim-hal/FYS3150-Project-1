#include <cmath>
#include <string>
#include <iostream>

#include "exact_solution.hpp"
#include "tools.hpp"
#include "matrix_solver.hpp"

int main(int argc, char *argv[]) {
    

    if (argc < 2)
        return -1;
        
    if (strncmp(argv[1], "exact", 5) == 0) {
        const int N = 100000;
        double *x, *u;
        compute_exact_solution(&x, &u, N);

        std::string filename = "computed/exact_evaluated.csv";
        write_to_file(x, u, filename, N);

        delete [] x;
        delete [] u;

        return 0;
    }

    else {
        const int N = atoi(argv[1]);
        double *v;
        double *g = new double[N];
        double *a = new double[N - 1];
        double *b = new double[N];
        double *c = new double[N - 1];
        double *x = new double[N];

        const double increment = 1./N;

        for (int i = 0; i < N; i++) {
            if (i < N - 1) {
                a[i] = -1.;
                c[i] = -1.;
            }
            b[i] = 2.;
            x[i] = increment * i;
            g[i] = increment * increment * 100 * exp(-10 * x[i]);
        }

        special_tridiagonal(&v, g, N);
        //special_tridiagonal(&v, a, b, c, g, N);
        //general_tridiagonal(&v, a, b, c, g, N);

        write_to_file(x, v, "computed/" + std::to_string(N) + ".csv", N);

        delete [] v;
        delete [] g;
        delete [] a;
        delete [] b;
        delete [] c;
        delete [] x;

        return 0;
    }
}
