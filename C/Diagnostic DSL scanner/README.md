# Diagnostic DSL scanner

Lexical analysis for a small language I designed in the formal languages course. The programs look like diagnostic scripts for a car: scan a vehicle, read error codes or live data, and raise a warning when a condition holds.

`scanner.l` is a Flex specification. It classifies keywords (`SCAN_VEHICLE`, `MONITOR`, `WARN_IF`, `if`, `for`), operators, strings and numbers, and it reports a lexical error with the line number when a character does not fit. Whitespace is skipped.

`symbol_table.c` keeps identifiers in a binary search tree. Insert ignores a name that is already there and search returns the position assigned at the first insert, which is what a later phase needs when the same name shows up again.

The same language has an ANTLR grammar and a handwritten Java scanner in `Java/MiniDSL`.

Technologies: C, Flex.
