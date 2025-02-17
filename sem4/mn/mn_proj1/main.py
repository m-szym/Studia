from data import get_data, prepare_data
from macd import macd, macd_buy_sell, whole_ema
from plot import *
from trade import *


def test_trades(budget=1000.0):
    dataset = get_data()
    za = dataset['Zamkniecie'].to_numpy()

    wyn1 = []
    wyn2 = []
    wyn3 = []
    wyn4 = []

    batch_size = 1000
    for i in range(1000, za.size - 5*365, batch_size):
        batch = za[i:i + batch_size]
        m, s = macd(batch)
        by, sl = macd_buy_sell(m, s)

    #     wyn1.append(trade_on_signals_with_confirmation(batch, by, sl, budget=budget))
    #     wyn2.append(trade_on_signals(batch, by, sl, budget=budget))
    #     wyn3.append(trade_on_signals_with_stagger(batch, by, sl, stagger=6, budget=budget))
    #     wyn4.append(trade_on_signals_with_tolerance(batch, by, sl, tolerance=2, budget=budget))
    #
    # # plt.plot(wyn1)
    # # plt.plot(wyn2)
    # # plt.plot(wyn3)
    # # plt.plot(wyn4)
    # # plt.legend(["Confirmed signals", "Signals", "Staggered", "Tolerant"])
    # # plt.show()

    period = "VI 2016 - IV 2020"
    # period = "VI 2016 - VI 2017"
    # period = "IV 1994 - III 2024"
    # period = "1999 - 2019"
    print(f"\nTrading with initial budget of {budget} and \n"
          f"trading period of {batch_size} days over period of {period}\n")
    print(f"# Mean result of the \"Strategy 1\" : {np.mean(wyn2):.2f}")
    print(f"# Mean result of the \"Strategy 2\" : {np.mean(wyn1):.2f}")
    print(f"# Mean result of the \"Strategy 3\" : {np.mean(wyn3):.2f}")
    print(f"# Mean result of the \"Strategy 4\" : {np.mean(wyn4):.2f}")


def plots():
    dataset = get_data()
    prices, dates = prepare_data(dataset, 5900, 6100, dates=True)

    m, s = macd(prices)
    by, sl = macd_buy_sell(m, s)

    e12 = whole_ema(prices, 12)
    e26 = whole_ema(prices, 26)

    # plot_prices(prices, dates=dates)
    # plot_prices(prices, e12, e26, dates)
    #
    # plot_macd_histogram(m, s)
    #
    # plot_full(macd=m,
    #           signal=s,
    #           buy=by,
    #           sell=sl,
    #           dates=dates,
    #           zero=True)
    #
    # plot_full(macd=m,
    #           signal=s,
    #           dates=dates,
    #           zero=True)
    #
    # plot_macd_prices(prices, m, s, e12, e26)

    # plot_macd_prices(prices, m, s)

    # plot_full(prices=prices,
    #           ema12=e12,
    #           ema26=e26,
    #           macd=m,
    #           signal=s,
    #           buy=by,
    #           sell=sl,
    #           dates=dates,
    #           zero=True)
    #
    # plot_full(
    #     prices=prices,
    #     macd=m,
    #     signal=s,
    #     buy=by,
    #     sell=sl,
    #     dates=dates,
    #     zero=True
    # )

    plot_macd_prices(prices, m, s, buy=by, sell=sl)
    # plot_macd_prices(prices, m, s, buy=by, sell=sl, histogram=True)
    # plot_macd_prices(prices, m, s, histogram=True)


if __name__ == '__main__':
    plots()
    # test_trades()

