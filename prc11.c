#include <stdio.h>
#include <string.h>

#define SUCCESS 1
#define FAILURE 0

int E(), Edash(), T(), Tdash(), F();

const char *cursor;
char string[64];

int main() {
    printf("Enter String: ");
    scanf("%s", string);
    cursor = string;
    printf("\nInput          Action\n");

    if (E() && *cursor == '\0') {
        printf("\n");
        printf("String parsed\n");
        return 0;
    } else {
        printf("\n");
        printf("Error parsing\n");
        return 1;
    }
}

int E() {
    printf("%-16s E -> T E'\n", cursor);
    if (T()) {
        if (Edash()) {
            return 1;
        }
    }
    return 0;
}

int Edash() {
    if (*cursor == '+') {
        printf("%-16s E' -> + T E'\n", cursor);
        cursor++;
        if (T() && Edash()) {
            return 1;
        }
        return 0;
    } else if (*cursor == '-') {
        printf("%-16s E' -> - T E'\n", cursor);
        cursor++;
        if (T() && Edash()) {
            return 1;
        }
        return 0;
    } else {
        printf("%-16s E' -> $\n", cursor);
        return 1;
    }
}

int T() {
    printf("%-16s T -> F T'\n", cursor);
    if (F()) {
        if (Tdash()) {
            return 1;
        }
    }
    return 0;
}

int Tdash() {
    if (*cursor == '*' || *cursor == '/') {
        printf("%-16s T' -> %c F T'\n", cursor, *cursor);
        cursor++;
        if (F() && Tdash()) {
            return 1;
        }
        return 0;
    } else {
        printf("%-16s T' -> $\n", cursor);
        return 1;
    }
}

int F() {
    if (*cursor == '(') {
        printf("%-16s F -> ( E )\n", cursor);
        cursor++;
        if (E() && *cursor == ')') {
            cursor++;
            return 1;
        }
        return 0;
    } else if (*cursor == 'i') {
        printf("%-16s F -> i\n", cursor);
        cursor++;
        return 1;
    }
    return 0;
}
