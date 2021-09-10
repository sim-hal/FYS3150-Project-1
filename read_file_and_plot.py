import numpy as np
import matplotlib.pyplot as plt

def read_function_vals(filename):
    data = np.loadtxt(filename, dtype="float", delimiter=",")
    x_array, u_array = data[:, 0], data[:, 1]
    return x_array, u_array

def plot_function_values(x, u, filename="exact_function_u(x).pdf"):
    plt.plot(x, u, label="u")
    plt.xlabel("x")
    plt.ylabel("u(x)")
    plt.title("Plot of exact function u(x)")
    plt.savefig(filename)

    
if __name__ == "__main__":
    x_array, u_array = read_function_vals("exact_evaluated.csv")
    plot_function_values(x_array, u_array)

    x, v = read_function_vals("general_approximation_10000.txt")
    plot_function_values(x, v, filename="approx_plot_10000.pdf")
