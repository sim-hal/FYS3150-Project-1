headers := $(wildcard include/*.hpp)
sources := $(wildcard src/*.hpp)

problem2: main
	mkdir -p computed
	mkdir -p plots
	./main exact
	python3 src/read_file_and_plot.py exact

problem7: main problem2
	mkdir -p computed
	mkdir -p plots
	./main 10
	./main 100
	./main 1000
	./main 10000
	./main 100000
	python3 src/error_plotting.py 10 100 1000 10000 100000
	python3 src/read_file_and_plot.py exact 10 100 100000

main: main.cpp $(headers) $(sources)
	g++ main.cpp src/exact_solution.cpp src/tools.cpp src/matrix_solver.cpp -I include -o main.exe

latex: problem2 problem7
	pdflatex latex/project_1.tex -output-dir=latex
	rm -f project_1.log
	rm -f project_1.aux
	rm -f texput.log

all: problem2 problem7 latex

clear:
	rm -f main
	rm -f -rf computed
	rm -f -rf plots
