function plot_problem_5(N,time_Jacobi,time_Gauss_Seidel,iterations_Jacobi,iterations_Gauss_Seidel)
% Opis wektorów stanowiących parametry wejściowe:
% N - rozmiary analizowanych macierzy
% time_Jacobi - czasy wyznaczenia rozwiązania metodą Jacobiego
% time_Gauss_Seidel - czasy wyznaczenia rozwiązania metodą Gaussa-Seidla
% iterations_Jacobi - liczba iteracji wymagana do wyznaczenia rozwiązania metodą Jacobiego
% iterations_Gauss_Seide - liczba iteracji wymagana do wyznaczenia rozwiązania metodą Gauss-Seidla

subplot(2,1,1);
plot(N,time_Jacobi); 
hold on; 
plot(N,time_Gauss_Seidel); 
xlabel("Rozmiar macierzy");
ylabel("Czas obliczeń");
title("Zależność czasu obliczeń od rozmiaru macierzy");
legend("Jacobi", "Gauss-Seidel", 'Location', 'eastoutside');
hold off;

subplot(2,1,2);
bar(N, [iterations_Jacobi; iterations_Gauss_Seidel])
xlabel("Rozmiar macierzy");
ylabel("Liczba iteracji");
title("Zależność liczby iteracji od rozmiaru macierzy");
legend("Jacobi", "Gauss-Seidel", 'Location', 'eastoutside');

% print -dpng zadanie5.png 
end