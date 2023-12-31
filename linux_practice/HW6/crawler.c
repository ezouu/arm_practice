#include "crawler.h"
#include "bag.h"
#include "hashtable.h"
#include "pagedir.h"
#include "webpage.h"
#include "url.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>

char *download(const char *url, size_t *size_out);
char *normalizeURL(const char *base, const char *url);

static void parseArgs(int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth);
static void crawl(char* seedURL, char* pageDirectory, int maxDepth);
static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen);

int main(int argc, char* argv[]) {
    char* seedURL;
    char* pageDirectory;
    int maxDepth;

    parseArgs(argc, argv, &seedURL, &pageDirectory, &maxDepth);
    crawl(seedURL, pageDirectory, maxDepth);

    free(seedURL);
    free(pageDirectory);

    return 0;
}

static void parseArgs(int argc, char* argv[], char** seedURL, char** pageDirectory, int* maxDepth) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <seedURL> <pageDirectory> <maxDepth>\n", argv[0]);
        exit(1);
    }

    *seedURL = strdup(argv[1]);
    *pageDirectory = strdup(argv[2]);
    *maxDepth = atoi(argv[3]);  

    if (*maxDepth < 0 || *maxDepth > 10) {
        fprintf(stderr, "maxDepth must be between 0 and 10\n");
        exit(2);
    }

    if (!pagedir_init(*pageDirectory)) {
        fprintf(stderr, "Failed to initialize page directory\n");
        exit(3);
    }
}

static void crawl(char *seedURL, char *pageDirectory, const int maxDepth) {
    hashtable_t* pagesSeen = hashtable_create(100);
    int crawledCount = 0;
    if (!pagesSeen) {
        fprintf(stderr, "Failed to create hashtable\n");
        exit(4);
    }

    bag_t* pagesToCrawl = bag_create();
    if (!pagesToCrawl) {
        fprintf(stderr, "Failed to create bag\n");
        hashtable_free(pagesSeen);
        exit(5);
    }

    int docID = 1;
    webpage_t* seedPage = webpage_create(seedURL, 0, NULL);
    if (!seedPage) {
        fprintf(stderr, "Failed to create seed page\n");
        bag_free(pagesToCrawl);
        hashtable_free(pagesSeen);
        exit(6);
    }

    bag_add(pagesToCrawl, seedPage);
    hashtable_insert(pagesSeen, seedURL);

    while (bag_size(pagesToCrawl) > 0) {
        webpage_t* currentPage = bag_remove(pagesToCrawl);
        if (!currentPage) {
            continue;
        }

        printf("%d Fetched: %s\n", currentPage->depth, currentPage->url);
        sleep(1);

        size_t size_out;
        char* html = download(currentPage->url, &size_out);
        if (!html) {
            fprintf(stderr, "Failed to download page\n");
            webpage_free(currentPage);
            continue;
        }

        currentPage->html = html;
        printf("%d Scanning: %s\n", currentPage->depth, currentPage->url);

        if (currentPage->depth < maxDepth) {
            pageScan(currentPage, pagesToCrawl, pagesSeen);
        }
        crawledCount++;
        pagedir_save(currentPage, pageDirectory, docID++);
        free(html);
        currentPage->html = NULL;
        webpage_free(currentPage);
    }

    hashtable_free(pagesSeen);
    bag_free(pagesToCrawl);
    // printf("Total websites crawled: %d\n", crawledCount); 
}


static void pageScan(webpage_t* page, bag_t* pagesToCrawl, hashtable_t* pagesSeen) {
    const char* startPattern = "<a href=\"";
    const char* endPattern = "\"";
    char* html = page->html;
    char* startPos = html;
    char* endPos;

    while ((startPos = strstr(startPos, startPattern)) != NULL) {
        startPos += strlen(startPattern);
        if ((endPos = strstr(startPos, endPattern)) != NULL) {
            size_t urlLen = endPos - startPos;
            char* url = strndup(startPos, urlLen);
            if (!url) {
                fprintf(stderr, "Failed to allocate memory for URL\n");
                break;
            }

            printf("%d Found: %s\n", page->depth, url);

            char* normalizedURL = normalizeURL(page->url, url);
            if (normalizedURL) {
                if (!isInternalURL(page->url, normalizedURL)) {
                    printf("%d IgnExtrn: %s\n", page->depth, normalizedURL);
                } else if (!hashtable_search(pagesSeen, normalizedURL)) {
                    hashtable_insert(pagesSeen, normalizedURL);
                    printf("%d Added: %s\n", page->depth, normalizedURL);

                    webpage_t* newPage = webpage_create(normalizedURL, page->depth + 1, NULL);
                    if (newPage) {
                        bag_add(pagesToCrawl, newPage);
                    } else {
                        fprintf(stderr, "Failed to create new page for URL: %s\n", normalizedURL);
                    }
                } else {
                    printf("%d IgnDupl: %s\n", page->depth, normalizedURL);
                }
                free(normalizedURL);
            }
            free(url);
            startPos = endPos + strlen(endPattern);
        }
    }
}

