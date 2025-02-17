from iterative import solve_jacobi, solve_gauss_seidel
from lu import solve_lu
from equation import get_matrix, get_vector
from plots import plot_errors, plot_execution_times



# part A
n = 929
A = get_matrix(n, 7, -1, -1)
b = get_vector(n, 3)


# part B
r_j, ferr_j, errs_j, t_j = solve_jacobi(A, b, low_bound=1e-9, iterations=100)
r_gs, ferr_gs, errs_gs, t_gs = solve_gauss_seidel(A, b, low_bound=1e-9, iterations=100)

print(f"Final norm of residuum of Jacobi: {ferr_j}, after {len(errs_j)} iterations in {t_j:.2f}s")
print(f"Final norm of residuum of Gauss-Seidel: {ferr_gs}, after {len(errs_gs)} iterations in {t_gs:.2f}s")

plot_errors([errs_j, errs_gs])


# part C
A2 = get_matrix(929, 3, -1, -1)
r_j2, ferr_j2, errs_j2, t_j2 = solve_jacobi(A2, b, low_bound=1e-9, iterations=100)
r_gs2, ferr_gs2, errs_gs2, t_gs2 = solve_gauss_seidel(A2, b, low_bound=1e-9, iterations=100)


# part D
r_lu, ferr_lu, t_lu = solve_lu(A2, b)
print(f"Norm of residuum of LU: {ferr_lu} in {t_lu:.4f}s")


# part E
sizes = [100, 500, 1000, 2000, 3000]
times = [[], [], []]
for s in sizes:
    sA = get_matrix(s, 7, -1, -1)
    sb = get_vector(s, 3)

    *_, st_j  = solve_jacobi(sA, sb, low_bound=1e-9, iterations=1000)
    *_, st_gs = solve_gauss_seidel(sA, sb, low_bound=1e-9, iterations=1000)
    *_, st_lu = solve_lu(sA, sb)
    
    times[0].append(st_j)
    times[1].append(st_gs)
    times[2].append(st_lu)

plot_execution_times(sizes, times)