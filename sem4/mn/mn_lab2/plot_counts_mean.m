function plot_counts_mean(counts_mean)
hold on;
xlabel("Nr pęcherzyka");
ylabel("Średnia liczba prób");
title("Wykres średniej liczby prób generowania pęcherzyków");
x = linspace(0, max(size(counts_mean)), max(size(counts_mean)));
plot(x, counts_mean);
hold off;

% print -dpng zadanie3.png 
end