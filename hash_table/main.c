#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hash_table.h"
typedef struct Contact {
    char *phone;
    char *addr;
} Contact;

int main() {
    HashTable test_hash;
    ht_init(&test_hash, 10, 0, 0);
    ht_set(&test_hash, "Vasya", "333-45-67");
    Contact *pc = malloc(sizeof(Contact));
    if (pc == NULL) {
        printf("Memory error\n");
        exit(1);
    }
    pc->phone = "02";
    pc->addr = "Kutateladze";
    ht_set(&test_hash, "Police", pc);
    assert(ht_get(&test_hash, "Police") == pc);
    ht_set(&test_hash, "Ambulance", NULL);
    assert(strcmp(ht_get(&test_hash, "Vasya"), "333-45-67") == 0);
    Contact *pc2 = malloc(sizeof(Contact));
    if (pc2 == NULL) {
        printf("Memory error\n");
        exit(1);
    }
    pc2->phone = "911";
    pc2->addr = "NY";
    ht_set(&test_hash, "Police", pc2);
    assert(ht_get(&test_hash, "Police") == pc2);
    assert(ht_has(&test_hash, "Police"));
    assert(ht_get(&test_hash, "asdsrfdgf") == 0);
    assert(test_hash.size == 10);
    ht_resize(&test_hash, 20);
    assert(test_hash.size == 20);
    ht_resize(&test_hash, 10);
    assert(test_hash.size == 10);
    ht_destroy(&test_hash);
    free(pc);
    free(pc2);

    return 0;
}
