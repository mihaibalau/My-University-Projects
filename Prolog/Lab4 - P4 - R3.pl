
% The list a1... an is given. Write a predicate to determine all sublists strictly ascending of this list a.

%					{ [], if n = 0
%	asc_sublist = 	{ l1, if n = 1
%					{ l1 U asc_sublist(l2l3..ln), if L1 < L2
%					{ asc_sublist(L2L3..Ln), otherwise

% asc_sublist(L: list, R: list)
% flow model: (i, o)
% L - list of possible elements
% R - resulting list as a combination of elemens in increasing order

asc_sublist([], []).

asc_sublist([H|T], [H]) :-
    asc_sublist(T, []).

asc_sublist([H|T], [H|R]) :-
    asc_sublist(T, [H1|R1]),
    H < H1,
    R = [H1|R1].

asc_sublist([_|T], R) :-
    asc_sublist(T, R).
	
% findall(R, asc_sublist([1,3,2,4,5,1,7], R), X).