%{
#include <stdio.h>
int count = 0;
%}

%%
[a-zA-Z0-9_]{11,}   { count++; printf("%.10s ", yytext); }  
[a-zA-Z0-9_]+       { printf("%s ", yytext); }  
\n                  { printf("\n"); }
.                   { printf("%s", yytext); }   

%%

int main() {
    printf("Enter text:\n");
    yylex();
    printf("\nTotal words longer than 10 chars: %d\n", count);
    return 0;
}

int yywrap() { return 1; }
