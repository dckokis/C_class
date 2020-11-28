#include <assert.h>
#include <stdio.h>
#include <string.h>
#define N 100
#include "stack.h"


///* Функция возвращает 1, если скобочное выражение корректно, или 0 в противном случае. *///
int check_brackets(char *expression, size_t lenght) {
    char *open_bracket = "([{<";
    char *closed_bracket = ")]}>";

    Stack brackets_stack;
    stack_create(&brackets_stack);

    for (int i = 0; i < lenght; ++i) {
        for(int j = 0; j < 4; j++) {
            if (*(expression) == *(closed_bracket + j)) { // if expression starts with open bracket it is incorrect
                stack_destroy(&brackets_stack);
                return 0;
            } else if (*(expression + i) == *(open_bracket + j)){ // if current char is open bracket push it to stack
                stack_push(&brackets_stack, expression + i);
                break;
            } else if (*(expression + i) == *(closed_bracket + j)) {
                if (*(char *)stack_peek(&brackets_stack) == *(open_bracket + j)) { // if the last open bracket is paired with current closed bracket pop it from stack peek
                    stack_pop(&brackets_stack);
                    break;
                }
            }
        }
    }
    if (stack_size(&brackets_stack) == 0){
        stack_destroy(&brackets_stack);
        return 1;
    } else {
        stack_destroy(&brackets_stack);
        return 0;
    }

}
int main() {
    char *expression = malloc(N);
    gets_s(expression, N);
    size_t len = strlen(expression);
    printf("%d\n", check_brackets(expression, len));
    return 0;
}