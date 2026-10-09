A1 = [  2,  1, -1, -2;
        4,  4,  1,  3;
       -6, -1, 10, 10;
       -2,  1,  8,  4 ];

b1 = [2; 4; -5; 1];

x1_gauss = gauss_pivot(A1, b1)
x1_lup = solve_LUP(A1, b1)

