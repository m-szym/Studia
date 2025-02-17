import pandas as pd


def get_data():
    #url = 'https://stooq.pl/q/d/l/?s=wig20&d1=20000416&d2=20240228&i=d'
    url = 'https://stooq.pl/q/d/l/?s=wig20&i=d'
    #url = 'https://stooq.pl/q/d/l/?s=att&i=d'
    #url = 'https://stooq.pl/q/d/l/?s=xauusd&i=d'
    names = ["Data", "Otwarcie", "Najwyzszy", "Najnizszy", "Zamkniecie", "Wolumen"]
    dataset = pd.read_csv(url, sep=',', names=names, skiprows=1)
    return dataset


def inspect_data(dataset):
    print('Dataset shape:')
    print(dataset.shape)

    print('Tail:')
    print(dataset.tail())

    print('Statistics:')
    print(dataset.describe().transpose())


def prepare_data(dataset, slice_start, slice_end, price_to_use="Zamkniecie", dates=False):
    prices = dataset[price_to_use][slice_start:slice_end].to_numpy()
    if not dates:
        return prices
    dates = dataset["Data"][slice_start:slice_end].to_numpy()
    return prices, dates
