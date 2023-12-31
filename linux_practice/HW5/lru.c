#include "lru.h"
#include "hashtable.h"
#include "set.h"
#include <stdlib.h>
#include <string.h>

#include "set.h"
#include <stdlib.h>

typedef struct lru lru_t; 
void itemdelete(void* item);

struct lru {
  int capacity;
  int size;
  set_t* items;   
  set_t* age;
};

lru_t* lru_new(int capacity) {

  lru_t* lru = malloc(sizeof(lru_t));
  lru->capacity = capacity;
  lru->size = 0;

  lru->items = set_new();
  lru->age = set_new();

  return lru;
}

bool lru_insert(lru_t* lru, const char* key, void* item) {

  if (!lru || lru->size == lru->capacity)  
     return false;

  if (!item)
     return false;

  if (set_find(lru->items, key) != NULL)   
     return false;
   
  if (lru->size == lru->capacity) {
   
    char* first_key;
    
    set_t* temp_set = set_new();
    
    void* arg = temp_set;
    
    void copy_first_key(void* set, const char* key, void* item) {
       set_insert(set, key, NULL);
       first_key = strdup(key);
    }
    
    set_iterate(lru->items, arg, copy_first_key);
      
       
    set_t* new_set = set_new();
    
    void* arg2 = new_set;
    
    void copy_items(void* set, const char* key, void* item) {
      if (strcmp(key, first_key) != 0) {
         set_insert(set, key, item);  
      }
    }
    
    set_iterate(lru->items, arg2, copy_items);
    
    set_delete(lru->items, free);  // Pass free to set_delete
    lru->items = new_set;
    
    free(first_key);
    set_delete(temp_set, free);
    
    lru->size--;   
    
  }

  set_insert(lru->items, key, item);
  
  lru->size++;

  return true;

}

void* lru_find(lru_t* lru, const char* key) {

  if(!lru || !key) {
    return NULL; 
  }

  void* item = set_find(lru->items, key);

  if(item) {
    // Found - update age

    // Create temp set
    set_t* temp_age = set_new();

    // Copy age set 
    void* arg = temp_age;
    void copy(void* ts, const char* k, void* v) {
      set_insert(ts, k, NULL);
    }
    set_iterate(lru->age, arg, copy);

    // Insert found key  
    set_insert(temp_age, key, NULL);

    // Swap age set
    set_t* old_age = lru->age;
    lru->age = temp_age;
    set_delete(old_age, free);

    return item;

  } else {
    return NULL;
  }

}


void lru_print(lru_t* lru, FILE* fp, 
  void (*itemprint)(FILE* fp, const char* key, void* item)) {
  
  if(!lru) {
    fprintf(fp, "(null)\n");
    return;
  }

  set_print(lru->items, fp, itemprint); 
}

void lru_iterate(lru_t* lru, void* arg, 
  void (*itemfunc)(void* arg, const char* key, void* item)) {

  if(!lru || !itemfunc) 
    return;

  set_iterate(lru->items, arg, itemfunc);
}

void lru_delete(lru_t* lru, void (*itemdelete)(void*)) {
  
  if(!lru) 
    return;

  set_delete(lru->items, itemdelete);
  set_delete(lru->age, free);

  free(lru);
}