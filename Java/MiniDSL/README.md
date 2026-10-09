# MiniDSL

Parser side of the diagnostic language from the formal languages course. The Flex scanner for the same language is in `C/Diagnostic DSL scanner`.

`MiniDSL.g4` is the ANTLR 4 grammar. A program is a list of statements: `SCAN_VEHICLE ... READ error_codes|live_data|freeze_frame|readiness_status`, `MONITOR ... WARN_IF`, assignments, and `if` blocks closed by `end`. Conditions allow comparisons and `and` / `or`.

`Main.java` tokenizes a sample script by hand (keywords, numbers, strings, operators, line and column) and then feeds the same text to the generated ANTLR parser. `ProductionsVisitor.java` walks the parse tree and prints the production used at each node, so I could check that the grammar matched the script.

The generated lexer and parser classes are not included. ANTLR builds them from `MiniDSL.g4`.

Technologies: Java, ANTLR 4.
