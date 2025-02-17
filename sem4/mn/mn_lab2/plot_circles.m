function plot_circles(circles, L1)

axis equal;
axis([0 200 0 200]);
hold on;

if L1 % 2 == 1;
    circles = [circles(2:3,:); circles(1,:)];
    circles = circles';   
end

for i = 1:max(size(circles))
    plot_circle(circles(i,3), circles(i,1), circles(i,2));
end

hold off

% print -dpng zadanie1.png 

end