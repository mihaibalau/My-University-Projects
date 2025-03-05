
% a. Write a predicate to determine the difference of two sets.
% b. Write a predicate to add value 1 after every even element from a list.

member1(E, [E | _]).
member1(E, [_ | L]) :-
    member1(E, L).

difference([], _, []).
difference([H|L], B, R) :-
    member1(H, B),
    difference(L, B, R). 

difference([H|L], B, [H|R]) :-
    \+ member1(H, B),
    difference(L, B, R).


even([], []).
even([H|L], [H, 1|R]) :-
    H mod 2 =:= 0,
    even(L, R).

even([H|L], [H|R]) :-
    H mod 2 =\= 0, 
    even(L, R).