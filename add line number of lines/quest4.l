%{
int line = 1;
%}

%%
\n      { printf(" (%d)\n", line++); } 
.       { printf("%s", yytext); }     

%%

int main() {
    yylex();
    return 0;
}

int yywrap() { return 1; }
