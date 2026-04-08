#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int i;
  int sequence_length = 5;
  double n;
  srand((unsigned int)time(NULL));
  printf(">>> The random number generator is seeded! <<<\n\n");
  printf("--- Sequence a: from 0.0 to 1.0 ---\n");
  for (i = 0; i < sequence_length; i++) {
      double random_a = (double)rand() / RAND_MAX;
      printf("%.6f/n", random_a);
   }
  printf("\n>>> Enter the upper bound 'n' (e.g. 7.5 or 100.0): ");
  if(scanf("%lf", &n) != 1) {
    printf("Error: Invalid input. Please enter a valid number.\n");
    return EXIT_FAILURE;
  }
  printf("\n--- Sequence(b): from 0.0 to %2f ---\n", n);
  for(i = 0; i < sequence_length; i++) {
     double random_b = ((double)rand() / RAND_MAX) * n;
    printf("%.6f\n", random_b);
  }
  return EXIT_SUCCESS;
}
