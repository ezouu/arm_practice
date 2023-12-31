#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <stdlib.h>

typedef struct {
    char* url;
    int depth;
    char* html;  // HTML content of the page
} webpage_t;

webpage_t* webpage_create(const char* url, int depth, const char* html);
void webpage_free(webpage_t* page);

#endif // WEBPAGE_H
