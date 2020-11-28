#include <stdlib.h>
#include <stdio.h>
#include "hash_table.h"


//Jenkins Hash Function
unsigned jenkins_one_at_a_time_hash(char *key) {
    unsigned hash = 0;

    for (; *key; ++key) {
        hash += *key;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

/* Инициализировать таблицу.
 *
 * size - размер базового массива;
 * hf   - хеш-функция;
 * dtor - деструктор. Этой функции будут передаваться data удаляемых элементов
 *        (ht_destroy, ht_delete, а также при перезаписи элементов в ht_set).
 *
 * Если hf=0, берется стандартная функция (Дженкинс).
 * Если dtor=0, деструктор отсутствует (не будет вызываться).
 */
void ht_init(HashTable *ht, size_t size, HashFunction hf, Destructor dtor) {
    ht->size = size;
    if (hf == 0) ht->hashfunc = jenkins_one_at_a_time_hash;
    ht->dtor = dtor;
    ht->table = calloc(size, sizeof(struct List));
    if (ht->table == NULL) {
        printf("Memory error\n");
        exit(1);
    }
}

/* Уничтожить таблицу */
void ht_destroy(HashTable *ht) {
    int i = 0;
    while (ht->table[i]->key) {
        ht->dtor(ht->table[i]->data);
        ht->table[i]->key = NULL;
    }
    for (i; i < ht->size; i++) {
        if (ht->table[i]->next->key) {
            ht->dtor(ht->table[i]->next->data);
            ht->table[i]->next->key = NULL;
        }
    }
    ht->table = NULL;
    ht->size = -1;
}

/* Записать в таблицу соответствие key -> data. Если key уже существовал,
 * соотв. поле data будет удалено (dtor) и перезаписано */
Pointer ht_set(HashTable *ht, char *key, Pointer data);

/* Получить значение по ключу. Если ключа нет в таблице, вернуть 0. */
Pointer ht_get(HashTable *ht, char *key);

/* Проверка существования ключа key в таблице. 1 - есть, 0 - нет. */
int ht_has(HashTable *ht, char *key);

/* Удалить элемент с ключом key из таблицы (если он есть) */
void ht_delete(HashTable *ht, char *key);

/* Обход таблицы с посещением всех элементов. Функция f будет вызвана для
 * всех пар (key, data) из таблицы */
void ht_traverse(HashTable *ht, void (*f)(char *key, Pointer data));

/* Изменить размер базового массива.
 *
 * Примерный алгоритм: выделить новый массив table и перенести в него все
 * существующие структуры List из старой table, затем старую освободить и
 * заменить новой.
 *
 * Это эффективнее, чем создавать новую таблицу и делать в нее полноценные
 * вставки.
 */
void ht_resize(HashTable *ht, size_t new_size);

