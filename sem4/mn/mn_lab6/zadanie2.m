function [country, source, degrees, y_original, y_movmean, y_approximation, mse] = zadanie2(energy)
% Głównym celem tej funkcji jest wyznaczenie aproksymacji wygładzonych danych o produkcji energii elektrycznej w wybranym kraju i z wybranego źródła energii.
% Wygładzenie danych wykonane jest poprzez wywołanie funkcji movmean.
% Wybór kraju i źródła energii należy określić poprzez nadanie w tej funkcji wartości zmiennym typu string: country, source.
% Dopuszczalne wartości tych zmiennych można sprawdzić poprzez sprawdzenie zawartości struktury energy zapisanej w pliku energy.mat.
% 
% energy - struktura danych wczytana z pliku energy.mat
% country - [String] nazwa kraju
% source  - [String] źródło energii
% degrees - wektor zawierający cztery stopnie wielomianu dla których wyznaczono aproksymację
% y_original - dane wejściowe, czyli pomiary produkcji energii zawarte w wektorze energy.(country).(source).EnergyProduction
% y_movmean - średnia 12-miesięczna danych wejściowych, y_movmean = movmean(y_original,[11,0]);
% y_approximation - tablica komórkowa przechowująca cztery wartości funkcji aproksymującej wygładzone dane wejściowe. y_approximation stanowi aproksymację stopnia degrees(i).
% mse - wektor o rozmiarze 4x1: mse(i) zawiera wartość błędu średniokwadratowego obliczonego dla aproksymacji stopnia degrees(i).

country = 'Poland';
source = 'Gas';
degrees = [1, 3, 12, 22];
y_original = energy.(country).(source).EnergyProduction;
y_approximation= {[], [], [], []};
mse = [0, 0, 0, 0];

% Sprawdzenie dostępności danych
if isfield(energy, country) && isfield(energy.(country), source)
    % Przygotowanie danych do aproksymacji
    dates = energy.(country).(source).Dates;
    y_original = energy.(country).(source).EnergyProduction;
    y_movmean = movmean(y_original,[11,0]);

    x = linspace(-1,1,length(y_original))';

    % Pętla po wielomianach różnych stopni
    % Pętla po wielomianach różnych stopni
    for i = 1:length(degrees)
        p = polyfit(x, y_movmean, degrees(i));
        z =  polyval(p, x);
        y_approximation{i} = z;
        mse(i) = mean((y_movmean - z) .^ 2);
    end

    subplot(2,1,1);
    plot(x, y_original, 'DisplayName','original');
    hold on;
    plot(x, y_movmean, 'DisplayName', 'movmean');
    for i = 1:length(degrees)
        plot(x, y_approximation{i}, 'DisplayName',string(degrees(i)));
    end
    legend("AutoUpdate","on");
    xlabel("X");
    ylabel("Energy produced [TWh]");
    title("Approximated energy production");
    hold off;

    subplot(2,1,2); 
    bar(mse); 
    set(gca, 'XTickLabel', degrees);
    hold on;
    xlabel("Polynomial degree");
    ylabel("MSE");
    title("MSE for polynomials of different degress");
    hold off;
    
    print("zadanie2", "-dpng");

else
    disp(['Dane dla (country=', country, ') oraz (source=', source, ') nie są dostępne.']);
end

end