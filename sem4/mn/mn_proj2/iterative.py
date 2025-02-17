from time import time
from linalg import FlatMatrix, column, diagonal, forward_substitution


def solve_jacobi(A: FlatMatrix, b: FlatMatrix, iterations=1000, low_bound=1e-6, loud=False)  -> tuple[FlatMatrix, float, list[float], float]:
    """
    Solve a system of linear equations (Ar = b) using Jacobi method
    Parameters:
        A - matrix of coefficients
        b - column vector of constants
        iterations - maximum number of iterations
        low_bound - stop when the norm of the residuum is below this value
        loud - print progress of the method
    Returns:
        r - solution vector
        err_num - final norm of the residuum
        errors - list with norms of the residuum after each iteration
        time - time taken to solve the system
    """

    start = time()
    r = column(b.rows(), init=1)
    d = diagonal(A)
    lu = A - d
    di = d.diag_invert()
    errors = []
    err_num = (A @ r - b).euclidean_norm()

    for i in range(iterations):
        if err_num < low_bound:
            break

        r = -di @ (lu @ r) + di @ b
        err_num = (A @ r - b).euclidean_norm()
        errors.append(err_num)

        if loud:
            print(f"{i} iter of Jacobi, err: {err_num}")

    end = time()
    return r, err_num, errors, end - start


def solve_gauss_seidel(A: FlatMatrix, b: FlatMatrix, iterations=1000, low_bound=1e-6, loud=False) -> tuple[FlatMatrix, float, list[float], float]:
    """
    Solve a system of linear equations (Ar = b) using Gauss-Seidel method
    Parameters:
        A - matrix of coefficients
        b - column vector of constants
        iterations - maximum number of iterations
        low_bound - stop when the norm of the residuum is below this value
        loud - print progress of the method
    Returns:
        r - solution vector
        err_num - final norm of the residuum
        errors - list with norms of the residuum after each iteration
        time - time taken to solve the system
    """

    start = time()
    r = column(b.rows(), init=1)
    u = A.triu(1)
    ld = A.tril(0)
    err_num = (A @ r - b).euclidean_norm()
    errors = []

    for i in range(iterations):
        if err_num < low_bound:
            break

        r = forward_substitution(-ld, (u @ r)) + forward_substitution(ld, b)
        err_num = (A @ r - b).euclidean_norm()
        errors.append(err_num)

        if loud:
            print(f"{i} iter of Gauss-Seidel, err: {err_num}")

    end = time()
    return r, err_num, errors, end - start


