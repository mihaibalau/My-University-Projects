function D = divdiff_simple(x, y)
  % x : column vector of nodes [x0; x1; ...; xn]
  % y : column vector of function values [f(x0); ...; f(xn)]
  % D : (n+1) x (n+1) table; first column is y, upper triangle are divided differences

  n = length(x);
  D = zeros(n, n);      % pre-allocate table
  D(:,1) = y(:);        % first column: function values

  % Build columns 2..n using the recursive formula
  for j = 2:n           % column index (order of divided difference + 1)
    for i = 1:(n-j+1)   % row index; goes only where the upper triangle exists
      D(i,j) = (D(i+1,j-1) - D(i,j-1)) / (x(i+j-1) - x(i));
    end
  end
end

function [z, H] = divdiff_hermite(x, y, yp)
  % x  : column vector of distinct nodes [x0; x1; ...; xn]
  % y  : column vector of function values f(xi)
  % yp : column vector of derivative values f'(xi)
  % z  : new grid with each node duplicated
  % H  : Hermite divided-difference table on z

  n = length(x);

  % Build duplicated grid z and first column
  z = zeros(2*n, 1);
  H = zeros(2*n, 2*n);

  for i = 1:n
    z(2*i-1) = x(i);
    z(2*i)   = x(i);
    H(2*i-1,1) = y(i);
    H(2*i,1)   = y(i);
  end

  % First-order differences: use derivatives on pairs from same node
  for i = 1:n
    H(2*i-1,2) = yp(i);  % f'(xi)
    H(2*i,2)   = (H(2*i+1,1) - H(2*i,1)) / (z(2*i+1) - z(2*i));
    % Note: for the last node, 2*i+1 does not exist, so we guard later
    if 2*i == 2*n
      H(2*i,2) = yp(i);  % for the last node, also use derivative
    end
  end

  % General divided differences for columns 3..2n
  for j = 3:(2*n)
    for i = 1:(2*n - j + 1)
      H(i,j) = (H(i+1,j-1) - H(i,j-1)) / (z(i+j-1) - z(i));
    end
  end
end

function B = backward_diff(y)
  % y : column vector of function values at equally spaced nodes
  % B : table of backward differences

  n = length(y);
  B = zeros(n, n);
  B(:,1) = y(:);

  for j = 2:n
    for i = n:-1:j
      B(i,j) = B(i,j-1) - B(i-1,j-1);
    end
  end
end

