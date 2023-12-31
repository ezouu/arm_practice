#include "set.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  char *key;
  void *item;
} set_item_t;

struct set {
  set_item_t *items;
  int count;
  int capacity; 
};

set_t* set_new(void) {
  set_t* set = malloc(sizeof(set_t));
  set->count = 0;
  set->capacity = 8;
  set->items = malloc(set->capacity * sizeof(set_item_t));
  return set;
}

bool set_insert(set_t *set, const char *key, void *item) {
  if (!set || !key || !item) return false;

  // Check if key already exists
  for (int i = 0; i < set->count; i++) {
    if (strcmp(set->items[i].key, key) == 0) {
      return false; 
    }
  }

  // Expand array if needed
  if (set->count == set->capacity) {
    set->capacity *= 2;
    set->items = realloc(set->items, set->capacity * sizeof(set_item_t));
  }

  // Insert new item
  char *key_copy = strdup(key);
  set->items[set->count].key = key_copy;
  set->items[set->count].item = item;
  set->count++;

  return true;
}

void* set_find(set_t *set, const char *key) {
  if (!set || !key) return NULL;

  for (int i = 0; i < set->count; i++) {
    if (strcmp(set->items[i].key, key) == 0) {
      return set->items[i].item;
    }
  }

  return NULL;
}

void set_print(set_t *set, FILE *fp, void (*itemprint)(FILE *fp, const char *key, void *item)) {
  if (!set) {
    fprintf(fp, "(null)\n");
    return;
  }

  for (int i = 0; i < set->count; i++) {
    if (itemprint) {
      itemprint(fp, set->items[i].key, set->items[i].item);
    } else {
      fprintf(fp, "%s\n", set->items[i].key); 
    }
  }
}

void set_iterate(set_t *set, void *arg, void (*itemfunc)(void *arg, const char *key, void *item)) {
  if (!set || !itemfunc) return;
  
  for (int i = 0; i < set->count; i++) {
    itemfunc(arg, set->items[i].key, set->items[i].item);
  }
}

void set_delete(set_t *set, void (*itemdelete)(void *item)) {
  if (!set) return;

  for (int i = 0; i < set->count; i++) {
    if (itemdelete) {
      itemdelete(set->items[i].item);
    }
    free(set->items[i].key);
  }

  free(set->items);
  free(set);
}