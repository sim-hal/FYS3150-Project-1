#ifndef GENERAL_TRIDIAGONAL
#define GENERAL_TRIDIAGONAL

void general_tridiagonal(double **v, double *a, double *b, double *c, double *g, int N) {
    *v = new double[N];
    b_tilde = new double[N];
    g_tilde = new double[N];

    b_tilde[0] = b[0];
    g_tilde[0] = g[0];

    for (int i = 1; i < N; i++) {
        b_tilde[i] = b[i] - (a[i] * c[i - 1])/b_tilde[i - 1];
        g_tilde[i] = g[i] - (a[i] * g_tilde[i - 1])/b_tilde[i - 1];
    }

    v[N] = g_tilde[N]/b_tilde[N]

    for (int i = N - 1; i <= 0; i--) {
        v[i] = (g_tilde[i] - c[i] * v[i + 1])/b_tilde[i];
    }
}

#endif
