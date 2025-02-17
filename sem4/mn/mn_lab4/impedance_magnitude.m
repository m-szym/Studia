function impedance_delta = impedance_magnitude(omega)

R = 525;
C = 7e-5;
L = 3;
M = 75; % docelowa wartość modułu impedancji

if omega <= 0 
    error("omega MUST be > 0")
end


Z = (1/R^2) + (omega*C - 1/(omega*L))^2;
Z = 1/sqrt(Z);


impedance_delta = Z - M;

end