import pandas as pd
import numpy as np

from inter import createMatrix, spline_interpolate
from lu import lu_pivot, solve_lu_pivot
from plot import *
from lagrange import lagrange_interpolate

data_path = "csv/data/2018_paths/"
interpolation_path = "csv/interp/"


def run_splines(filename, skip=1, save=False, annotate=True, name=None):
    data = pd.read_csv(data_path + filename, names=['x', 'y'])

    x = data['x'].iloc[::skip].reset_index(drop=True)
    y = data['y'].iloc[::skip].reset_index(drop=True)

    A, b = createMatrix(x, y)

    # solve with custom LU
    # X = solve_lu_pivot(A, b)

    # solve with numpy
    _A, _b = np.array(A.data), np.array(b.data)
    X = np.linalg.solve(_A, _b)

    x_dense, result = spline_interpolate(x, X)

    if save:
        with open(interpolation_path + "s" + str(skip) + "_" + filename, 'w') as f:
            for i in range(len(x_dense)):
                f.write(f"{x_dense[i]},{result[i].item()}")

    title = name + " spline interpolation"
    if skip != 1:
        title += f" (every {skip}-th datapoint used)"
    plot_height_profile_f({'x': x, 'y': y},
                          {'x': x_dense, 'y': result},
                          skip=skip, annotate=annotate,
                          title=title,
                          full=data)


def run_lagrange(filename, skip=1, save=False):
    data = pd.read_csv(data_path + filename, names=['x', 'y'])

    x = data['x'].iloc[::skip].reset_index(drop=True)
    y = data['y'].iloc[::skip].reset_index(drop=True)

    x_dense, result = lagrange_interpolate(x, y)

    if save:
        with open(interpolation_path + "s" + str(skip) + "_" + filename, 'w') as f:
            for i in range(len(x_dense)):
                f.write(f"{x_dense[i]},{result[i].item()}")

    plot_height_profile_f({'x': x, 'y': y}, {'x': x_dense, 'y': result}, skip=skip, annotate=True)


file = "genoa_rapallo.csv"

for s in [1, 2, 4, 10, 25, 50, 100]:
    run_splines(file, skip=s, name="Genoa-Rapallo")

for s in [1, 2, 4]:
    run_splines(file, skip=s, annotate=False, name="Genoa-Rapallo")
# run_lagrange("100.csv", skip=10)
