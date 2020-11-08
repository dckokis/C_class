#include <stdio.h>
typedef struct tStack {
    /* ... */
} Stack;

typedef void *Pointer;

/* Создать пустой стек */
void stack_create(Stack *pstack);

/* Уничтожить стек, освободив выделенную память */
void stack_destroy(Stack *pstack);

/* Поместить значение value на вершину стека */
void stack_push(Stack *pstack, Pointer value);

/* Возвращает количество элементов в стеке (0, если стек пуст) */
size_t stack_size(Stack *pstack);

/* Снять значение с вершины стека. Если стек пуст, возвращает 0 */
Pointer stack_pop(Stack *pstack);

/*
 * Возвращает значение с вершины стека, не удаляя его из стека.
 * Если стек пуст, возвращает 0
 */
Pointer stack_peek(Stack *pstack);
int main() {
    return 0;
}
