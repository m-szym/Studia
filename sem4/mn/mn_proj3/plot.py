import pandas as pd
import matplotlib.pyplot as plt
import glob

plot_size = (20, 12)


def plot_height_profile(data_path, inter_path, skip=1, reverse_data=False):
    names = ['x', 'y'] if not reverse_data else ['y', 'x']

    data = pd.read_csv(data_path, names=names)
    inter = pd.read_csv(inter_path, names=names)

    plt.figure(figsize=plot_size)
    plt.plot(data['x'], data['y'])
    plt.plot(inter['x'], inter['y'])
    #plt.scatter(data['x'].iloc[::skip], data['y'].iloc[::skip], marker='o', c='r')
    pt = pd.read_csv("csv/interp/gc15p.csv", names=['x', 'y'])
    plt.scatter(pt['x'], pt['y'], marker='o', c='r')
    plt.ylim((-50, 700))
    #plt.ylim((-12000, -2000))
    s = 5
    if skip > 5:
        s = 1
    for i in range(0, len(pt['x']), s):
        plt.annotate(f"{pt['y'][i]:.3f}",
                     (pt['x'][i], pt['y'][i]),
                     textcoords="offset points",
                     xytext=(-10, -10))

    datapoints_label = "Datapoints" if skip == 1 else f"Datapoints (every {skip}-th)"
    plt.legend(["Original data", "Interpolation", datapoints_label])
    t = "Genoa-Rapallo - Lagrange interpolation"
    if skip != 1:
        t += f" (every {skip}-th datapoint)"
    plt.title(t, loc="center")
    plt.show()


def plot_height_profile_f(data, inter, skip=1, annotate=False, title="Spline interpolation", full=None):
    plt.figure(figsize=plot_size)
    if full is not None:
        plt.plot(full['x'], full['y'])
    plt.plot(inter['x'], inter['y'])
    plt.scatter(data['x'], data['y'], marker='o', c='r')


    if annotate:
        s = 5
        if skip > 5:
            s = 1
        for i in range(0, len(data['x']), s):
            plt.annotate(f"{data['y'][i]:.3f}",
                         (data['x'][i], data['y'][i]),
                         textcoords="offset points",
                         xytext=(-10, -10))

    datapoints_label = "Datapoints" if skip == 1 else f"Datapoints (ever {skip}-th)"
    legend = ["Interpolation", datapoints_label]
    if full is not None:
        legend.insert(0, "Original data")
    plt.legend(legend)
    plt.title(title, loc="center")
    plt.show()

plot_height_profile("csv/data/2018_paths/genoa_rapallo.csv",
                    "csv/interp/gc10.csv",
                    skip=5)
