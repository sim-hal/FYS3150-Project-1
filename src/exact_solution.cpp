#include <cmath>
#include "../include/exact_solution.hpp"

void compute_exact_solution(double **x, double **u, const int N){
    /**
     * Computes the exact solution as given in the problem set
    */
    const double closeToOne = 1. - exp(-10); // Just to avoid repeated computation of exponential expression
    *x = new double[N];
    *u = new double[N];
    const double increment = 1. / N;
    for (int i = 0; i < N; i++){
        (*x)[i] = increment * (double)i;
        (*u)[i] = 1 - closeToOne * (*x)[i] - exp(-10 * (*x)[i]);
    }
}
