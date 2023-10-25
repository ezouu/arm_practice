#include <stdio.h>
#include <string.h>

#define NUM_BINS 16
#define MAX_VALUES 10000

int main() {

  int counts[NUM_BINS] = {0};
  int values[MAX_VALUES];
  int numValues = 0;  
  int bin_size = 1;
  int range = 16;

  printf("%d bins of size %d for range [0,%d)\n", NUM_BINS, bin_size, range);

  while (1) {
    int n;
    if (scanf("%d", &n) == 1) {
      values[numValues++] = n;
      
      while (n >= range) {
        bin_size *= 2;
        range *= 2;
        
        memset(counts, 0, sizeof(counts));
        
        printf("%d bins of size %d for range [0,%d)\n", NUM_BINS, bin_size, range);
      }
    }
    else {
      break;
    }
  }

  for (int i = 0; i < numValues; i++) {
    int bin = values[i] / bin_size;
    if (bin < NUM_BINS) {
      counts[bin]++;
    }
  }

  for (int i = 0; i < NUM_BINS; i++) {
    printf("[%3d:%3d] ", i * bin_size, (i + 1) * bin_size - 1);
    
    if (counts[i] > 0) {
      for (int j = 0; j < counts[i]; j++) {
        printf("*");
      }
    }
    
    printf("\n");
  }

  return 0;
}

/*
gcc -o histogram histogram.c
./histogram
*/