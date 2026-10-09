f  = @(x) 1 ./ (1 + x);
fp = @(x) -1 ./ (1 + x).^2;


# 1 a)

x = [0; 1; 2];
y = f(x);
D = divdiff_simple(x, y)


# 1 b)

x  = [0; 1; 2];
y  = f(x);
yp = fp(x);
[z, H] = divdiff_hermite(x, y, yp)

# 1 c)

x  = linspace(1, 2, 11).';
y  = f(x);
yp = fp(x);

D11 = divdiff_simple(x, y)

[z11, H11] = divdiff_hermite(x, y, yp)


# 2 a)

x = [-2; -1; 0; 1; 2; 3; 4];
y = [-5; 1; 1; 1; 7; 25; 60];


Ddata = divdiff_simple(x, y)


# 2 b)

Fdata = forward_diff(y)


# 3 c)

Bdata = backward_diff(y)

