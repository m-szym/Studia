from time import time
from linalg3 import FlatMatrix, eye, forward_substitution, backward_substitution


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


def lu_pivot(A):
    """Perform LU decomposition with partial pivoting of a matrix A into L and U matrices"""
    m = A.rows()
    n = A.cols()
    U = A.copy()
    L = eye(n)
    P = eye(n)

    for k in range(m-1):
        # for i in range(k, m):
        #     if abs(U[i][k]) > M:
        #         M = abs(U[i][k])
        #         Mind = i

        # Mind += k
        t = [abs(U[i][k]) for i in range(k, m)]
        p = max(t)
        Mind = t.index(p) + k

        if Mind != k:
            for i in range(k, m):
                U[k][i], U[Mind][i] = U[Mind][i], U[k][i]

            for i in range(k):
                L[k][i], L[Mind][i] = L[Mind][i], L[k][i]

            for i in range(n):
                P[k][i], P[Mind][i] = P[Mind][i], P[k][i]

        for i in range(k+1, m):
            L[i][k] = U[i][k] / U[k][k]
            for j in range(k, m):
                U[i][j] -= L[i][k] * U[k][j]

    return L, U, P

def solve_lu_pivot(A, b):
    """
    Solve a system of linear equations (Ar = b) using LU decomposition with partial pivoting
    Parameters:
        A - matrix of coefficients
        b - column vector of constants
    Returns:
        r - solution vector
        err_num - final norm of the residuum
        time - time taken to solve the system
    """

    L, U, P = lu_pivot(A)
    y = forward_substitution(L, P @ b)
    x = backward_substitution(U, y)

    return x