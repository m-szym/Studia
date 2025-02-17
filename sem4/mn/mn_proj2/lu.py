from time import time
from linalg import FlatMatrix, eye, forward_substitution, backward_substitution


def lu(A: FlatMatrix) -> tuple[FlatMatrix, FlatMatrix]:
    """Perform LU decomposition of a matrix A into L and U matrices"""
    m = A.rows()
    U = A.copy()
    L = eye(m)

    for i in range(2, m+1):
        for j in range(1, i):
            L[i-1][j-1] = U[i-1][j-1] / U[j-1][j-1]
            U.set_row(i-1, U.get_row(i-1) - (U.get_row(j-1) * L[i-1][j-1]))

    return L, U

def solve_lu(A: FlatMatrix, b: FlatMatrix) -> tuple[FlatMatrix, float, float]:
    """
    Solve a system of linear equations (Ar = b) using LU decomposition
    Parameters:
        A - matrix of coefficients
        b - column vector of constants
    Returns:
        r - solution vector
        err_num - final norm of the residuum
        time - time taken to solve the system
    """

    start = time()
    L, U = lu(A)
    y = forward_substitution(L, b)
    x = backward_substitution(U, y)
    end = time()
    err_num = (A @ x - b).euclidean_norm()

    return y, err_num, end - start


