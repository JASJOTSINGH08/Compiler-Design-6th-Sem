%{
#include <stdio.h>
%}

DIGIT   [0-9]
ID      [a-zA-Z_][a-zA-Z0-9_]*
OP      [+\-*/=<>!&|^%]+
STR     \"(\\.|[^\"])*\"

%%

{DIGIT}+    { printf("NUMBER: %s\n", yytext); }
{ID}        { printf("IDENTIFIER: %s\n", yytext); }
{OP}        { printf("OPERATOR: %s\n", yytext); }
{STR}       { printf("STRING: %s\n", yytext); }
[\n\t ]+    { /* Ignore spaces and newlines */ }
.           { printf("UNKNOWN: %s\n", yytext); }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() { return 1; }
