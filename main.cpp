#include <cmath>
#include <string>
#include <iostream>
#include <string.h>
#include <chrono>
#include <fstream>

#include "include/exact_solution.hpp"
#include "include/tools.hpp"
#include "include/matrix_solver.hpp"


int main(int argc, char *argv[]) {
    

    if (argc < 2) // if not enough arguments are provided
        return -1;
        
    if (strncmp(argv[1], "exact", 5) == 0) {
        const int N = 100000;
        double *x, *u;
        compute_exact_solution(&x, &u, N);

        std::string filename = "computed/exact.csv";
        write_to_file(x, u, filename, N);

        delete [] x;
        delete [] u;

        return 0;
    }

    if (strncmp(argv[1], "time", 4) == 0) {
        std::ofstream outputFile("computed/time.csv");
        outputFile << "N,t_general,t_special" << std::endl;
        outputFile << std::scientific;

        for (int i = 2; i < 7; i++){
            
            int N = pow(10, i);
            double total_time_general = 0;
            double total_time_special = 0;

            int ITERS = 100; // number of times to run each algorithm per value of N

            for (int j = 0; j < ITERS * 2; j++){
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

                auto t1 = std::chrono::high_resolution_clock::now();
                
                if (j < ITERS) {
                    general_tridiagonal(&v, a, b, c, g, N);
                }
                else {
                    special_tridiagonal(&v, g, N);
                }

                auto t2 = std::chrono::high_resolution_clock::now();
                double duration_seconds = std::chrono::duration<double>(t2 - t1).count();
                
                if (j < ITERS){
                    total_time_general += duration_seconds;
                }
                else {
                    total_time_special += duration_seconds;
                }

                // free memory

                delete [] v;
                delete [] g;
                delete [] a;
                delete [] b;
                delete [] c;
                delete [] x;

            }
            // write to file
            outputFile << N << "," << total_time_general / ITERS << "," << total_time_special / ITERS << std::endl;
        }
        outputFile.close();
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

        // initialize arrays
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

        write_to_file(x, v, "computed/" + std::to_string(N) + ".csv", N);

        // free memory

        delete [] v;
        delete [] g;
        delete [] a;
        delete [] b;
        delete [] c;
        delete [] x;

        return 0;
    }
}
