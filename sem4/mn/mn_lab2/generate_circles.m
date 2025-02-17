function [circles, index_number, circle_areas] = generate_circles(a, r_max, n_max)
index_number = 193229; % numer Twojego indeksu
L1 = 9;
L2 = 2;
circles = zeros(n_max, 3);

good_circles = 1;
while good_circles <= n_max
    r = rand() * r_max;
    x = (rand() * (a - 2*r)) + r;
    y = (rand() * (a - 2*r)) + r;

    is_valid = true;
    for i = 1:n_max
        if circles(i,1) == 0;
            break
        end
        if norm([circles(i,1), circles(i,2)] - [x, y]) < (circles(i,3) + r)
            is_valid = false;
            break
        end

        if x - r < 0 || x + r > 200 || y - r < 0 || y + r > 200
            is_valid = false;
            break
        end

    end

    if is_valid
        circles(good_circles, 1) = x;
        circles(good_circles, 2) = y;
        circles(good_circles, 3) = r;
        good_circles = good_circles + 1;
    end
end

circle_areas = zeros(n_max, 1);
circle_areas = pi*circles(:,3).^2;
circle_areas = cumsum(circle_areas);

if L2 % 2 == 0;
    circle_areas = circle_areas';
end

if L1 % 2 == 1;
    circles = circles';
    circles = [circles(3,:); circles(1:2,:)];
end

end
