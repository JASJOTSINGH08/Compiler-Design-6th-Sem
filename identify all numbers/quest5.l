%%
[0-9]+ { printf("Number found: %s\n", yytext); }
.|\n  { }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() { return 1; }
