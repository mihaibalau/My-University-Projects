
% a. Write a predicate to determine the sum of two numbers written in list representation.
% b. For a heterogeneous list, formed from integer numbers and list of digits, write a predicate to compute the 
% sum of all numbers represented as sublists. 
% Eg.: [1, [2, 3], 4, 5, [6, 7, 9], 10, 11, [1, 2, 0], 6] => [8, 2, 2].

add(E, [], [E]). 
add(E, [H | T], [H | Rez]) :- 
	add(E, T, Rez).

inverse([], []). 
inverse([H | T], Rez) :- 
	inverse(T, L), 
	add(H, L, Rez).

% 									{ 0, empty list
%list_to_number (l1l2..ln, N, P) =  { N * P + list_to_number(l2..ln), else

% list_to_number (L: list, N: number formated with list elements, P: Number power) 
% (i, o, o) – deterministic

list_to_number([], 0, 1).
list_to_number([H|T], N, P) :-
    list_to_number(T, N1, P1),
    N is H * P1 + N1,
    P is P1 * 10.

% 									{ [], N = 0
%number_to_list (N, l1l2..ln) =  	{ N U number_to_list (l2..ln), else

% number_to_list (N: number, L: list created with number digits) 
% (i, o) – deterministic

number_to_list(0, []).
number_to_list(N, [D|L]) :-
    D is N mod 10,
    N1 is N // 10,
    number_to_list(N1, L).

% 									
%two_list_sum (l11l12..l1n, l21l22..l2n, l31l32..l3n) = l31l32..l3n

% two_list_sum (L1: First number as list, l2: Second number as list, L3: sum of that numbers as list) 
% (i, i, o) – deterministic

two_list_sum(L1, L2, R) :-
    list_to_number(L1, N1, P),
    list_to_number(L2, N2, P2),
    S is N1 + N2,
    number_to_list(S, R1),
	inverse(R1, R).

% 									{ R = 0, empty list
%list_sum (l1l2..ln, R) = 		 	{ list_to_number(H) + R, H - list
%									{ R, H not list

% list_sum (L: list, R - sum of the numbers represented as a sublist, returned as number, from the main list) 
% (i, o) – deterministic

list_sum([], 0).
list_sum([H|T], R) :-
    is_list(H),
	list_sum(T, R1),
    list_to_number(H, N, P),
	R is R1 + N.
list_sum([H|T], R) :-
    \+ is_list(H),
    list_sum(T, R).

% multi_list_sum(L: list, R: sum of the numbers represented as a sublist, returned as another list, from the main list
% (i, o) – deterministic

multi_list_sum(L, R) :-
    list_sum(L, S),
    number_to_list(S, R1),
    inverse(R1, R).

% two_list_sum([2, 2, 4], [3, 2, 1], R).
% multi_list_sum([1, [2, 3], 4, 5, [6, 7, 9], 10, 11, [1, 2, 0], 6], R).