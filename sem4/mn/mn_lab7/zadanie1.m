function [integration_error, Nt, ft_5, integral_1000] = zadanie1()
    % Numeryczne całkowanie metodą prostokątów.
    % Nt - wektor zawierający liczby podprzedziałów całkowania
    % integration_error - integration_error(1,i) zawiera błąd całkowania wyznaczony
    %   dla liczby podprzedziałów równej Nt(i). Zakładając, że obliczona wartość całki
    %   dla Nt(i) liczby podprzedziałów całkowania wyniosła integration_result,
    %   to integration_error(1,i) = abs(integration_result - reference_value),
    %   gdzie reference_value jest wartością referencyjną całki.
    % ft_5 - gęstość funkcji prawdopodobieństwa dla n=5
    % integral_1000 - całka od 0 do 5 funkcji gęstości prawdopodobieństwa
    %   dla 1000 podprzedziałów całkowania

    reference_value = 0.0473612919396179; % wartość referencyjna całki

    Nt = 5:50:10^4;
    integration_error = ones(size(Nt));

    for i=1:size(Nt, 2)
        integration_result = int_square(@awaria, Nt(i));
        integration_error(i) = abs(integration_result - reference_value);
    end
    
    loglog(Nt,integration_error);
    xlabel("Liczba podprzedziałów całkowania");
    ylabel("Błąd całkowania");
    title("Zależność błędu całkowania od liczby podprzedziałów całkowania");
    print("zadanie1", "-dpng");

    ft_5 = awaria(5);
    integral_1000 = int_square(@awaria, 1000);

end

function [f] = awaria(t)
    sigma = 3;
    mu = 10;

    f = exp(-((t - mu)^2) / (2 * sigma^2));
    f = f / (sigma * sqrt(2 * pi));
end

function [value] = int_square(fun, k)
    a = 0;
    b = 5;
    delta = (b - a) / k;
    value = 0;
    for i=1:k
        value = value + fun(((a + (i-1) * delta) + (a + (i-1+1) * delta) ) / 2) * delta;
    end
end
