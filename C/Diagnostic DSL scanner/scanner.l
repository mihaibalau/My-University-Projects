%{
#include <stdio.h>
#include <string.h>

int line = 1;
%}

%%

SCAN_VEHICLE            { printf("KEYWORD: SCAN_VEHICLE\n"); }
READ                    { printf("KEYWORD: READ\n"); }
MONITOR                 { printf("KEYWORD: MONITOR\n"); }
WARN_IF                 { printf("KEYWORD: WARN_IF\n"); }
ERROR_IF                { printf("KEYWORD: ERROR_IF\n"); }
List                    { printf("KEYWORD: List\n"); }
if                      { printf("KEYWORD: if\n"); }
else                    { printf("KEYWORD: else\n"); }
end                     { printf("KEYWORD: end\n"); }
for                     { printf("KEYWORD: for\n"); }
in                      { printf("KEYWORD: in\n"); }
print                   { printf("KEYWORD: print\n"); }
and                     { printf("KEYWORD: and\n"); }

"=="                    { printf("OPERATOR: ==\n"); }
"!="                    { printf("OPERATOR: !=\n"); }
">="                    { printf("OPERATOR: >=\n"); }
"<="                    { printf("OPERATOR: <=\n"); }
">"                     { printf("OPERATOR: >\n"); }
"<"                     { printf("OPERATOR: <\n"); }
"="                     { printf("ASSIGN: =\n"); }
"+"                     { printf("OPERATOR: +\n"); }
"-"                     { printf("OPERATOR: -\n"); }
"->"                    { printf("OPERATOR: ->\n"); }
"?"                     { printf("OPERATOR: ?\n"); }
":"                     { printf("OPERATOR: :\n"); }

"("                     { printf("SEPARATOR: (\n"); }
")"                     { printf("SEPARATOR: )\n"); }
"["                     { printf("SEPARATOR: [\n"); }
"]"                     { printf("SEPARATOR: ]\n"); }
"{"                     { printf("SEPARATOR: {\n"); }
"}"                     { printf("SEPARATOR: }\n"); }
","                     { printf("SEPARATOR: ,\n"); }

\"[a-zA-Z0-9_ ]*\"       { printf("STRING: %s\n", yytext); }
0|[-]?[1-9][0-9]*        { printf("NUMBER: %s\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]*   { printf("IDENTIFIER: %s\n", yytext); }

\n                      { line++; }         
[ \t\r]+                ;                  
.                       { printf("LEXICAL ERROR (line %d): %s\n", line, yytext); }

%%

int main(void) {
    yylex();
    return 0;
}
