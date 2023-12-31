#include "webpage.h"
#include <stdlib.h>
#include <string.h>

webpage_t* webpage_create(const char* url, int depth, const char* html) {
    if (!url) return NULL;

    webpage_t* page = malloc(sizeof(webpage_t));
    if (!page) return NULL;


    page->url = NULL;
    page->html = NULL;


    page->url = strdup(url);
    if (!page->url) {
        free(page);
        return NULL;
    }

    page->depth = depth;

    if (html) {

        page->html = strdup(html);
        if (!page->html) {
            free(page->url);
            free(page);
            return NULL;
        }
    }

    return page;
}

void webpage_free(webpage_t* page) {
    if (page) {
        free(page->url);
        free(page->html);
        free(page);
    }
}
