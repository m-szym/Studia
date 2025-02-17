import numpy as np


def trade_on_signals_with_confirmation(prices, buy, sell, budget=1000.0):
    cash = budget
    stocks = 0.0
    confirm_buying = False
    confirm_selling = False

    for i in range(prices.size):
        if i in buy and cash > 0.0:
            if confirm_buying:
                stocks = cash / prices[i]
                cash = 0.0
            else:
                confirm_buying = True
            confirm_selling = False
        elif i in sell and stocks > 0.0:
            if confirm_selling:
                cash = stocks * prices[i]
                stocks = 0.0
            else:
                confirm_selling = True
            confirm_buying = False

    if stocks > 0:
        cash = stocks * prices[prices.size - 1]

    return cash - budget


def trade_on_signals(prices, buy, sell, budget=1000.0):
    cash = budget
    stocks = 0.0

    for i in range(prices.size):
        if i in buy and cash > 0.0:
            stocks = cash / prices[i]
            cash = 0.0
        elif i in sell and stocks > 0.0:
            cash = stocks * prices[i]
            stocks = 0.0

    if stocks > 0.0:
        cash = stocks * prices[prices.size - 1]

    return cash - budget


def trade_on_signals_with_stagger(prices, buy, sell, budget=1000.0, stagger=6):
    cash = budget
    stocks = 0.0
    buy_stagger = 0
    sell_stagger = 0

    for i in range(prices.size):
        if i in buy and cash > 0.0:
            buy_stagger = stagger
            sell_stagger = -1
        elif i in sell and stocks > 0.0:
            sell_stagger = stagger
            buy_stagger = -1

        if buy_stagger > 0:
            buy_stagger -= 1
            if buy_stagger == 0:
                stocks = cash / prices[i]
                cash = 0.0
        elif sell_stagger > 0:
            sell_stagger -= 1
            if sell_stagger == 0:
                cash = stocks * prices[i]
                stocks = 0.0

    if stocks > 0.0:
        cash = stocks * prices[prices.size - 1]

    return cash - budget


def trade_on_signals_with_tolerance(prices, buy, sell, budget=1000.0, tolerance=2):
    cash = budget
    stocks = 0.0
    ignore_buy_signals = tolerance
    ignore_sell_signals = tolerance

    for i in range(prices.size):
        if i in buy and cash > 0.0:
            if ignore_buy_signals > 0:
                ignore_buy_signals -= 1
            else:
                stocks = cash / prices[i]
                cash = 0.0
                ignore_sell_signals = tolerance

        elif i in sell and stocks > 0.0:
            if ignore_sell_signals > 0:
                ignore_sell_signals -= 1
            else:
                cash = stocks * prices[i]
                stocks = 0.0
                ignore_buy_signals = tolerance

    if stocks > 0.0:
        cash = stocks * prices[prices.size - 1]

    return cash - budget