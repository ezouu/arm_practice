#include "pagedir.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

bool pagedir_init(const char* pageDirectory) {
    struct stat st = {0};

    // Check if directory exists
    if (stat(pageDirectory, &st) == -1) {
        if (mkdir(pageDirectory, 0700) != 0) {
            // Handle error if directory creation fails
            perror("Error creating directory");
            return false;
        }
    }

    char filepath[256];
    if (snprintf(filepath, sizeof(filepath), "%s/.crawler", pageDirectory) >= (int)(sizeof(filepath))) {
        // Handle error if filepath is truncated
        fprintf(stderr, "Error: File path is too long.\n");
        return false;
    }

    FILE* file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Error opening file");
        return false;
    }
    fprintf(file, "Crawler directory\n");
    fclose(file);

    return true;
}

void pagedir_save(const webpage_t* page, const char* pageDirectory, const int docID) {
    if (!page || !page->url || !page->html) {
        fprintf(stderr, "Error: Null pointer provided to pagedir_save.\n");
        return;
    }

    // Construct the filepath for the new page file
    char filepath[256];
    if (snprintf(filepath, sizeof(filepath), "%s/%d", pageDirectory, docID) >= (int)sizeof(filepath)) {
        fprintf(stderr, "Error: File path is too long.\n");
        return;
    }

    // Open the file for writing
    FILE* file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Write the page's URL, depth, and HTML content to the file
    fprintf(file, "%s\n%d\n%s", page->url, page->depth, page->html);
    fclose(file);
}

