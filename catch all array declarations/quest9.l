%{
FILE *fptr;
%}

%%
int|float|char|double[ \t]*[a-zA-Z_][a-zA-Z0-9_]*\[.*\] { 
    fptr = fopen("arrays.txt", "a");
    fprintf(fptr, "Array Declaration: %s\n", yytext);
    fclose(fptr);
}
int|float|char|double[ \t]+[a-zA-Z_][a-zA-Z0-9_]*(,[ \t]*[a-zA-Z_][a-zA-Z0-9_]*)+ { 
    fptr = fopen("arrays.txt", "a");
    fprintf(fptr, "Multiple Declaration: %s\n", yytext);
    fclose(fptr);
}
.|\n { }

%%

int main() {
    yylex();
    return 0;
}

int yywrap() { return 1; }
