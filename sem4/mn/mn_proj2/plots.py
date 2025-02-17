import matplotlib.pyplot as plt


def plot_errors(errors: list[list[float]]):
    for e in errors:
        plt.plot(e)

    plt.yscale("log")

    plt.title("Norm of residuum over time")
    plt.ylabel("Norm of residuum (log scale)")
    plt.xlabel("Iteration")
    plt.legend(["Jacobi", "Gauss-Seidel"])

    plt.show()


def plot_execution_times(sizes: list[int], times: list[list[float]]):
    for t in times:
        plt.plot(sizes, t)

    plt.title("Execution time for different sizes of matrix")
    plt.xlabel("Matrix size")
    plt.ylabel("Execution time")
    plt.legend(["Jacobi", "Gauss-Seidel", "LU"])

    plt.show()
