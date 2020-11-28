#include <assert.h>
#include <stdio.h>
#include <string.h>
#define N 100
#include "stack.h"


///* Функция возвращает 1, если скобочное выражение корректно, или 0 в противном случае. *///
// кладем открывающую скобку на стек, смотрим закрывающую, снимаем элемент, смотрим парные или нет
// (()[]{>
// в конце смотрим пустой ли стек
int check_brackets(char *expression, size_t lenght) {
    char *open_bracket = "([{<";
    char *closed_bracket = ")]}>";

    Stack brackets_stack;
    stack_create(&brackets_stack);
    for (int i = 0; i < lenght; ++i) {
        for(int j = 0; j < 4; j++) {
            if ((expression + i) == (open_bracket + j)){
                stack_push(&brackets_stack, expression + i);
            } else if ((expression + i) == (closed_bracket + j)) {
                if (stack_peek(&brackets_stack) == open_bracket + j) {
                    stack_pop(&brackets_stack);
                } else break;
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
    char *expression = malloc(100);
    gets_s(expression, N);
    size_t len = strlen(expression);
    printf("%d\n", check_brackets(expression, len));
    return 0;
}