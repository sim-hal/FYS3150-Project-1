#include <fstream>
#include <iostream>
#include <string>

#include "../include/tools.hpp"

void write_to_file(double *x, double *u, std::string filename, const int N) {
    /**
     * Writes x and u to file as columns in the csv-format
    */
    std::ofstream outputFile(filename);

    outputFile << std::scientific;

    for (int i = 0; i < N; i++){
        outputFile << x[i] << ',' << u[i]  << std::endl;
    }

    outputFile.close();
}
