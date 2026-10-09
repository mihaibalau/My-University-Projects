% --- Exercise 1 (Simplified) ---
% 1. Define the function
f = @(x) (x + 1) ./ (3 * x.^2 + 2 * x + 1);

% 2. Define the 7 equally spaced nodes and evaluation points
x = linspace(-2, 4, 7);
y = f(x);
xx = linspace(-2, 4, 100); % Points for drawing a smooth curve

% 3. Calculate the deBoor (Not-a-knot) cubic spline
% Octave's spline function uses deBoor boundary conditions by default
y_deBoor = spline(x, y, xx);

% 4. Plot the results
figure(1);
plot(x, y, 'ko', 'MarkerSize', 8, 'MarkerFaceColor', 'k'); hold on;
plot(xx, f(xx), 'k-', 'LineWidth', 2);
plot(xx, y_deBoor, 'b--', 'LineWidth', 2);
legend('Nodes', 'Exact f(x)', 'deBoor Spline');
title('Exercise 1: deBoor Spline Interpolation');
grid on;
hold off;

% --- Exercise 2 (Simplified) ---
% 1. Define the function and its derivative (we only need the derivative for the endpoints)
f = @(x) x .* sin(pi * x);
df = @(x) sin(pi * x) + pi * x .* cos(pi * x);

% 2. Define the nodes given in the lab
x = [-1, -0.5, 0, 0.5, 1, 1.5];
y = f(x);
xx = linspace(-1, 1.5, 100);

% 3. Calculate the deBoor spline
y_deBoor = spline(x, y, xx);

% 4. Calculate the Complete spline
% We attach the derivative of the first point to the start of 'y',
% and the derivative of the last point to the end of 'y'.
df_start = df(x(1));
df_end = df(x(end));
y_complete = spline(x, [df_start, y, df_end], xx);

% 5. Plot the results
figure(2);
plot(x, y, 'ko', 'MarkerSize', 8, 'MarkerFaceColor', 'k'); hold on;
plot(xx, f(xx), 'k-', 'LineWidth', 2);
plot(xx, y_deBoor, 'b--', 'LineWidth', 2);
plot(xx, y_complete, 'r-.', 'LineWidth', 2);
legend('Nodes', 'Exact f(x)', 'deBoor Spline', 'Complete Spline');
title('Exercise 2: Cubic Splines Comparison');
grid on;
hold off;

% --- Exercise 3 ---
% 1. Input the given data
x_data = [0.5, 1.5, 2, 3, 3.5, 4.5, 5, 6, 7, 8];
y_data = [5, 5.8, 5.8, 6.8, 6.9, 7.6, 7.8, 8.2, 9.2, 9.9];

% 2. Find the linear least squares approximation (Degree = 1)
% polyfit returns the coefficients of the line: [a, b]
p_least_squares = polyfit(x_data, y_data, 1);

% Create smooth points for the line
xx_data = linspace(0, 9, 2);
yy_data = polyval(p_least_squares, xx_data);

% 3. Compute the error
% We evaluate the polynomial exactly at our x_data points to see how far off it is
y_approx = polyval(p_least_squares, x_data);
error_least_squares = sum((y_data - y_approx).^2);
fprintf('Total Error (Sum of Squares): %f\n', error_least_squares);

% 4. Estimate the value at x = 4
estimate_at_4 = polyval(p_least_squares, 4);
fprintf('Estimated value at x = 4: %f\n', estimate_at_4);

% 5. Plot the data and the approximation
figure(3);
plot(x_data, y_data, 'ko', 'MarkerSize', 8, 'MarkerFaceColor', 'k'); hold on;
plot(xx_data, yy_data, 'r-', 'LineWidth', 2);
plot(4, estimate_at_4, 'b*', 'MarkerSize', 10, 'LineWidth', 2); % Star to show our estimate
legend('Actual Data', 'Least Squares Fit', 'Estimate at x=4', 'Location', 'northwest');
title('Exercise 3: Least Squares Data Fitting');
grid on;
hold off;
