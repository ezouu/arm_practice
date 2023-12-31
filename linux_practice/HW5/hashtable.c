#include "hashtable.h"
#include "set.h"
#include <stdlib.h>
#include <string.h>
unsigned int hash(const char *key);
struct hashtable {
  int num_slots;
  set_t **slots;  
};

unsigned int hash(const char *key) {
  // Simple hash function
  unsigned int hash = 5381;
  int c;  
  while ((c = *key++)) 
    hash = ((hash << 5) + hash) + c; 
  return hash;
}

hashtable_t *hashtable_new(const int num_slots) {

  hashtable_t *ht = malloc(sizeof(hashtable_t));
  if(!ht) return NULL;

  ht->num_slots = num_slots;
  ht->slots = malloc(num_slots * sizeof(set_t*));
  
  if(!ht->slots) {
    free(ht);
    return NULL;
  }

  for(int i=0; i<num_slots; i++) {
    ht->slots[i] = set_new();
    if(!ht->slots[i]) {
      hashtable_delete(ht, NULL);
      return NULL;
    }
  }

  return ht;
}

bool hashtable_insert(hashtable_t *ht, const char *key, void *item) {
  
  if(!ht || !key || !item) return false;

  int slot = hash(key) % ht->num_slots;

  return set_insert(ht->slots[slot], key, item);
}


void* hashtable_find(hashtable_t *ht, const char *key) {
  
  if(!ht || !key) return NULL;

  int slot = hash(key) % ht->num_slots;

  return set_find(ht->slots[slot], key); 
}

void hashtable_print(hashtable_t *ht, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {

  // Print each set
  for(int i=0; i<ht->num_slots; i++) {
    set_print(ht->slots[i], fp, itemprint); 
  }

}

void hashtable_iterate(hashtable_t *ht, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
  
  if(!ht || !itemfunc) return;

  // Iterate over each set
  for(int i=0; i<ht->num_slots; i++) {
    set_iterate(ht->slots[i], arg, itemfunc);
  }

}

void hashtable_delete(hashtable_t *ht, void (*itemdelete)(void *item)) {

  if(!ht) return;

  for(int i=0; i<ht->num_slots; i++) {
    set_delete(ht->slots[i], itemdelete); 
  }

  free(ht->slots);
  free(ht);

}
