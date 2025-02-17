import numpy as np


def sma(batch):
    return np.mean(batch)


def whole_sma(data, size):
    smas = np.zeros((data.size,))
    for i in range(size, data.size):
        smas[i] = sma(data[i-size:i])

    return smas


def ema(value, prev_ema, size, smoothing=2):
    weight = smoothing / (size + 1)
    return value * weight + prev_ema * (1 - weight)


def whole_ema(data, size, smoothing=2):
    #emas = np.zeros((data.size - size))
    emas = np.zeros((data.size,))
    current_ema = sma(data[:size-1])
    for i in range(size, data.size):
        #emas[i - size] = current_ema
        emas[i] = current_ema
        current_ema = ema(data[i], current_ema, size, smoothing)

    return emas


def macd(data):
    ema12 = whole_ema(data, 12)
    ema26 = whole_ema(data, 26)

    macd = ema12 - ema26
    for i in range(26):
        macd[i] = 0.0

    signal = whole_ema(macd, 9)

    return macd, signal


def intersections(line1, line2):
    l1_over_l2 = []
    l1_under_l2 = []
    for i in range(1, line2.size - 1):
        if line1[i] - line2[i] > 0 > line1[i - 1] - line2[i - 1]:
            l1_over_l2.append(i)
        elif line1[i] - line2[i] < 0 < line1[i - 1] - line2[i - 1]:
            l1_under_l2.append(i)

    return l1_over_l2, l1_under_l2


def macd_buy_sell(macd, signal):
    return intersections(macd, signal)
