function plot_direct(N, vtime_direct)
    % N - wektor zawierający rozmiary macierzy dla których zmierzono czas obliczeń metody bezpośredniej
    % vtime_direct - czas obliczeń metody bezpośredniej dla kolejnych wartości N
    plot(N, vtime_direct);
    xlabel("Rozmiary macierzy A");
    ylabel("Czas rozwiązywania [s]");
    title("Zależność czasu rozwiązywnia równania od wielkości macierzy A");

end