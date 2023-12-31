#include "hashtable.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long hash(char* str) {
    if (!str) return 0;

    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

hashtable_t* hashtable_create(int capacity) {
    hashtable_t* table = malloc(sizeof(hashtable_t));
    if (!table) return NULL;

    table->capacity = capacity;
    table->keys = calloc(capacity, sizeof(char*));
    table->values = calloc(capacity, sizeof(int));
    if (!table->keys || !table->values) {
        free(table->keys);  // Safe to call free on NULL
        free(table->values);
        free(table);
        return NULL;
    }

    return table;
}

int hashtable_insert(hashtable_t* table, char* key) {
    if (!table || !key) return -1;  // Error code for invalid input

    unsigned long index = hash(key) % table->capacity;

    while (table->keys[index] != NULL) {
        if (strcmp(table->keys[index], key) == 0) return 0;  // Key already exists
        index = (index + 1) % table->capacity;
    }

    char* keyCopy = strdup(key);
    if (!keyCopy) return -2;  // Error code for allocation failure

    table->keys[index] = keyCopy;
    table->values[index] = 1;

    return 1;
}

int hashtable_search(hashtable_t* table, char* key) {
    if (!table || !key) return 0;

    unsigned long index = hash(key) % table->capacity;

    while (table->keys[index] != NULL) {
        if (strcmp(table->keys[index], key) == 0) return table->values[index];
        index = (index + 1) % table->capacity;
    }

    return 0;
}

void hashtable_free(hashtable_t* table) {
    if (!table) return;

    for (int i = 0; i < table->capacity; i++) {
        free(table->keys[i]);  // Safe to call free on NULL
    }
    free(table->keys);
    free(table->values);
    free(table);
}
