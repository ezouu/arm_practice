#include "bag.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bag_t* bag_create() {
    bag_t* bag = (bag_t*)malloc(sizeof(bag_t));
    if (!bag) return NULL;

    bag->capacity = 10;
    bag->size = 0;
    bag->pages = (webpage_t**)malloc(sizeof(webpage_t*) * bag->capacity);
    if (!bag->pages) {
        free(bag);
        return NULL;
    }

    return bag;
}

void bag_add(bag_t* bag, webpage_t* page) {
    if (!bag || !page) return;  // Check for NULL pointers

    if (bag->size == bag->capacity) {
        size_t new_capacity = bag->capacity * 2;
        webpage_t** new_pages = realloc(bag->pages, sizeof(webpage_t*) * new_capacity);
        if (!new_pages) {
            fprintf(stderr, "Failed to resize bag\n");
            return;  // Avoid altering the original state on failure
        }
        bag->pages = new_pages;
        bag->capacity = new_capacity;
    }

    bag->pages[bag->size++] = page;
}

webpage_t* bag_remove(bag_t* bag) {
    if (bag->size == 0) return NULL;

    return bag->pages[--bag->size];
}

void bag_free(bag_t* bag) {
    for (int i = 0; i < bag->size; i++) {
        free(bag->pages[i]->url);
        free(bag->pages[i]);
    }
    free(bag->pages);
    free(bag);
}

int bag_size(const bag_t* bag) {
    if (!bag) {
        return 0;
    }
    return bag->size;
}
