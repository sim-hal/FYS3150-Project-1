"""Plotting of error, as specified in exercise 8.
"""

import numpy as np
import matplotlib.pyplot as plt

from read_file_and_plot import read_function_vals

def plot_absolute_error(u: np.ndarray, v: np.ndarray, x: np.ndarray, 
                        ax: plt.axes = None):
    """Plots the base 10 logarithm of the absolute error between u and v.

    Args:
        u: The exact values, computed analytically.
        v: The estimated values, computed numerically.
        x: The array describing what to plot on the x axis. 
        ax: The axis object to plot in. None by default, in which case a new one
            is created.
    """
    if ax is None:
        ax = plt.gca()

    error = np.log10(np.abs(u - v))

    ax.plot(x, error)

def plot_relative_error(u: np.ndarray, v: np.ndarray, x: np.ndarray, 
                        ax: plt.axes = None):
    """Plots the base 10 logarithm of the relative error between u and v.

    Args:
        u: The exact values, computed analytically.
        v: The estimated values, computed numerically.
        x: The array describing what to plot on the x axis. 
        ax: The axis object to plot in. None by default, in which case a new one
            is created.
    """
    if ax is None:
        ax = plt.gca()

    error = np.log10(np.abs((u - v)/u))

    ax.plot(x, error)

def plot_all_errors(n_list: List[int] = [10, 100, 1000, 10000],
                    title: str = "Errors"):
    """Make a figure, plotting all absolute and relative errors.

    Args:
        n_list: Which n-values to plot. For each of them, a file 
                `computed/<n>.csv` must exist. In the computed-folder, there 
                must also be a `exact_evaluated.csv`.
        title: The title of the plot. Used as plt.title, but also as a filename.
    """

    nrows = 2
    ncols = len(n_list)

    fig, axs = plt.subplots(nrows, ncols, sharex="col", sharey="row",
                            figsize=(2*ncols, 2*nrows))

    plt.title(title)

    x, u = read_function_vals(f"computed/exact_evaluated.csv")

    for n, abs_ax, rel_ax in zip(n_list, axs[0], axs[1]):
        _, v = read_function_vals(f"computed/{n}.csv")
        step_size = len(x)//len(v)

        plot_absolute_error(u[step_size], v, x[step_size], abs_ax)
        plot_relative_error(u[step_size], v, x[step_size], rel_ax)

        abs_ax.set_title(f"n = {n}")
        rel_ax.set_xlabel("x")

    axs[0, 0].set_ylabel("Absolute (log) error")
    axs[1, 0].set_ylabel("Relative (log) error")

    plt.savefig("plots/" + title.replace(" ", "_").lower() + ".pdf")   

if __name__ == "__main__":
    import sys

    plot_all_errors(n_list=sys.argv[1:])
