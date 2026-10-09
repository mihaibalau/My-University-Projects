grammar MiniDSL;

// START RULE
program: statement+ EOF;

// Statements
statement: scanStatement
         | monitorStatement
         | assignment
         | ifStatement
         | SEMICOLON
         ;

// SCAN
scanStatement: SCAN_VEHICLE identifier READ scanTarget;
scanTarget: 'error_codes' | 'live_data' | 'freeze_frame' | 'readiness_status';

// MONITOR
monitorStatement: MONITOR identifier WARN_IF condition;

// ASSIGNMENT
assignment: identifier ASSIGN expression;

// IF STATEMENT
ifStatement: IF condition statement* END;

// EXPRESSIONS
expression: listExpression
          | value
          ;

listExpression: LIST LPAREN LBRACKET listContent? RBRACKET RPAREN;
listContent: dictEntry (COMMA dictEntry)*;
dictEntry: LBRACE dictPair (COMMA dictPair)* RBRACE;
dictPair: identifier COLON value;

// CONDITIONS & COMPARISONS
condition: simpleCondition
         | condition AND condition
         | condition OR condition
         | LPAREN condition RPAREN
         ;

simpleCondition: comparableValue comparisonOp comparableValue;
comparableValue: identifier | value;
comparisonOp: EQ | NEQ | LT | GT | LTE | GTE;

// IDENTIFIERS & VALUES
identifier: IDENTIFIER;
value: NUMBER | STRING | identifier;

// KEYWORDS
SCAN_VEHICLE: 'SCAN_VEHICLE';
MONITOR: 'MONITOR';
WARN_IF: 'WARN_IF';
READ: 'READ';
IF: 'if';
END: 'end';
LIST: 'List';
AND: 'and';
OR: 'or';
PRINT: 'print';

// OPERATORS
ASSIGN: '=';
PLUS: '+';
MINUS: '-';
MUL: '*';
DIV: '/';

// COMPARISON OPERATORS
EQ: '==';
NEQ: '!=';
LT: '<';
GT: '>';
LTE: '<=';
GTE: '>=';

// DELIMITERS
LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';
LBRACKET: '[';
RBRACKET: ']';
COLON: ':';
COMMA: ',';
SEMICOLON: ';';
DOT: '.';

// LITERALS
IDENTIFIER: [a-zA-Z_][a-zA-Z0-9_]*;
NUMBER: '-'? [0-9]+;
STRING: '"' [a-zA-Z0-9_]* '"';

// WHITESPACE & COMMENTS
WS: [ \t\n\r]+ -> skip;
COMMENT: '//' ~[\n\r]* -> skip;
