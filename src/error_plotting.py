"""Plotting of error, as specified in exercise 8.
"""

import numpy as np
import matplotlib.pyplot as plt
from typing import Tuple, Dict, List

from read_file_and_plot import read_function_vals

def compute_absolute_error(u: np.ndarray, v: np.ndarray):
    """Computes the base 10 logarithm of the absolute error between u and v.

    Args:
        u: The exact values, computed analytically.
        v: The estimated values, computed numerically.
    """
    return np.log10(np.abs(u - v))

def compute_relative_error(u: np.ndarray, v: np.ndarray):
    """Computes the base 10 logarithm of the relative error between u and v.

    Args:
        u: The exact values, computed analytically.
        v: The estimated values, computed numerically.
    """
    return np.where(u > 0, np.log10(np.abs((u - v)/u)), 0)

def plot_all_errors(n_list: List[int] = [10, 100, 1000, 10000],
                    title: str = "Errors")\
                    -> Tuple[Dict[int, float], Dict[int, float]]:
    """Make a figure, plotting all absolute and relative errors.

    Args:
        n_list: Which n-values to plot. For each of them, a file 
                `computed/<n>.csv` must exist. In the computed-folder, there 
                must also be a `exact_evaluated.csv`.
        title: The title of the plot. Used as plt.title, but also as a filename.

    Return:
        Two dicts, one for maximum absolute errors for each n, and one for max
        relative errors for each n.
    """

    nrows = 2
    ncols = len(n_list)

    max_abs_errors = {}
    max_rel_errors = {}

    fig, axs = plt.subplots(nrows, ncols, sharex="col", sharey="row",
                            figsize=(2*ncols, 2*nrows))

    fig.suptitle(title)

    x, u = read_function_vals(f"computed/exact_evaluated.csv")

    for n, abs_ax, rel_ax in zip(n_list, axs[0], axs[1]):
        _, v = read_function_vals(f"computed/{n}.csv")
        step_size = len(x)//len(v)

        abs_err = compute_absolute_error(u[::step_size], v)
        rel_err = compute_relative_error(u[::step_size], v)

        max_abs_errors[n] = np.max(abs_err)
        max_rel_errors[n] = np.max(rel_err)

        abs_ax.set_title(f"n = {n}")
        abs_ax.plot(x[::step_size], abs_err)
        rel_ax.set_xlabel("x")
        rel_ax.plot(x[::step_size], rel_err)

    axs[0, 0].set_ylabel("Absolute (log) error")
    axs[1, 0].set_ylabel("Relative (log) error")

    plt.savefig("plots/" + title.replace(" ", "_").lower() + ".pdf")

    return max_abs_errors, max_rel_errors

def main():
    if len(sys.argv) == 1:
        raise ValueError("n-values must be provided as system arguments.")
    
    n_list = [int(n) for n in sys.argv[1:]]
    max_abs_errs, max_rel_errs = plot_all_errors(n_list=n_list)

    print("Maximum errors for each n:")
    print("    | ".join([f"{int(n):8d}" for n in n_list]))
    print(" | ".join([f"{err:11.4g}" for err in max_abs_errs.values()]))
    print(" | ".join([f"{err:11.4g}" for err in max_rel_errs.values()]))

if __name__ == "__main__":
    import sys

    main()
