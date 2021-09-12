#include <cmath>
#include "matrix_solver.hpp"

void general_tridiagonal(double **v, double *a, double *b, double *c, double *g, int N) {
    *v = new double[N];
    double *b_tilde = new double[N];
    double *g_tilde = new double[N];

    b_tilde[0] = b[0];
    g_tilde[0] = g[0];

    for (int i = 1; i < N; i++) {
        double w = a[i - 1] / b_tilde[i - 1];
        b_tilde[i] = b[i] - w * c[i - 1];
        g_tilde[i] = g[i] - w * g_tilde[i - 1];
    }

    (*v)[N - 1] = g_tilde[N - 1] / b_tilde[N - 1];
    for (int i = N - 2; i >= 0; i--) {
        (*v)[i] = (g_tilde[i] - c[i - 1] * (*v)[i + 1]) / b_tilde[i];
    }
}

void special_tridiagonal(double **v, double *g, int N) {
    *v = new double[N];
    double *b_tilde_inv = new double[N];
    double *g_tilde = new double[N];

    b_tilde_inv[0] = 0.5;
    g_tilde[0] = g[0];

    for (int i = 1; i < N; i++) {
        b_tilde_inv[i] = double(i+2)/double(i+3);
        g_tilde[i] = g[i] + b_tilde_inv[i - 1] * g_tilde[i - 1];
    }

    (*v)[N - 1] = g_tilde[N - 1] * b_tilde_inv[N - 1];
    for (int i = N - 2; i >= 0; i--)
        (*v)[i] = (g_tilde[i] + (*v)[i + 1]) * b_tilde_inv[i];
}
