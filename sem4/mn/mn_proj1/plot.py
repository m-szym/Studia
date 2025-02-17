import matplotlib.pyplot as plt

start_idx = 35
# As MACD can only be calculated onwards from 35 datapoint all plots only show data in slice of [35:]
# otherwise plots would either be inconsistent or show false values (when indicator could not yet be calculated)
# The 35 datapoint stagger is due to:
# 1. EMA12 needing 12 datapoints for it's first value
# 2. EMA26 needing 26 datapoints for it's first value
#    Due to the above MACD line needs 26 datapoints for it's first value
# 3. Signal, being EMA9 of MACD line, needing 9 datapoints of MACD effectively staggering by 35 datapoints f

plot_size = (20, 12)
dates_step = 10


def plot_prices(prices, ema12=None, ema26=None, dates=None):
    plt.figure(figsize=plot_size)

    plt.plot(prices[start_idx:])

    if ema12 is not None:
        plt.plot(ema12[start_idx:])

    if ema26 is not None:
        plt.plot(ema26[start_idx:])

    if dates is not None:
        plt.xticks([*range(0, prices.size - start_idx, dates_step)],
                   dates[start_idx:dates.size:dates_step],
                   rotation='vertical')

    plt.legend(["Closing price", "EMA12", "EMA26"])
    plt.show()


def plot_full(prices=None, ema12=None, ema26=None, macd=None, signal=None, dates=None, buy=None, sell=None,
              buysell=None, marker=None, zero=False):
    plt.figure(figsize=plot_size)
    legend = []

    if prices is not None:
        plt.plot(prices[start_idx:], marker=marker)
        legend.append("Closing price")

    if ema12 is not None:
        plt.plot(ema12[start_idx:], marker=marker)
        legend.append("EMA12")

    if ema26 is not None:
        plt.plot(ema26[start_idx:], marker=marker)
        legend.append("EMA26")

    if dates is not None:
        plt.xticks([*range(0, dates.size - start_idx, dates_step)],
                   dates[start_idx:dates.size:dates_step],
                   rotation='vertical')

    if macd is not None:
        plt.plot(macd[start_idx:], marker=marker)
        legend.append("MACD")

    if signal is not None:
        plt.plot(signal[start_idx:], marker=marker)
        legend.append("Signal")

    if buy is not None:
        if buysell is None or buysell == "flags":
            plt.vlines([v-start_idx for v in buy if v > start_idx],
                       min(macd[start_idx:]),
                       [signal[start_idx:][v - start_idx] for v in buy if v > start_idx],
                       color="g")
        elif buysell == "points":
            plt.scatter(buy,
                        [signal[v] for v in buy],
                        c="green",
                        marker="o")
        legend.append("Buy signal")

    if sell is not None:
        if buysell is None or buysell == "flags":
            plt.vlines([v-start_idx for v in sell if v > start_idx],
                       [signal[start_idx:][v - start_idx] for v in sell if v > start_idx],
                       max(macd[start_idx:]),
                       color="r")
        elif buysell == "points":
            plt.scatter(sell,
                        [signal[v] for v in sell],
                        c="red",
                        marker="o")
        legend.append("Sell signal")

    if zero:
        plt.hlines(y=0, xmin=0, xmax=macd.size, color="grey", linestyles="--")

    plt.legend(legend)
    # plt.vlines([i for i in range(1, macd.size) if np.sign(macd[i]) != np.sign(macd[i-1])], 0, max(prices), colors="b")

    plt.show()


def plot_macd_prices(prices, macd, signal, ema12=None, ema26=None, buy=None, sell=None, dates=None, histogram=False):
    plt.figure(figsize=plot_size)
    legend = ["Closing price", "MACD (not to scale)", "Signal (not to scale)"]
    v_move = 0.9 * min(prices[start_idx:])
    v_macd = macd + v_move
    v_signal = signal + v_move
    plt.plot(prices[start_idx:])
    plt.plot(v_macd[start_idx:])
    plt.plot(v_signal[start_idx:])

    if ema12 is not None:
        plt.plot(ema12[start_idx:])
        legend.append("EMA12")

    if ema26 is not None:
        plt.plot(ema26[start_idx:])
        legend.append("EMA26")

    if dates is not None:
        plt.xticks([*range(0, prices.size - start_idx, dates_step)],
                   dates[start_idx:dates.size:dates_step],
                   rotation='vertical')

    if buy is not None:
        plt.vlines([v-start_idx for v in buy if v > start_idx],
                   min((v_macd[start_idx:])),
                   [prices[start_idx:][v - start_idx] for v in buy if v > start_idx],
                   color="g")
        legend.append("Buy signal")

    if sell is not None:
        plt.vlines([v-start_idx for v in sell if v > start_idx],
                   [v_signal[start_idx:][v - start_idx] for v in sell if v > start_idx],
                   [prices[start_idx:][v - start_idx] for v in sell if v > start_idx],
                   color="r")
        legend.append("Sell signal")

    if histogram:
        diff = (macd - signal)[start_idx:]
        mult = 5
        plt.vlines(x=[i for i in range(diff.size) if diff[i] > 0],
                   ymin=v_move,
                   ymax=[v_move + (v * mult) for v in diff if v > 0],
                   color="g",
                   linewidth=2)

        plt.vlines(x=[i for i in range(diff.size) if diff[i] < 0],
                   ymax=v_move,
                   ymin=[v_move + (v * mult) for v in diff if v < 0],
                   color="r",
                   linewidth=2)

    plt.legend(legend)
    plt.show()


def plot_macd_histogram(macd, signal):
    plt.figure(figsize=plot_size)
    plt.plot(macd[start_idx:])
    plt.plot(signal[start_idx:])
    diff = (macd - signal)[start_idx:]

    plt.vlines(x=[i for i in range(diff.size) if diff[i] > 0],
               ymin=0,
               ymax=[v for v in diff if v > 0],
               color="g",
               linewidth=2)

    plt.vlines(x=[i for i in range(diff.size) if diff[i] < 0],
               ymax=0,
               ymin=[v for v in diff if v < 0],
               color="r",
               linewidth=2)

    plt.hlines(y=0, xmin=0, xmax=macd.size, color="grey", linestyles="--")
    plt.legend(["MACD", "Signal", "MACD > Signal", "Signal > MACD"])
    plt.show()