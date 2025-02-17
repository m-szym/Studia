from linalg import FlatMatrix, column, zeros
from math import sin


def get_matrix(n: int, a: (int | float), b: (int | float) , c: (int | float)) -> FlatMatrix:
    """
    Generate a tridiagonal matrix of size n x n
    with elements a on the main diagonal, 
    b on the first subdiagonal and superdiagonal,
    and c on the second subdiagonal and superdiagonal
    """
    m = zeros((n, n))
    for i in range(n):
        for j in range(n):
            if i == j:
                m[i][j] = a
            elif i == j - 1 or i == j + 1:
                m[i][j] = b
            elif i == j - 2 or i == j + 2:
                m[i][j] = c

    return m


def get_vector(n: int, f: (int | float)) -> FlatMatrix:
    """Return a column vector of size n with i-th element equal to sin(i * (f + 1))"""
    return column(n, [sin(i *(f + 1)) for i in range(n)])
