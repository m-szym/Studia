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