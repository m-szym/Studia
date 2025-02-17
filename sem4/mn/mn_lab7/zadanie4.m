function [integration_error, Nt, ft_5, integral_1000] = zadanie4()
    % Numeryczne całkowanie metodą Monte Carlo.
    %
    %   integration_error - wektor wierszowy. Każdy element integration_error(1,i)
    %       zawiera błąd całkowania obliczony dla liczby losowań równej Nt(1,i).
    %       Zakładając, że obliczona wartość całki dla Nt(1,i) próbek wynosi
    %       integration_result, błąd jest definiowany jako:
    %       integration_error(1,i) = abs(integration_result - reference_value),
    %       gdzie reference_value to wartość referencyjna całki.
    %
    %   Nt - wektor wierszowy zawierający liczby losowań, dla których obliczano
    %       wektor błędów całkowania integration_error.
    %
    %   ft_5 - gęstość funkcji prawdopodobieństwa dla n=5
    %
    %   [xr, yr] - tablice komórkowe zawierające informacje o wylosowanych punktach.
    %       Tablice te mają rozmiar [1, length(Nt)]. W komórkach xr{1,i} oraz yr{1,i}
    %       zawarte są współrzędne x oraz y wszystkich punktów zastosowanych
    %       do obliczenia całki przy losowaniu Nt(1,i) punktów.
    %
    %   yrmax - maksymalna dopuszczalna wartość współrzędnej y losowanych punktów

    reference_value = 0.0473612919396179; % wartość referencyjna całki

    ft_5 = awaria(5);

    Nt = 5:50:10^4;
    integration_error = [];
    xr = cell(1, length(Nt));
    yr = cell(1, length(Nt));
    yrmax = ft_5 + 0.1;

    integral_1000 = monte_carlo(@awaria, 1000, yrmax);

    reference_value = 0.0473612919396179; % wartość referencyjna całki

    Nt = 5:50:10^4;
    integration_error = ones(size(Nt));

    for i=1:size(Nt, 2)
        [integration_result, xp, yp] = monte_carlo(@awaria, Nt(i), yrmax);
        xr{1, i} = xp;
        yr{1, i} = yp;
        integration_error(i) = abs(integration_result - reference_value);
    end
    
    loglog(Nt,integration_error);
    xlabel("Liczba podprzedziałów całkowania");
    ylabel("Błąd całkowania");
    title("Zależność błędu całkowania od liczby podprzedziałów całkowania");
    print("zadanie4", "-dpng");



end

function [f] = awaria(t)
    sigma = 3;
    mu = 10;

    f = exp(-((t - mu)^2) / (2 * sigma^2));
    f = f / (sigma * sqrt(2 * pi));
end

function [value, xp, yp] = monte_carlo(fun, k, yrmax)
    n = 5;
    value = 0;
    xp = zeros(1, k);
    yp = zeros(1, k);
    for i=1:k
        xp(i) = rand() * n;
        yp(i) = rand() * yrmax;
        if (yp(i) <= fun(xp(i)))
            value = value + 1;
        end
    end

    value = (value / k) * (n * yrmax);
end
