function plot_circle_areas(circle_areas)
hold on;
xlabel("Nr pęcherzyka");
ylabel("Pole pęcherzyka");
title("Wykres pól pęcherzyków");
x = linspace(0, max(size(circle_areas)), max(size(circle_areas)));
plot(x, circle_areas);
hold off;

% print -dpng zadanie3.png 
end