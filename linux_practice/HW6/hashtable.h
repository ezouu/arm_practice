#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct {
    char** keys;
    int* values;
    int capacity;
} hashtable_t;

hashtable_t* hashtable_create(int capacity);
int hashtable_insert(hashtable_t* table, char* key);
int hashtable_search(hashtable_t* table, char* key);
void hashtable_free(hashtable_t* table);

#endif // HASHTABLE_H
