#ifndef BAG_H
#define BAG_H
#include "webpage.h"
#include <stdlib.h>

typedef struct {
    webpage_t** pages;
    int size;
    int capacity;
} bag_t;

// Function prototypes
bag_t* bag_create();
void bag_add(bag_t* bag, webpage_t* page);
webpage_t* bag_remove(bag_t* bag);
void bag_free(bag_t* bag);
int bag_size(const bag_t* bag);
#endif // BAG_H
