function plot_PageRank(r)
hold on;
xlabel("Strona");
ylabel("Ranga");
title("PageRank");
bar(r);
hold off;
% print -dpng zadanie7.png 
end