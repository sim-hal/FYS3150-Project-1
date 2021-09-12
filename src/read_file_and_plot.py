import numpy as np
import matplotlib.pyplot as plt
from typing import List

def read_function_vals(filename):
    data = np.loadtxt(filename, dtype="float", delimiter=",")
    x_array, u_array = data[:, 0], data[:, 1]
    return x_array, u_array

def main(files_to_plot: List[str]):
    for file in files_to_plot:
        x, u = read_function_vals(f"computed/{file}.csv")
        label = "Exact" if file == "exact_evaluated" else f"n={file}"
        plt.plot(x, u, label=label)
    plt.ylabel("u(x)")
    plt.xlabel("x")
    plt.legend()
    plt.savefig(f"plots/{'_'.join(files_to_plot)}.pdf")
    plt.cla()

if __name__ == "__main__":
    import sys

    main(sys.argv[1:])
