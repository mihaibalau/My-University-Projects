% Exercise 1a
x = linspace(-3, 3, 100);

f = exp(x);
T1 = 1 + x;
T2 = 1 + x + (x.^2)/2;
T3 = 1 + x + (x.^2)/2 + (x.^3)/6;
T4 = 1 + x + (x.^2)/2 + (x.^3)/6 + (x.^4)/24;

figure(1);
plot(x, f, 'k', x, T1, 'r', x, T2, 'g', x, T3, 'b', x, T4, 'm');
legend('e^x', 'T1', 'T2', 'T3', 'T4', 'Location', 'northwest');
grid on;
title('Maclaurin Polynomials of e^x');

% Exercise 1b
format long

n = 10;
k = 0:n;
terms = 1 ./ factorial(k);
approx_e = sum(terms);
disp('Approximation of e:');
disp(approx_e);

% Proof that the error is smaller than 0.5 * 10^-6
error_bound = 3 / factorial(n + 1);
actual_error = abs(exp(1) - approx_e);
tolerance = 0.5 * 10^-6;

disp('Actual Error (must be < 5e-07):');
disp(actual_error);

disp('Is the actual error strictly smaller than the tolerance? (1 = Yes)');
disp(actual_error < tolerance);

% Exercise 2a
x = linspace(-pi, pi, 100);

f = sin(x);
T3 = x - (x.^3)/6;
T5 = x - (x.^3)/6 + (x.^5)/120;

figure(2);
plot(x, f, 'k', x, T3, 'r', x, T5, 'b');
legend('sin(x)', 'T3', 'T5', 'Location', 'south');
grid on;
title('Maclaurin Polynomials of sin(x)');

% ----- Exercise 2b -----
format long;

n = 2;
k = 0:n;
x_val = pi / 5;

numerator = (-1).^k .* (x_val.^(2*k + 1));
denominator = factorial(2.*k + 1);
terms = numerator ./ denominator;

approx_sin = sum(terms);
true_sin = sin(x_val);
actual_error = abs(true_sin - approx_sin);


% Exercise 3a
x = linspace(-0.9, 1, 100);

f = log(1 + x);
T2 = x - (x.^2)/2;
T5 = x - (x.^2)/2 + (x.^3)/3 - (x.^4)/4 + (x.^5)/5;

figure(3);
plot(x, f, 'k', x, T2, 'r', x, T5, 'b');
legend('ln(1+x)', 'T2', 'T5', 'Location', 'northwest');
grid on;
title('Maclaurin Polynomials of ln(1+x)');

% Exercise 3b
format long;

n = 199999;
k = 1:n;

% General term of ln(1+x) at x=1: (-1)^(k-1) * (1^k / k) = (-1)^(k-1) / k
terms = ((-1).^(k - 1)) ./ k;

approx_ln2 = sum(terms);
true_ln2 = log(2);
actual_error = abs(true_ln2 - approx_ln2);
tolerance = 0.5 * 10^-5;

disp('Approximation of ln(2) with 200000 terms:');
disp(approx_ln2);
disp('Actual Error:');
disp(actual_error);
disp('Is error smaller than tolerance? (1 = Yes)');
disp(actual_error < tolerance);

% Exercise 3c
% ln(1-x) is obtained by substituting x -> -x in formula (5)
% Result: ln(1-x) = -x - x^2/2 - x^3/3 - x^4/4 - x^5/5 - ...

n = 5;
k = 1:n;
x_val = 0.5;

terms_ln1minusx = -(x_val.^k) ./ k;

approx_ln1minusx = sum(terms_ln1minusx);
true_ln1minusx = log(1 - x_val);

disp('Approximation of ln(1-x) at x=0.5:');
disp(approx_ln1minusx);
disp('True value:');
disp(true_ln1minusx);



