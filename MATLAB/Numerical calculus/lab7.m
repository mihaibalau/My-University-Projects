% Application 1: f(x) = cos(pi * x), nodes {0, 1/3, 1/2, 1}

fprintf('\n');
fprintf('\n');
fprintf('\n');

f = @(x) cos(pi * x);

xnodes = [0, 1/3, 1/2, 1];
ynodes = f(xnodes);

% Newton divided differences
D = newton_divided_diff(xnodes, ynodes);

disp('Newton coefficients D0..D3:');
disp(D);

% Error bound for R3 f on [0,1]
% Using actual difference: max|f(x) - L3(x)|

xx = linspace(0, 1, 10001);

% Evaluate f(x) at all points
ff = cos(pi .* xx);

% Evaluate L3(x) at all points using Newton
L3xx = zeros(size(xx));
for k = 1:length(xx)
  L3xx(k) = newton_eval(D, xnodes, xx(k));
end

% Max absolute error
R3_bound = max(abs(ff - L3xx));

fprintf('Max error |f(x) - L3(x)| on [0,1] = %.6e\n', R3_bound);

% Plot f and its cubic interpolant L3 on [0,1]

xx = linspace(0, 1, 400);
ff = f(xx);

L3 = zeros(size(xx));
for k = 1:length(xx)
    L3(k) = newton_eval(D, xnodes, xx(k));
end

plot(xx, ff, 'b-', 'LineWidth', 2); hold on;
plot(xx, L3, 'r--', 'LineWidth', 2);
plot(xnodes, ynodes, 'ko', 'MarkerFaceColor', 'k'); % the nodes
legend('f(x) = cos(\pi x)', 'L_3 f(x)', 'nodes', 'Location', 'Best');
xlabel('x'); ylabel('y');
grid on;
title('Interpolation of cos(\pi x) with Newton form');

% Approximate cos(pi/5)

xstar = 1/5;                          % ← x input to the polynomial
approx_val = newton_eval(D, xnodes, xstar);  % ← gives cos(pi/5) approximately

true_val = cos(pi/5);                 % ← exact value to compare

fprintf('L3(1/5) = %.10f\n', approx_val);
fprintf('cos(pi/5) = %.10f\n', true_val);
fprintf('absolute error = %.3e\n', abs(true_val - approx_val));

% Error bound for this specific approximation

x = xstar;
w_at_x = (x - xnodes(1)) * (x - xnodes(2)) * ...
         (x - xnodes(3)) * (x - xnodes(4));

R3_bound_x = (pi^4 / factorial(4)) * abs(w_at_x);

fprintf('Pointwise bound for |R3 f(1/5)| <= %.3e\n', R3_bound_x);


% Application 2: Approximate sqrt(2) using Aitken's algorithm
% f(x) = 2^x, nodes -4,-3,...,4

fprintf('\n');
fprintf('\n');
fprintf('\n');

f = @(x) 2.^x;

xnodes = -4:1:4;     % 9 nodes
ynodes = f(xnodes);

xstar = 0.5;         % because sqrt(2) = 2^(1/2)

approx_val = aitken_interp(xnodes, ynodes, xstar);
true_val   = sqrt(2);

fprintf('Aitken approximation of sqrt(2): %.10f\n', approx_val);
fprintf('sqrt(2) = %.10f\n', true_val);
fprintf('absolute error = %.3e\n', abs(true_val - approx_val));

% Application 3: interpolate lg x between 1000 and 1050

fprintf('\n');
fprintf('\n');
fprintf('\n');

xnodes = [1000, 1010, 1020, 1030, 1040, 1050];
ynodes = [3.0000000, ...
          3.0043214, ...
          3.0086002, ...
          3.0128372, ...
          3.0170333, ...
          3.0211893];

% coefficients for Newton polynomial
D = newton_divided_diff(xnodes, ynodes);

fprintf('x\tapprox_lg(x)\n');
for x = 1001:1009
    val = newton_eval(D, xnodes, x);
    fprintf('%d\t%.7f\n', x, val);
end
