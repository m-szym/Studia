from linalg3 import FlatMatrix, column, zeros


def createMatrix(x_vec, y_vec):
    n = len(x_vec) - 1
    h = float(abs(x_vec[1] - x_vec[0]))
    b = column(4*n, 0.0)
    # nadokreślony układ równań
    A = zeros((4*n, 4*n))

    for i in range(0, n):
        b[4*i][0] = y_vec[i]
        b[4*i+1][0] = y_vec[i+1]

    for j in range(1, n-1):
        # lewy punkt
        A[4*j][4*j] = 1.0

        # prawy punkt
        A[4*j+1][4*j] = 1.0
        A[4*j+1][4*j+1] = h
        A[4*j+1][4*j+2] = h ** 2
        A[4*j+1][4*j+3] = h ** 3

        # prawa I pochodna
        A[4*j+2][4*j+1] = 1.0
        A[4*j+2][4*j+2] = 2 * h
        A[4*j+2][4*j+3] = 3 * (h ** 2)
        A[4*j+2][4*j+5] = -1.0

        # prawa II pochodna
        A[4*j+3][4*j+2] = 2.0
        A[4*j+3][4*j+3] = 6 * h
        A[4*j+3][4*j+6] = -2.0


    # pierwszy przedział
    A[0][0] = 1.0
    
    A[1][0] = 1.0
    A[1][1] = h
    A[1][2] = h ** 2
    A[1][3] = h ** 3
    # prawe pochodne I przedziału
    A[2][1] = 1.0
    A[2][2] = 2 * h
    A[2][3] = 3 * (h ** 2)
    A[2][5] = -1.0

    A[3][2] = 2.0
    A[3][3] = 6 * h
    A[3][6] = -2.0
    # lewa 2 pochodne I przedziału
    A[4*n-1][2] = 1.0

    # A[4*n+1][2] = 2
    # A[4*n+1][3] = 6 * h

    # ostatni przedział
    A[4*n-4][4*n-4] = 1.0

    A[4*n-3][4*n-4] = 1.0
    A[4*n-3][4*n-3] = h
    A[4*n-3][4*n-2] = h ** 2
    A[4*n-3][4*n-1] = h ** 3

    # prawa 2 pochodna ostatniego przedziału
    A[4*n-2][4*n-2] = 2.0
    A[4*n-2][4*n-1] = 6 * h

    return A, b


def spline_interpolate(x, poly):
    res = []
    x_dense = []
    n = len(x) - 1
    mult = 100

    for i in range(n):
        k = abs(x[i+1] - x[i]) / mult
        for j in range(mult):
            t = x[i] + j * k
            x_dense.append(t)
            res.append(poly[4*i] + poly[4*i+1] * (t - x[i]) + poly[4*i+2] * (t - x[i]) ** 2 + poly[4*i+3] * (t - x[i]) ** 3)

    return x_dense, res


