#include <stdio.h>
#include <string.h>

char terminals[] = {'i', '+', '*', '(', ')', '$'};
char nonTerminals[] = {'E', 'T', 'F'};
char table[6][6];
char stack[100], input[100];
int FirstVT[3][6], LastVT[3][6];

int idx(char c) {
    if (c == 'i') return 0;
    if (c == '+') return 1;
    if (c == '*') return 2;
    if (c == '(') return 3;
    if (c == ')') return 4;
    if (c == '$') return 5;
    return -1;
}

int nt_idx(char c) {
    if (c == 'E') return 0;
    if (c == 'T') return 1;
    if (c == 'F') return 2;
    return -1;
}

void init_table() {
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            table[i][j] = ' ';
    table[0][1] = '>'; table[0][2] = '>'; table[0][4] = '>'; table[0][5] = '>';
    table[1][0] = '<'; table[1][1] = '>'; table[1][2] = '<'; table[1][3] = '<'; table[1][4] = '>'; table[1][5] = '>';
    table[2][0] = '<'; table[2][1] = '>'; table[2][2] = '>'; table[2][3] = '<'; table[2][4] = '>'; table[2][5] = '>';
    table[3][0] = '<'; table[3][1] = '<'; table[3][2] = '<'; table[3][4] = '=';
    table[4][1] = '>'; table[4][2] = '>'; table[4][4] = '>'; table[4][5] = '>';
    table[5][0] = '<'; table[5][1] = '<'; table[5][2] = '<'; table[5][3] = '<';
}

void init_sets() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 6; j++)
            FirstVT[i][j] = LastVT[i][j] = 0;
    FirstVT[0][0] = FirstVT[0][3] = 1;
    FirstVT[1][0] = FirstVT[1][3] = 1;
    FirstVT[2][0] = FirstVT[2][3] = 1;
    LastVT[0][0] = LastVT[0][4] = 1;
    LastVT[1][0] = LastVT[1][4] = 1;
    LastVT[2][0] = LastVT[2][4] = 1;
}

void print_table() {
    printf("Precedence Table:\n  ");
    for (int i = 0; i < 6; i++) printf("%c ", terminals[i]);
    printf("\n");
    for (int i = 0; i < 6; i++) {
        printf("%c ", terminals[i]);
        for (int j = 0; j < 6; j++)
            printf("%c ", table[i][j] == ' ' ? '.' : table[i][j]);
        printf("\n");
    }
}

void print_sets() {
    printf("\nFirstVT Sets:\n");
    for (int i = 0; i < 3; i++) {
        printf("FirstVT(%c): { ", nonTerminals[i]);
        int first = 1;
        for (int j = 0; j < 6; j++)
            if (FirstVT[i][j]) {
                if (!first) printf(", ");
                printf("%c", terminals[j]);
                first = 0;
            }
        printf(" }\n");
    }
    printf("\nLastVT Sets:\n");
    for (int i = 0; i < 3; i++) {
        printf("LastVT(%c): { ", nonTerminals[i]);
        int first = 1;
        for (int j = 0; j < 6; j++)
            if (LastVT[i][j]) {
                if (!first) printf(", ");
                printf("%c", terminals[j]);
                first = 0;
            }
        printf(" }\n");
    }
}

void parse() {
    int top = 0, i = 0;
    stack[top] = '$';
    strcat(input, "$");
    printf("\n%-20s %-20s %-10s\n", "STACK", "INPUT", "ACTION");
    while (1) {
        char a = stack[top], b = input[i];
        int x = idx(a), y = idx(b);
        printf("%-20s %-20s ", stack, input + i);
        if (a == '$' && b == '$') {
            printf("ACCEPT\n");
            break;
        }
        if (table[x][y] == '<' || table[x][y] == '=') {
            stack[++top] = b;
            i++;
            printf("SHIFT\n");
        } else if (table[x][y] == '>') {
            while (top > 0 && stack[top] != '<') top--;
            if (top > 0) top--;
            printf("REDUCE\n");
        } else {
            printf("REJECT\n");
            break;
        }
    }
}

int main() {
    init_table();
    init_sets();
    print_table();
    print_sets();
    printf("\nEnter input string: ");
    scanf("%s", input);
    parse();
    return 0;
}