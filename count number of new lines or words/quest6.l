%{
int line_count = 0, a_word_count = 0;
%}

%%

\n      { line_count++; }
[aA][a-zA-Z]* { a_word_count++; }
.       { }

%%

int main() {
    yylex();
    printf("New lines: %d\n", line_count);
    printf("Words starting with 'a': %d\n", a_word_count);
    return 0;
}

int yywrap() { return 1; }
