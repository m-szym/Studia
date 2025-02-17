function [M,N,P,R,x_coarse,y_coarse,F_coarse,x_fine,y_fine,F_fine] = zadanie4()
P = 20; % liczba unikalnych współrzędnych x punktów dla których będzie obliczana interpolacja
R = 20; % liczba unikalnych współrzędnych y punktów dla których będzie obliczana interpolacja
M = 6; % liczba węzłów interpolacji wzdłuż osi X (stopień wielomianu zmiennej x: M-1)
N = 4; % liczba węzłów interpolacji wzdłuż osi Y (stopień wielomianu zmiennej y: N-1)

% Generowanie węzłów interpolacji na płaszczyźnie
x_coarse = linspace(0, 1, M);
y_coarse = linspace(0, 1, N);
[X_coarse, Y_coarse] = meshgrid(x_coarse, y_coarse);

% Wyznaczenie wartości funkcji oryginalnej w węzłach
F_coarse = 1 + 2.*X_coarse.^5 + 3.*Y_coarse.^3;
% F_coarse = X_coarse.^6 + 5.*X_coarse.^5 + 3.*Y_coarse.^4 - 2.*(X_coarse.^3 + Y_coarse.^3) + 0.5.*X_coarse.^2 - 20.*Y_coarse.^2 - 50.*X_coarse + 10.*Y_coarse + 100; 

subplot(2,1,1);
surf(X_coarse, Y_coarse, F_coarse);


MN = M*N;
xvec_coarse = reshape(X_coarse, MN, 1);
yvec_coarse = reshape(Y_coarse, MN, 1);
fvec_coarse = reshape(F_coarse, MN, 1);

% Macierz Vandermonde'a dla interpolacji 2d
V = zeros(M*N, M*N);
for i = 0:(M-1)
    for j = 0:(N-1)
        V(:, i*N + j + 1) = xvec_coarse.^i .* yvec_coarse.^j;
    end
end

% Współczynniki wielomianu interpolacyjnego
coeffs = V \ fvec_coarse;

% Obliczanie wartości funkcji interpolującej na gęstszej siatce
x_fine = linspace(0, 1, P);
y_fine = linspace(0, 1, R);
[X_fine, Y_fine] = meshgrid(x_fine, y_fine);

F_fine = zeros(size(X_fine));

% zadanie B: zdefiniuj obliczenia wartości wielomianu interpolującego. Rezultat obliczeń zapisz w zmiennej F_fine.
for i = 0:(M-1)
    for j = 0:(N-1)
        % F_fine(i, j) =  polyval(coeffs, x_fine(i)) + polyval(coeffs, y_fine(j)) ;
        %F_fine(i, j) = sum(sum(polyvalm(flipud(coeffs), X_fine)));
        F_fine = F_fine + coeffs(i * N + j + 1) * X_fine .^i .* Y_fine .^ j;
    end
end

subplot(2,1,2);
surf(X_fine, Y_fine, F_fine);


end

