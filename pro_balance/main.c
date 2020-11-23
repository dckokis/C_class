#include <assert.h>
#include <stdio.h>
#define N 100
#include "stack.h"

// можно сделать массив флажков, на j место ставить либо 0 либо 1.
///* Функция возвращает 1, если скобочное выражение корректно, или 0 в противном случае. *///

int check_brackets(char *expression) {
    char *open_bracket = "([{<";
    char *closed_bracket = ")]}>";

    Stack brackets_stack;
    stack_create(&brackets_stack);

    for (int i = 0; i < sizeof(expression); ++i) {
        for(int j = 0; j < 4; j++) {
            if (expression + i * sizeof(char) == open_bracket + j * sizeof(char) || expression + i * sizeof(char) == closed_bracket + j * sizeof(char)){
                stack_push(&brackets_stack, expression + i * sizeof(char));
            }
        }
    }
    for(int j = 0; j < 4; j++) {
        if (stack_peek(&brackets_stack) == open_bracket + j * sizeof(char)){
            return 0;
        }
    }
    int flag[4] = {0}; // 1 ) 2 ] 3 } 4 >
    for (int i = 0; i < stack_size(&brackets_stack); i++) {
        for(int j = 0; j < 4; j++) {
            if (stack_pop(&brackets_stack) == closed_bracket + j * sizeof(char)) {
                flag[j]++;
                stack_pop(&brackets_stack);
            } else if (stack_pop(&brackets_stack) == open_bracket + j * sizeof(char)) {
                flag[j]--;
                stack_pop(&brackets_stack);
            }
        }
    }
    if (flag[0] == 0 && flag[1] == 0 && flag[2] == 0 && flag[3] == 0) return 1;
    else return 0;
}
int main() {
    char *expression;
    scanf("%s", &expression);
    printf("%d\n", check_brackets(expression));
    return 0;
}