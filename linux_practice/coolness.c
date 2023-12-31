#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LOWER_T -99
#define UPPER_T 50 
#define LOWER_V 0.5

double calculateCoolness(double t, double v) {
  return 35.74 + 0.6215*t - 35.75*pow(v,0.16) + 0.4275*t*pow(v,0.16);
}

int main(int argc, char *argv[]) {

  double t, v, coolness;

  if (argc > 3) {
    printf("Usage: ./coolness [temperature] [wind speed]\n");
    return 1;
  }

  if (argc == 1) {
    // No arguments
    printf("Temp\tWind\tCoolness\n");
    int previousTemp = -10000000; 
    for (t = -10; t <= 40; t += 10) {

      for (v = 5; v <= 15; v += 5) {
        coolness = calculateCoolness(t, v);
        printf("%0.1f\t%0.1f\t%0.1f\n", t, v, coolness);   
      }
      
      if (t != previousTemp) {
        if (t!=40){
          printf("\n");
        }
        previousTemp = t; 
      }      
    }

  } else if (argc == 2) {
    // One argument
    t = atof(argv[1]);
    if (t < LOWER_T || t > UPPER_T) {
      printf("Error: Coolness. Acceptable input values are %d<=T<=%d and %g<=V.\n", LOWER_T, UPPER_T, LOWER_V);
      return 1;
    }
    
    printf("Temp\tWind\tCoolness\n");
    for (v = 5; v <= 15; v += 5) {
      coolness = calculateCoolness(t, v);
      printf("%0.1f\t%0.1f\t%0.1f\n", t, v, coolness);
    }

  } else {
    // Two arguments
    t = atof(argv[1]);
    v = atof(argv[2]);

    if (t < LOWER_T || t > UPPER_T) {
      printf("Error: Coolness. Acceptable input values are %d<=T<=%d and %g<=V.\n", LOWER_T, UPPER_T, LOWER_V);
      return 1;
    }

    if (v < LOWER_V) {
      printf("Error: Coolness. Acceptable input values are %d<=T<=%d and %g<=V.\n", LOWER_T, UPPER_T, LOWER_V);
      return 1; 
    }

    coolness = calculateCoolness(t, v);
    printf("Temp\tWind\tCoolness\n");
    printf("%0.1f\t%0.1f\t%0.1f\n", t, v, coolness);
  }

  return 0;
}
