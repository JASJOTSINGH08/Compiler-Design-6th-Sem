#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SHIFT 1
#define REDUCE 2
#define ACCEPT 3
#define ERROR 4

char stack[50];
int stack_top = -1;
int state_stack[50];
char input_str[30];

void push_char(char c) {
    stack[++stack_top] = c;
}

char pop_char() {
    if (stack_top >= 0)
        return stack[stack_top--];
    return '\0';
}

void display_stack() {
    printf("\n\t\t\t $");
    for (int i = 0; i <= stack_top; i++)
        printf("%c", stack[i]);
}

int get_terminal_idx(char c) {
    switch (c) {
        case 'i': return 0;
        case '+': return 1;
        case '*': return 2;
        case '(': return 3;
        case ')': return 4;
        case '$': return 5;
        default: return -1;
    }
}

typedef struct {
    int action_type;
    int next_state;
} ParseEntry;

ParseEntry parse_table[12][6];
int goto_table[12][3];

void init_tables() {
    int i, j;
    for (i = 0; i < 12; i++)
        for (j = 0; j < 6; j++)
            parse_table[i][j] = (ParseEntry){ERROR, -1};

    for (i = 0; i < 12; i++)
        for (j = 0; j < 3; j++)
            goto_table[i][j] = 0;

    parse_table[0][0] = (ParseEntry){SHIFT, 5};
    parse_table[0][3] = (ParseEntry){SHIFT, 4};
    parse_table[1][1] = (ParseEntry){SHIFT, 6};
    parse_table[1][5] = (ParseEntry){ACCEPT, -1};
    parse_table[2][1] = (ParseEntry){REDUCE, 2};
    parse_table[2][2] = (ParseEntry){SHIFT, 7};
    parse_table[2][4] = (ParseEntry){REDUCE, 2};
    parse_table[2][5] = (ParseEntry){REDUCE, 2};
    parse_table[3][1] = (ParseEntry){REDUCE, 4};
    parse_table[3][2] = (ParseEntry){REDUCE, 4};
    parse_table[3][4] = (ParseEntry){REDUCE, 4};
    parse_table[3][5] = (ParseEntry){REDUCE, 4};
    parse_table[4][0] = (ParseEntry){SHIFT, 5};
    parse_table[4][3] = (ParseEntry){SHIFT, 4};
    parse_table[5][1] = (ParseEntry){REDUCE, 6};
    parse_table[5][2] = (ParseEntry){REDUCE, 6};
    parse_table[5][4] = (ParseEntry){REDUCE, 6};
    parse_table[5][5] = (ParseEntry){REDUCE, 6};
    parse_table[6][0] = (ParseEntry){SHIFT, 5};
    parse_table[6][3] = (ParseEntry){SHIFT, 4};
    parse_table[7][0] = (ParseEntry){SHIFT, 5};
    parse_table[7][3] = (ParseEntry){SHIFT, 4};
    parse_table[8][1] = (ParseEntry){SHIFT, 6};
    parse_table[8][4] = (ParseEntry){SHIFT, 11};
    parse_table[9][1] = (ParseEntry){REDUCE, 1};
    parse_table[9][2] = (ParseEntry){SHIFT, 7};
    parse_table[9][4] = (ParseEntry){REDUCE, 1};
    parse_table[9][5] = (ParseEntry){REDUCE, 1};
    parse_table[10][1] = (ParseEntry){REDUCE, 3};
    parse_table[10][2] = (ParseEntry){REDUCE, 3};
    parse_table[10][4] = (ParseEntry){REDUCE, 3};
    parse_table[10][5] = (ParseEntry){REDUCE, 3};
    parse_table[11][1] = (ParseEntry){REDUCE, 5};
    parse_table[11][2] = (ParseEntry){REDUCE, 5};
    parse_table[11][4] = (ParseEntry){REDUCE, 5};
    parse_table[11][5] = (ParseEntry){REDUCE, 5};

    goto_table[0][0] = 1;
    goto_table[0][1] = 2;
    goto_table[0][2] = 3;
    goto_table[4][0] = 8;
    goto_table[4][1] = 2;
    goto_table[4][2] = 3;
    goto_table[6][1] = 9;
    goto_table[6][2] = 3;
    goto_table[7][2] = 10;
}

void parse_input() {
    int input_pos = 0;
    int state_top = 0;
    state_stack[0] = 0;
    push_char('$');

    while (1) {
        int current_state = state_stack[state_top];
        char current_input = input_str[input_pos];
        int term_idx = get_terminal_idx(current_input);

        if (term_idx == -1) {
            printf("error");
            break;
        }

        ParseEntry entry = parse_table[current_state][term_idx];

        display_stack();
        printf("\t\t%s\t\t", &input_str[input_pos]);

        if (entry.action_type == SHIFT) {
            push_char(current_input);
            state_stack[++state_top] = entry.next_state;
            input_pos++;
            printf("shift %d", entry.next_state);
        }
        else if (entry.action_type == REDUCE) {
            int pop_count;
            char non_term;
            switch (entry.next_state) {
                case 1: pop_count = 3; non_term = 'E'; break; // E -> E + T
                case 2: pop_count = 1; non_term = 'E'; break; // E -> T
                case 3: pop_count = 3; non_term = 'T'; break; // T -> T * F
                case 4: pop_count = 1; non_term = 'T'; break; // T -> F
                case 5: pop_count = 3; non_term = 'F'; break; // F -> ( E )
                case 6: pop_count = 1; non_term = 'F'; break; // F -> i
                default: printf("error"); return;
            }
            for (int i = 0; i < pop_count; i++) {
                pop_char();
                if (state_top > 0) state_top--;
            }
            push_char(non_term);
            int goto_idx = non_term == 'E' ? 0 : non_term == 'T' ? 1 : 2;
            int next_state = goto_table[state_stack[state_top]][goto_idx];
            if (next_state == 0 && state_top != 0) {
                printf("error");
                break;
            }
            state_stack[++state_top] = next_state;
            printf("reduce %d", entry.next_state);
        }
        else if (entry.action_type == ACCEPT) {
            printf("accept");
            break;
        }
        else {
            printf("error");
            break;
        }
    }
    printf("\n");
}

int main() {
    char user_input[30];
    printf("\n\nLR PARSING\nENTER THE EXPRESSION: ");
    scanf("%s", user_input);
    strcpy(input_str, user_input);
    strcat(input_str, "$");
    init_tables();
    parse_input();
    return 0;
}