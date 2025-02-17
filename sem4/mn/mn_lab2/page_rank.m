function [numer_indeksu, Edges, I, B, A, b, r] = page_rank()
numer_indeksu = 193229;
Edges = [1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5, 6, 6, 7, 8;
        4, 6, 3, 4, 5, 5, 6, 7, 8, 5, 6, 4, 6, 4, 7 ,6 ,3];
N = 8;
d = 0.85;
I = speye(N);
B = sparse(Edges(2,:), Edges(1,:),  1, N, N);
A = spdiags(transpose(1./sum(B)), 0, N, N);
b = ones(N, 1) * ((1 - d) / N);
M = I - d * B * A;
r = M\b;


end