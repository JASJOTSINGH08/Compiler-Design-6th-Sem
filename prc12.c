#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 10

void findOutFirst(char);
void findOutFollow(char);
void addToResultSet(char[], char);

int n;
char productions[MAX][MAX];
char first[MAX][MAX], follow[MAX][MAX];
int visitedFirst[MAX], visitedFollow[MAX];

int main() {
    int i;
    char startSymbol;

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter the productions :\n");
    for (i = 0; i < n; i++) {
        scanf("%s", productions[i]);
    }

    for (i = 0; i < MAX; i++) {
        first[i][0] = '\0';
        follow[i][0] = '\0';
        visitedFirst[i] = 0;
        visitedFollow[i] = 0;
    }

    for (i = 0; i < n; i++) {
        findOutFirst(productions[i][0]);
    }

    startSymbol = productions[0][0];
    addToResultSet(follow[startSymbol - 'A'], '$');

    for (i = 0; i < n; i++) {
        findOutFollow(productions[i][0]);
    }

    printf("\nFIRST Sets:\n");
    for (i = 0; i < n; i++) {
        printf("FIRST(%c): { %s }\n", productions[i][0], first[productions[i][0] - 'A']);
    }

    printf("\nFOLLOW Sets:\n");
    for (i = 0; i < n; i++) {
        printf("FOLLOW(%c): { %s }\n", productions[i][0], follow[productions[i][0] - 'A']);
    }

    return 0;
}

void findOutFirst(char c) {
    if (visitedFirst[c - 'A']) return;
    visitedFirst[c - 'A'] = 1;

    if (!isupper(c)) {
        addToResultSet(first[c - 'A'], c);
        return;
    }

    for (int i = 0; i < n; i++) {
        if (productions[i][0] == c) {
            char next = productions[i][2];
            if (!isupper(next)) {
                addToResultSet(first[c - 'A'], next);
            } else {
                findOutFirst(next);
                strcat(first[c - 'A'], first[next - 'A']);
            }
        }
    }
}

void findOutFollow(char c) {
    if (visitedFollow[c - 'A']) return;
    visitedFollow[c - 'A'] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 2; j < strlen(productions[i]); j++) {
            if (productions[i][j] == c) {
                if (productions[i][j + 1] != '\0') {
                    findOutFirst(productions[i][j + 1]);
                    strcat(follow[c - 'A'], first[productions[i][j + 1] - 'A']);
                }
                if (productions[i][j + 1] == '\0' || strchr(first[productions[i][j + 1] - 'A'], 'ε')) {
                    findOutFollow(productions[i][0]);
                    strcat(follow[c - 'A'], follow[productions[i][0] - 'A']);
                }
            }
        }
    }
}

void addToResultSet(char result[], char val) {
    if (strchr(result, val) == NULL) {
        int len = strlen(result);
        result[len] = val;
        result[len + 1] = '\0';
    }
}
