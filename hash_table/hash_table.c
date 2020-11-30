#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash_table.h"

///* Jenkins Hash Function *///
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

///* Инициализировать таблицу.
///* size - размер базового массива;
/// * hf   - хеш-функция;
/// * dtor - деструктор. Этой функции будут передаваться data удаляемых элементов
/// * (ht_destroy, ht_delete, а также при перезаписи элементов в ht_set).
/// * Если hf=0, берется стандартная функция (Дженкинс).
/// * Если dtor=0, деструктор отсутствует (не будет вызываться).
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

///* Уничтожить таблицу *///
void ht_destroy(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i]->key == NULL) {
            break;
        } else {
            free(ht->table[i]->data);
            //ht->dtor(ht->table[i]->data);
//            ht->table[i]->data = NULL;
//            ht->table[i]->key = NULL;
            int j = 0;
            List *current = ht->table[j]->next;
            while (current->next->key != NULL && j < ht->size) {
                free(current->next->data);
                //ht->dtor(current->next->data);
//                current->next->data = NULL;
//                current->next->key = NULL;
//                current->next->next = NULL;
                current = current->next;
                j++;
            }
        }
    }
    free(ht->table);
    ht->table = NULL;
    ht->size = -1;
}

///* Записать в таблицу соответствие key -> data. Если key уже существовал,
/// * соотв. поле data будет удалено (dtor) и перезаписано
Pointer ht_set(HashTable *ht, char *key, Pointer data) {
    unsigned hash = ht->hashfunc(key) % ht->size;
    if (ht->table[hash]->key == NULL) {
        ht->table[hash]->key = key;
        ht->table[hash]->data = data;
    } else if (ht->table[hash]->next->key == NULL) {
        ht->table[hash]->next->key = key;
        ht->table[hash]->next->data = data;
    } else {
        int i = 0;
        List *current = ht->table[hash]->next;
        while (current->next->key != NULL && i < ht->size) {
            current = current->next;
            i++;
        }
        if (current->next->key == NULL) {
            current->next->key = key;
            current->next->data = data;
        } else if (i >= ht->size) { //extend hash table
            size_t newsize = ht->size * 2;
            List **newtable = realloc(ht->table, newsize);
            if (newtable == NULL) {
                printf("Memory error");
                exit(1);
            }
            ht->table = newtable;
            ht->size = newsize;
            current->next->key = key;
            current->next->data = data;
        }
    }
    return ht;
}

///* Получить значение по ключу. Если ключа нет в таблице, вернуть 0. *///
Pointer ht_get(HashTable *ht, char *key) {
    unsigned hash = ht->hashfunc(key) % ht->size;
    if (ht->table[hash]->key == NULL) {
        return 0;
    } else if (strcmp(ht->table[hash]->key, key) == 0) {
        return ht->table[hash]->data;
    } else {
        int i = 0;
        List *current = ht->table[hash]->next;
        while (strcmp(ht->table[hash]->key, key) != 0 && i < ht->size) {
            current = current->next;
            i++;
        }
        if (strcmp(ht->table[hash]->key, key) == 0) {
            return ht->table[hash]->data;
        } else if (i >= ht->size) { // no such key in hash table
            return 0;
        }
    }
}

///* Проверка существования ключа key в таблице. 1 - есть, 0 - нет. *///
int ht_has(HashTable *ht, char *key) {
    unsigned hash = ht->hashfunc(key) % ht->size;
    if (ht->table[hash]->key == NULL) {
        return 0;
    } else if (strcmp(ht->table[hash]->key, key) == 0) {
        return 1;
    } else {
        int i = 0;
        List *current = ht->table[hash]->next;
        while (strcmp(current->next->key, key) != 0 && i < ht->size) {
            current = current->next;
            i++;
        }
        if (strcmp(current->next->key, key) == 0) {
            return 1;
        } else if (i >= ht->size) { // no such key in hash table
            return 0;
        }
    }
}

///* Удалить элемент с ключом key из таблицы (если он есть) *///
void ht_delete(HashTable *ht, char *key) {
    unsigned hash = ht->hashfunc(key) % ht->size;
    if (ht_has(ht, key)) ht->table[hash]->key = NULL;
}

///* Обход таблицы с посещением всех элементов. Функция f будет вызвана для
/// * всех пар (key, data) из таблицы *///
void ht_traverse(HashTable *ht, void (*f)(char *key, Pointer data)) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i]->key == NULL) {
            break;
        } else {
            f(ht->table[i]->key, ht->table[i]->data);
            int j = 0;
            List *current = ht->table[j]->next;
            while (current->next->key != NULL && j < ht->size) {
                f(current->next->key, current->next->data);
                current = current->next;
                j++;
            }
            if (current->next->key == NULL) {
                break;
            } else if (j >= ht->size) { // no such key in hash table
                break;
            }
        }
    }
}

///* Изменить размер базового массива.
/// * Примерный алгоритм: выделить новый массив table и перенести в него все
/// * существующие структуры List из старой table, затем старую освободить и
/// * заменить новой.
/// * Это эффективнее, чем создавать новую таблицу и делать в нее полноценные
/// * вставки.
void ht_resize(HashTable *ht, size_t new_size) {
    List **newtable = calloc(new_size, sizeof(struct List));
    if (newtable == NULL) {
        printf("Memory error");
        exit(1);
    }
    int not_null = 0;
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i]->key != NULL) not_null++;
    }
    if (not_null > new_size) {
        printf("Not enough space for this action. Please input bigger size. For example:" "%d", not_null);
        exit(1);
    } else {
        for (int i = 0; i < ht->size; i++) {
            if (ht->table[i]->key != NULL) {
                unsigned hash = ht->hashfunc(ht->table[i]->key);
                if (newtable[hash]->key == NULL) {
                    newtable[hash]->data = ht->table[i]->data;
                    newtable[hash]->key = ht->table[i]->key;
                } else {
                    int j = 0;
                    List *current = newtable[hash]->next;
                    while (current->next->key != NULL && j < new_size) {
                        current = current->next;
                        j++;
                    }
                    if (current->next->key == NULL) {
                        newtable[hash]->data = ht->table[i]->data;
                        newtable[hash]->key = ht->table[i]->key;
                    }

                }
            }
        }
        ht->size = new_size;
        free(ht->table);
        ht->table = newtable;
    }
}

