function [nodes_Chebyshev, V, V2, original_Runge, interpolated_Runge, interpolated_Runge_Chebyshev] = zadanie2()
% nodes_Chebyshev - wektor wierszowy zawierający N=16 węzłów Czebyszewa drugiego rodzaju
% V - macierz Vandermonde obliczona dla 16 węzłów interpolacji rozmieszczonych równomiernie w przedziale [-1,1]
% V2 - macierz Vandermonde obliczona dla węzłów interpolacji zdefiniowanych w wektorze nodes_Chebyshev
% original_Runge - wektor wierszowy zawierający wartości funkcji Runge dla wektora x_fine=linspace(-1, 1, 1000)
% interpolated_Runge - wektor wierszowy wartości funkcji interpolującej określonej dla równomiernie rozmieszczonych węzłów interpolacji
% interpolated_Runge_Chebyshev - wektor wierszowy wartości funkcji interpolującej wyznaczonej
%       przy zastosowaniu 16 węzłów Czebyszewa zawartych w nodes_Chebyshev 
    N = 16;
    x_fine = linspace(-1, 1, 1000);
    original_Runge = ((x_fine.^2).*25 + 1);
    original_Runge = 1./original_Runge;
    x_course = linspace(-1, 1, N);
    y_course = 1./(((x_course.^2).*25 + 1));
    nodes_Chebyshev = get_Chebyshev_nodes(N)

    V = vandermonde_matrix(N);
    V2 = chebyshev_vandermonde_matrix(nodes_Chebyshev);

    runge_nodes = (1./((x_course.^2).*25 + 1))';
    c_runge = V \ runge_nodes;
    interpolated_Runge = polyval(flipud(c_runge), x_fine);

    runge_cheybyshev = (1./(1 + 25*nodes_Chebyshev.^2))';
    cc_runge = V2 \ runge_cheybyshev;
    interpolated_Runge_Chebyshev = polyval(flipud(cc_runge), x_fine);

    subplot(2,1,1);
    plot(x_fine, original_Runge);
    hold on;
    plot(x_course, y_course, 'o');
    plot(x_fine, interpolated_Runge);
    xlabel("x");
    ylabel("Wartości funkcji");
    title("Interpolacja f. Rungego");
    legend("Dokładna", "Węzły", "Interpolacja");
    hold off;

    subplot(2,1,2);
    plot(x_fine, original_Runge);
    hold on;
    plot(x_course, y_course, 'o');
    plot(x_fine, interpolated_Runge_Chebyshev);
    xlabel("x");
    ylabel("Wartości funkcji");
    title("Interpolacja f. Rungego w węzłami Czebyszewa");
    legend("Dokładna", "Węzły", "Interpolacja");
    hold off;

    print("zadanie2", "-dpng");
end

function nodes = get_Chebyshev_nodes(N)
    % oblicza N węzłów Czebyszewa drugiego rodzaju
    n = linspace(0, N-1, N);
    nodes = cos((n * pi)./ (N-1));
end

    function V = vandermonde_matrix(N)
        % Generuje macierz Vandermonde dla N równomiernie rozmieszczonych w przedziale [-1, 1] węzłów interpolacji
        x_coarse = linspace(-1,1,N);
        V = zeros(N,N);
        for i = 1:N
            V(:, i) = x_coarse.^(i-1);
        end
    end

    function V = chebyshev_vandermonde_matrix(nodes)
        N = size(nodes, 2);
        V = zeros(N, N);
        for i = 1:N
            V(:, i) = nodes.^(i-1);
        end
    end