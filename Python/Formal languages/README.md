# Formal languages

Two programs from the formal languages course, on top of the diagnostic DSL scanner in C and the ANTLR grammar in Java.

`grammar_to_dfa.py` builds deterministic automata for the two token classes of that language: identifiers and integer constants. Each automaton can be printed in the course format (states, transitions, start, accept) and then run on a string.

`ll1_parser.py` reads a grammar file and a token file. It computes FIRST and FOLLOW, fills the LL(1) table, and stops with the conflicting productions if the same cell is written twice. On an LL(1) grammar it parses the input and prints the production sequence. `grammar.txt` is the expression grammar (`E`, `T`, `F` with `+` and `*`) and `sequence.txt` is `id + id * id`.

```
python ll1_parser.py grammar.txt sequence.txt
```

Technologies: Python.
