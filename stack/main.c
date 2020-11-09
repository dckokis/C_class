#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef struct tStack {
    unsigned lenght;
    unsigned capacity;
    int *arr;
} Stack;

typedef void *Pointer;

/* Создать пустой стек */
void stack_create(Stack *pstack){
    pstack->lenght = 0;
    pstack->capacity = 1;
    pstack->arr = malloc(pstack->capacity*sizeof(int));
    if (pstack->arr == NULL){
        printf("Memory error\n");
        exit(1);
    }
}

/* Уничтожить стек, освободив выделенную память */
void stack_destroy(Stack *pstack){
    free(pstack->arr);
    pstack->lenght = -1;
    pstack->capacity = -1;
}

/* Поместить значение value на вершину стека */
void stack_push(Stack *pstack, Pointer value){
    if (pstack->lenght == pstack->capacity) {
        // extend stack
        unsigned newcapacity = pstack->capacity * 2;
        int *newarr = realloc(pstack->arr,newcapacity * sizeof(Pointer));
        if (newarr == NULL) {
            printf("Memory error\n");
            exit(1);
        }
        pstack->arr = newarr;
        pstack->capacity = newcapacity;
    }
    // adding element
    pstack->arr[(pstack->lenght)++] = (int) value;
}

/* Возвращает количество элементов в стеке (0, если стек пуст) */
size_t stack_size(Stack *pstack){
    return pstack->lenght;
}

/* Снять значение с вершины стека. Если стек пуст, возвращает 0 */
Pointer stack_pop(Stack *pstack) {
    if (pstack->lenght == 0) return 0;
    Pointer peek = (Pointer) pstack->arr[pstack->lenght - 1]; // сперва говорим ччто peek это указатель на элемент,
    // потом его зануляем, это норм?
    //pstack->arr[pstack->lenght - 1] = ; чему нужно приравнивать чтоы удалить?
    pstack->lenght--;
    return peek;
}

/*
 * Возвращает значение с вершины стека, не удаляя его из стека.
 * Если стек пуст, возвращает 0
 */
Pointer stack_peek(Stack *pstack) {
    if (pstack->lenght == 0) return 0;
    //Pointer peek = (Pointer) pstack->arr[pstack->lenght - 1];
    return (Pointer) pstack->arr[pstack->lenght - 1];
}

int main() {
    { //test stack_peek with strings
        Stack test_stack;
        stack_create(&test_stack);
        stack_push(&test_stack, "abc");
        stack_push(&test_stack, "def");
        stack_push(&test_stack, "ghi");
        assert(strcmp(stack_peek(&test_stack), "ghi") == 0);
        stack_destroy(&test_stack);
    }
    { //test stack_peek with int
        Stack test_stack;
        stack_create(&test_stack);
        stack_push(&test_stack, (Pointer) 58);
        assert((int) stack_peek(&test_stack) == 58);
        stack_destroy(&test_stack);
    }
    { //test stack_pop and stack_size
        Stack test_stack;
        stack_create(&test_stack);
        stack_push(&test_stack, "abc");
        stack_push(&test_stack, "def");
        stack_push(&test_stack, "ggg");
        stack_pop(&test_stack);
        assert(strcmp(stack_peek(&test_stack), "def") == 0);
        assert(stack_size(&test_stack) == 2);
        stack_destroy(&test_stack);
    }
    { //test stack_size and stack_destroy
        Stack test_stack;
        stack_create(&test_stack);
        stack_push(&test_stack, "abc");
        stack_push(&test_stack, "def");
        stack_push(&test_stack, "ggg");
        assert(stack_size(&test_stack) == 3);
        stack_destroy(&test_stack);
        assert(stack_size(&test_stack) == -1);
    }
    return 0;
}