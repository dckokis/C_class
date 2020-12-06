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
    ht->table = calloc(size, sizeof(struct List*));
    if (ht->table == NULL) {
        printf("Memory error\n");
        exit(1);
    }
}

///* Уничтожить таблицу *///
void ht_destroy(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i] == NULL) {
            break;
        } else {
            ht->dtor(ht->table[i]->head.data);
            int j = 0;
            ListNode *current = ht->table[j]->head.next;
            while (current->next->key != NULL && j < ht->size) {
                ht->dtor(current->next->data);
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
    List *list = ht->table[hash];
    if (list == NULL) {
        list = calloc(1, sizeof(struct ListNode));
        if (list == NULL) {
            printf("Memory error\n");
            exit(1);
        }
        ht->table[hash] = list;
        list->head.key = key;
        list->head.data = data;
        list->head.next = NULL;
    }else if (strcmp(list->head.key, key) == 0) {
        list->head.data = data;
    }
    else {
        ListNode *listnext = list->head.next;
        listnext = calloc(1, sizeof(struct ListNode));
        if (listnext == NULL) {
            printf("Memory error\n");
            exit(1);
        }
        list->head.next = listnext;
        listnext->key = key;
        listnext->data = data;
        listnext->next = NULL;
    }
    return ht;
}

///* Получить значение по ключу. Если ключа нет в таблице, вернуть 0. *///
Pointer ht_get(HashTable *ht, char *key) {
    unsigned hash = ht->hashfunc(key) % ht->size;
    List *list = ht->table[hash];
    if (list == NULL) {
        return 0;
    } else {
        if (strcmp(list->head.key, key) == 0) {
            return list->head.data;
        } else {
            ListNode *listnext = list->head.next;
            while (listnext != NULL) {
                listnext = listnext->next;
            }
            if (strcmp(listnext->key, key) == 0) {
                return listnext->data;
            } else {
                return 0;
            }
        }
    }
}

///* Проверка существования ключа key в таблице. 1 - есть, 0 - нет. *///
int ht_has(HashTable *ht, char *key) {
    unsigned hash = ht->hashfunc(key) % ht->size;
    List *list = ht->table[hash];
    if (list == NULL) {
        return 0;
    } else {
        if (strcmp(list->head.key, key) == 0) {
            return 1;
        } else {
            ListNode *listnext = list->head.next;
            while (listnext != NULL) {
                listnext = listnext->next;
            }
            if (strcmp(listnext->key, key) == 0) {
                return 1;
            } else {
                return 0;
            }
        }
    }
}

///* Удалить элемент с ключом key из таблицы (если он есть) *///
void ht_delete(HashTable *ht, char *key) {
    unsigned hash = ht->hashfunc(key) % ht->size;
    if (ht_has(ht, key)) ht->table[hash]->head.key = NULL;
}

///* Обход таблицы с посещением всех элементов. Функция f будет вызвана для
/// * всех пар (key, data) из таблицы *///
void ht_traverse(HashTable *ht, void (*f)(char *key, Pointer data)) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i]->head.key == NULL) {
            break;
        } else {
            f(ht->table[i]->head.key, ht->table[i]->head.data);
            int j = 0;
            ListNode *current = ht->table[j]->head.next;
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
        if (ht->table[i] != NULL) not_null++;
    }
    if (not_null > new_size) {
        printf("Not enough space for this action. Please input bigger size. For example:" "%d", not_null);
        exit(1);
    } else {
        for (int i = 0; i < ht->size; i++) {
            if (ht->table[i] != NULL) {
                unsigned hash = ht->hashfunc(ht->table[i]->head.key)%new_size;
                if (newtable[hash] == NULL) {
                    newtable[hash] = calloc(1, sizeof(struct ListNode));
                    if(newtable[hash] == NULL) {
                        printf("Memory error");
                        exit(1);
                    }
                    newtable[hash]->head.data = ht->table[i]->head.data;
                    newtable[hash]->head.key = ht->table[i]->head.key;
                } else {
                    int j = 0;
                    ListNode *current = newtable[hash]->head.next;
                    while (current->next->key != NULL && j < new_size) {
                        current = current->next;
                        j++;
                    }
                    if (current->next->key == NULL) {
                        newtable[hash]->head.data = ht->table[i]->head.data;
                        newtable[hash]->head.key = ht->table[i]->head.key;
                    }

                }
            }
        }
        ht->size = new_size;
        free(ht->table);
        ht->table = newtable;
    }
}

