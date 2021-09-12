#include <fstream>
#include <iostream>
#include <string>

#include "tools.hpp"

void write_to_file(double *x, double *u, std::string filename, const int N) {
    std::ofstream outputFile(filename);

    for (int i = 0; i < N; i++){
        outputFile << x[i] << ',' << u[i]  << std::endl;
    }

    outputFile.close();
}
