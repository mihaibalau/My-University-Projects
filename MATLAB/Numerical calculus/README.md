# Numerical calculus

Scripts from the numerical calculus course, written for MATLAB and Octave. `lab5.m` and `lab9.m` use Octave (`printf`, and `spline` with the not-a-knot default).

`divdiff.m` builds three tables: Newton divided differences, Hermite divided differences (each node repeated, with the derivative on the duplicated point) and backward differences. `lab2.m` runs them on `1/(1+x)` and on a small measured table.

`save.m` plots the Maclaurin polynomials of `e^x` up to degree 4 against the function, then sums the series for `e`.

`lab4.m` solves one linear system with Gaussian elimination with partial pivoting and with an LUP factorization.

`lab5.m` builds a tridiagonal system and compares Jacobi with Gauss-Seidel (iteration counts and the difference of the two solutions). The second half is Wilson's example: a small change in `b` or in `A` moves `x` a lot, and the script prints the relative errors next to `cond(A)`.

`lab7.m` interpolates `cos(pi x)` in Newton form and checks the error of that polynomial on `[0, 1]`.

`lab9.m` compares a not-a-knot cubic spline with a complete spline that also uses the derivatives at the ends, plotted against the real function.

`lab10.m` approximates `ln(2)` as the integral of `1/x` on `[1, 2]`. It doubles the number of panels for the composite rectangle, trapezoid and Simpson rules until the error is under `5 * 10^-4` (three correct decimals).

Technologies: MATLAB, Octave.
