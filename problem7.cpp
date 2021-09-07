#include <fstream>
#include <string>
#include "general_tridiagonal.hpp"

int main() {

    double *v, *g;
    int N = 10000;

    a = new double[N-1];
    b = new double[N];
    c = new double[N-1];

    g = new double[N];
    x = new double[N];

    for (int i = 0; i < N; i++) {
        if (i < N - 1) {
            a[i] = -1.;
            c[i] = -1.;
        }
        b[i] = 2.;
        x[i] = (N - 1)/i
        g[i] = 100 * exp(-10 * x[i])
    }

    general_tridiagonal(**v, *a, *b, *c, *g, N)

    ofstream output_file("general_approximation_" + std::to_string(N) + ".txt");
    
    output_file << "x, v"  << std::endl;

    for (int i = 0; i < N; i++) {
        output_file << x[i] << ',' << v[i]  << std::endl;
    }

    output_file.close()

    return 0;
}
