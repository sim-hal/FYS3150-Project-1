#include <fstream>
#include <string>
#include <iostream>
#include <cmath>

void general_tridiagonal(double **v, double *a, double *b, double *c, double *g, int N) {
    *v = new double[N];
    double *b_tilde = new double[N];
    double *g_tilde = new double[N];

    b_tilde[0] = b[0];
    g_tilde[0] = g[0];

    for (int i = 1; i < N; i++) {
        b_tilde[i] = b[i] - (a[i] * c[i - 1]) / b_tilde[i - 1];
        g_tilde[i] = g[i] - (a[i] * g_tilde[i - 1]) / b_tilde[i - 1];
    }

    (*v)[N] = g_tilde[N - 1] / b_tilde[N - 1];
    
    std::cout << (*v)[N] << std::endl;

    for (int i = N - 1; i >= 0; i--) {
        (*v)[i] = (g_tilde[i] - c[i] * (*v)[i + 1]) / b_tilde[i];
        std::cout << (*v)[i] << std::endl;
    }
}

int main() {

    double *v, *g;
    int N = 10000;

    double *a = new double[N-1];
    double *b = new double[N];
    double *c = new double[N-1];

    g = new double[N];
    double *x = new double[N];

    double increment = 1./N;

    for (int i = 0; i < N; i++) {
        if (i < N - 1) {
            a[i] = -1.;
            c[i] = -1.;
        }
        b[i] = 2.;
        x[i] = increment * i;
        g[i] = 100 * exp(-10 * x[i]);
    }

    general_tridiagonal(&v, a, b, c, g, N);

    std::ofstream output_file("general_approximation_" + std::to_string(N) + ".txt");
    
    output_file << "x, v"  << std::endl;

    for (int i = 0; i < N; i++) {
        output_file << x[i] << ',' << v[i]  << std::endl;
    }

    output_file.close();

    return 0;
}
