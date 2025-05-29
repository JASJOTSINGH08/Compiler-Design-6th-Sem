%{
int count = 0;
%}

%%
[a-zA-Z0-9]+ { count++; }
\n { }
. { }

%%

int main() {
    yylex();
    printf("Total words: %d\n", count);
    return 0;
}

int yywrap() { return 1; }
