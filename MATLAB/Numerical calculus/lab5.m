% Application 1: tridiagonal system, n = 1000

n = 10;

% Build A (n x n) and b (n x 1)
A = zeros(n, n);
b = zeros(n, 1);

% First equation: 5*x1 - x2 = 4
A(1, 1) = 5;
A(1, 2) = -1;
b(1) = 4;

% Middle equations: -x_{j-1} + 5*x_j - x_{j+1} = 3
for j = 2:(n-1)
  A(j, j-1) = -1;
  A(j, j)   = 5;
  A(j, j+1) = -1;
  b(j) = 3;
end

% Last equation: -x_{n-1} + 5*x_n = 4
A(n, n-1) = -1;
A(n, n)   = 5;
b(n) = 4;

% Initial guess, desired error, max iterations
x0 = zeros(n, 1);
err = 1e-5;
maxnit = 10000;

% Call Jacobi
[xJ, nitJ] = Jacobi(A, b, x0, err, maxnit);

% Call Gauss-Seidel
[xGS, nitGS] = GaussSeidel(A, b, x0, err, maxnit);

% Display number of iterations
printf("Jacobi iterations: %d\n", nitJ);
printf("Gauss-Seidel iterations: %d\n", nitGS);

% (Optional) check how close solutions are:
diff_norm = norm(xJ - xGS, inf);
printf("Infinity-norm difference between solutions: %e\n", diff_norm);


% Application 2: Wilson's example

printf("\n\n", rel_err_b_in);
A = [10 7  8   7;
     7  5  6   5;
     8  6  10  9;
     7  5  9  10];

b = [32; 23; 33; 31];

b_tilde = [32.1; 22.9; 33.1; 30.9];

A_tilde = [10    7    8.1  7.2;
           7.8   5.04 6    5;
           8     5.98 9.89 9;
           6.99  4.99 9    9.98];

% (a) Solve Ax = b
x = A \ b;

% (b) Perturb b: solve A x = b_tilde
x_tilde_b = A \ b_tilde;

% Relative input error (in b) and output error (in x)
rel_err_b_in  = norm(b_tilde - b) / norm(b);
rel_err_b_out = norm(x_tilde_b - x) / norm(x);

printf("(b) relative input  error in b: %e\n", rel_err_b_in);
printf("(b) relative output error in x: %e\n", rel_err_b_out);

% (c) Perturb A: solve A_tilde x = b
x_tilde_A = A_tilde \ b;

% Relative input error (in A) and output error (in x)
rel_err_A_in  = norm(A_tilde - A, 'fro') / norm(A, 'fro');
rel_err_A_out = norm(x_tilde_A - x) / norm(x);

printf("(c) relative input  error in A: %e\n", rel_err_A_in);
printf("(c) relative output error in x: %e\n", rel_err_A_out);

% (Optional) condition number of A, to show ill-conditioning
condA = cond(A);
printf("Condition number cond(A): %e\n", condA);

