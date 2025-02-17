a = 1;
b = 60000;
ytolerance = 1e-12;
max_iterations = 100;
function_error = 0;

[n_bisection,bis_ysolution,bis_iterations,bis_xtab,bis_xdif] = bisection_method(a,b,max_iterations,ytolerance,@estimate_execution_time);

[n_secant,sec_ysolution,sec_iterations,sec_xtab,sec_xdif] = secant_method(a,b,max_iterations,ytolerance,@estimate_execution_time);


subplot(2,1,1);
plot(bis_xtab);
hold on;
plot(sec_xtab);
title("Zmiana przybliżenia rozwiązania wraz z iteracjami");
ylabel("Przybliżenie rozwiązania");
xlabel("Iteracja");
legend("Bisekcja", "Sieczne");
hold off;

subplot(2,1,2);
semilogy(bis_xdif);
hold on;
semilogy(sec_xdif);
title("Zmiana różnicy między przybliżeniami rozwiązania wraz z iteracjami");
ylabel("Różnica między przybliżeniami");
xlabel("Iteracja");
legend("Bisekcja", "Sieczne");
hold off;


function [xsolution,ysolution,iterations,xtab,xdif] = bisection_method(a,b,max_iterations,ytolerance,fun)
% a - lewa granica przedziału poszukiwań miejsca zerowego
% b - prawa granica przedziału poszukiwań miejsca zerowego
% max_iterations - maksymalna liczba iteracji działania metody bisekcji
% ytolerance - wartość abs(fun(xsolution)) powinna być mniejsza niż ytolerance
% fun - nazwa funkcji, której miejsce zerowe będzie wyznaczane
%
% xsolution - obliczone miejsce zerowe
% ysolution - wartość fun(xsolution)
% iterations - liczba iteracji wykonana w celu wyznaczenia xsolution
% xtab - wektor z kolejnymi kandydatami na miejsce zerowe, począwszy od xtab(1)= (a+b)/2
% xdiff - wektor wartości bezwzględnych z różnic pomiędzy i-tym oraz (i+1)-ym elementem wektora xtab; xdiff(1) = abs(xtab(2)-xtab(1));

xsolution = 0;
ysolution = 0;
iterations = 0;
xtab = [];
xdif = [];

err=1;
while iterations < max_iterations 
    c = (a+b)/2;
    
    if err < ytolerance 
        break
    elseif fun(a)*fun(c) < 0
        b = c;
    else
        a = c;
    end
    xtab = [xtab;c];
    if iterations > 0
        xdif = [xdif;abs(xtab(end) - xtab(end-1))];
        err = abs(fun(c));
    end
    iterations = iterations + 1;

end

xsolution = c;
ysolution = fun(c);


end


function [xsolution,ysolution,iterations,xtab,xdif] = secant_method(a,b,max_iterations,ytolerance,fun)
% a - lewa granica przedziału poszukiwań miejsca zerowego (x0=a)
% b - prawa granica przedziału poszukiwań miejsca zerowego (x1=b)
% max_iterations - maksymalna liczba iteracji działania metody siecznych
% ytolerance - wartość abs(fun(xsolution)) powinna być mniejsza niż ytolerance
% fun - nazwa funkcji, której miejsce zerowe będzie wyznaczane
%
% xsolution - obliczone miejsce zerowe
% ysolution - wartość fun(xsolution)
% iterations - liczba iteracji wykonana w celu wyznaczenia xsolution
% xtab - wektor z kolejnymi kandydatami na miejsce zerowe, począwszy od x2
% xdiff - wektor wartości bezwzględnych z różnic pomiędzy i-tym oraz (i+1)-ym elementem wektora xtab; xdiff(1) = abs(xtab(2)-xtab(1));

xsolution = 0;
ysolution = 0;
iterations = 0;
xtab = [a;b];
xdif = [];

curr = b;
prev = a;
err = 1;
while iterations < max_iterations
    err = abs(fun(curr));
    if err < ytolerance
        break
    end

    tmp = curr;
    curr = curr - (fun(curr)*(curr-prev))/(fun(curr)-fun(prev));
    prev= tmp;


    xtab = [xtab;curr];
    if iterations > 0
        xdif = [xdif;abs(xtab(end) - xtab(end-1))];
    end
        iterations = iterations + 1;
    
end
xtab = xtab(3:end);
xsolution = curr;
ysolution = fun(curr);

end


function time_delta = estimate_execution_time(N)
% time_delta - różnica pomiędzy estymowanym czasem wykonania algorytmu dla zadanej wartości N a zadanym czasem M
% N - liczba parametrów wejściowych
M = 5000; % [s]

if N <= 0
    error("Number o parameters MUST be > 0")
end

t = (N^(16/11) + N^((pi^2)/8))/1000;

time_delta = t - M;

end
