# FYS3150 Project 1
*By Simon Halstensen, Carl Fredrik Nordbø Knutsen, Jan Harald Aasen & Didrik Sten Ingebrigtsen*


This project aims to solve the Poisson equation numerically, and analyse its error and the wall clock time spent on different algorithms.

## Usage
There is a `Makefile` included here, meaning it is relatively easy to compile and link the code. Running `make main` builds the main file, that can be used either to generate the exact solution to the equation (`main exact`), or some numerical approximation with h steps (`main <h>`). h has to be able to divide 100000. `make problem2` and `make problem7` uses the `main` executable to solve these problems, while `make latex` builds the pdf report. `make clear` cleans everything up.
