def lagrange_base_function(x, x_values, k):
    result = 1.0
    for i in range(len(x_values)):
        if i != k:
            result *= (x - x_values[i]) / (x_values[k] - x_values[i])
    return result


def lagrange_point(x, y, x0):
    result = 0.0
    for i in range(len(x)):
        result += y[i] * lagrange_base_function(x0, x, i)
    return result


def lagrange_interpolate(x, y, mult=100):
    res = []
    x_dense = []

    for i in range(len(x)-1):
        k = abs(x[i+1] - [x[i]]) / mult
        for j in range(mult):
            t = x[i] + j * k
            x_dense.append(t)
            res.append(lagrange_point(x, y, t))

    return x_dense, res
