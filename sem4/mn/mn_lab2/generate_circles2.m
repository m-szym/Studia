function [circles, index_number, circle_areas, rand_counts, counts_mean] = generate_circles2(a, r_max, n_max)
index_number = 193229; % numer Twojego indeksu
L1 = 9;
L2 = 2;
circles = zeros(n_max, 3);
rand_counts = zeros(n_max, 1);

for j = 1:n_max
    is_valid = false;

    while is_valid ~= true
        rand_counts(j) = rand_counts(j) + 1;
        is_valid = true;
        r = rand() * r_max;
        x = (rand() * (a - 2*r)) + r;
        y = (rand() * (a - 2*r)) + r;
    
        
        for i = 1:n_max
            if circles(i,1) == 0
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
    end

    circles(j, 1) = x;
    circles(j, 2) = y;
    circles(j, 3) = r;
end

circle_areas = pi*circles(:,3).^2;
circle_areas = cumsum(circle_areas);

counts_mean = zeros(n_max, 1);
for i = 1:n_max
    counts_mean(i) = mean(rand_counts(1:i));
end

if L2 % 2 == 0;
    circle_areas = circle_areas';
end

if L1 % 2 == 1;
    circles = circles';
    circles = [circles(3,:); circles(1:2,:)];
end

end
