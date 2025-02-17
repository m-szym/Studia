function [A,b,M,bm,x,err_norm,time,iterations,index_number] = solve_Jacobi(N)
% A - macierz z równania macierzowego A * x = b
% b - wektor prawej strony równania macierzowego A * x = b
% x - rozwiązanie równania macierzowego
% time_direct - czas wyznaczenia rozwiązania x
% err_norm - norma błędu rezydualnego rozwiązania x; err_norm = norm(A*x-b);
% index_number - Twój numer indeksu
index_number = 193229;
L1 = 9;

[A, b] = generate_matrix(N, L1);

L = tril(A, -1);
U = triu(A, 1);
D = diag(diag(A));

r = ones(N, 1);
M = -1*inv(D)*(L+U);
bm = inv(D)*b;

iterations = 0;
err_norm = norm(A*r-b);

tic;
while (err_norm > 1E-12 && iterations < 1000)
    r = M*r + bm;
    err_norm = norm(A*r-b);
    iterations = iterations + 1;
end

time = toc;
x = r;

end