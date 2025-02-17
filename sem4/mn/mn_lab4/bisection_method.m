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