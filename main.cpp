#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


void evaluateToFile(double **x, double **u){
    const int N = 1000;
    const double closeToOne = 1. - exp(-10);
    *x = new double[N];
    *u = new double[N];
    ofstream outputFile("exact_evaluated.csv");
    const double increment = 1. / N;
    for (int i = 0; i < N; i++){
        (*x)[i] = increment * (double)i;
        (*u)[i] = 1 - closeToOne * (*x)[i] - exp(-10 * (*x)[i]);
        cout << (*x)[i] << ',' << (*u)[i] << endl;
        outputFile << (*x)[i] << ',' << (*u)[i]  << endl;
    }
    outputFile.close();
}


int main() {
    cout << "Hello, World 2!" << endl;
    double *x, *u;
    evaluateToFile(&x, &u);

    delete [] x;
    delete [] u;
    return 0;
}
