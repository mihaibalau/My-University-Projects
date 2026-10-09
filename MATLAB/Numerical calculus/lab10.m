% Approximate ln(2) with 3 correct decimals using
% composite rectangle, trapezoid and Simpson rules.

f = @(x) 1 ./ x;
a = 1;
b = 2;
I_exact = log(2);        % exact integral value
tol = 0.5e-3;            % 3 correct decimals

% Make sure nc_formulas.m is in the current folder or on the path.
% We will try n = 1, 2, 4, 8, ... until the tolerance is met.

fprintf('Exact value: ln(2) = %.15f\n\n', I_exact);

% -------- Rectangle (midpoint) rule --------
n = 1;
while true
  I_rect = rect_comp(f, a, b, n);
  err = abs(I_rect - I_exact);
  fprintf('[Rectangle] n = %4d, I = %.10f, error = %.5e\n', n, I_rect, err);
  if err < tol
    fprintf('Rectangle: tolerance reached with n = %d.\n\n', n);
    break;
  end
  n = n * 2;
end

% -------- Trapezoid rule --------
n = 1;
while true
  I_trap = trap_comp(f, a, b, n);
  err = abs(I_trap - I_exact);
  fprintf('[Trapezoid] n = %4d, I = %.10f, error = %.5e\n', n, I_trap, err);
  if err < tol
    fprintf('Trapezoid: tolerance reached with n = %d.\n\n', n);
    break;
  end
  n = n * 2;
end

% -------- Simpson rule --------
n = 2;   % must be even
while true
  I_simp = simpson_comp(f, a, b, n);
  err = abs(I_simp - I_exact);
  fprintf('[Simpson  ] n = %4d, I = %.10f, error = %.5e\n', n, I_simp, err);
  if err < tol
    fprintf('Simpson: tolerance reached with n = %d.\n\n', n);
    break;
  end
  n = n * 2;
end


% ex2.m – Area under f(x) = x*exp(-x)/(x^2 + 1) on [0,1]
% using composite rectangle, trapezoid and Simpson rules.

f = @(x) x .* exp(-x) ./ (x.^2 + 1);
a = 0;
b = 1;

% Plot the function (part (a) of the exercise)
xplot = linspace(a, b, 200);
yplot = f(xplot);
figure;
plot(xplot, yplot, 'LineWidth', 1.5);
grid on;
xlabel('x');
ylabel('f(x)');
title('f(x) = x e^{-x} / (x^2 + 1) on [0,1]');

% Get a reference "exact" value for the integral.
% Try to use integral if it exists, otherwise approximate with fine Simpson.
if exist('integral', 'file')
  I_exact = integral(f, a, b);
else
  % fallback: very fine Simpson approximation
  I_exact = simpson_comp(f, a, b, 4096);
end

fprintf('Reference value of the integral: %.15f\n\n', I_exact);

n_values = 2 .^ (1 : 8);   % [2,4,8,...,256]

% We will store errors to compute ratios.
err_rect = zeros(size(n_values));
err_trap = zeros(size(n_values));
err_simp = zeros(size(n_values));

fprintf('n   Rectangle_error   Ratio   Trapezoid_error   Ratio   Simpson_error   Ratio\n');
fprintf('--------------------------------------------------------------------------------\n');

for k = 1 : length(n_values)
  n = n_values(k);

  I_rect = rect_comp(f, a, b, n);
  I_trap = trap_comp(f, a, b, n);
  % For Simpson we need even n, but n is already 2,4,8,...,256 so it is fine.
  I_simp = simpson_comp(f, a, b, n);

  err_rect(k) = abs(I_rect - I_exact);
  err_trap(k) = abs(I_trap - I_exact);
  err_simp(k) = abs(I_simp - I_exact);

  if k == 1
    ratio_rect = NaN;
    ratio_trap = NaN;
    ratio_simp = NaN;
  else
    ratio_rect = err_rect(k-1) / err_rect(k);
    ratio_trap = err_trap(k-1) / err_trap(k);
    ratio_simp = err_simp(k-1) / err_simp(k);
  end

  fprintf('%3d  %14.5e  %6.2f  %16.5e  %6.2f  %14.5e  %6.2f\n', ...
          n, err_rect(k), ratio_rect, err_trap(k), ratio_trap, err_simp(k), ratio_simp);
end

% ex3.m – Composite trapezoid for erf(x) on x = 0.1, 0.2, ..., 1.0

% The integrand inside erf(x) = (2/sqrt(pi)) * integral from 0 to x of e^(-t^2) dt
g = @(t) (2 / sqrt(pi)) * exp(-t.^2);

xs  = 0.1 : 0.1 : 1.0;   % the x values we tabulate
n   = 1000;               % number of subintervals for the trapezoid rule

fprintf('   x      erf_trap       erf_builtin    abs_error\n');
fprintf('----------------------------------------------------\n');

for x = xs
  % Composite trapezoid of g on [0, x] with n subintervals
  erf_trap = trap_comp(g, 0, x, n);

  % Built-in erf for comparison
  erf_ref  = erf(x);

  err = abs(erf_trap - erf_ref);

  fprintf('%4.1f  %12.8f   %12.8f   %.3e\n', x, erf_trap, erf_ref, err);
end
