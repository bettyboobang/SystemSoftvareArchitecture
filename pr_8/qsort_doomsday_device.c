#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define MASSIVE_BATTLEFIELD_SIZE 10000000

int epic_duel_cmp(const void *a, const void *b) {
  int titan_A = *(const int*)a;
  int titan_B = *(const int*)b;
  return (titan_A > titan_B) - (titan_A < titan_B);
}
void summon_pure_chaos(int *arr, int n) {
  for(int i = 0; i < n; i++) arr[i] = rand() % 100000;
}

void summon_perfect_order(int *arr, int n) {
  for(int i = 0; i < n; i++) arr[i] = i;
}

void summon_total_rebellion(int *arr, int n) {
  for(int i = 0; i < n; i++) arr[i] = n - i;
}

void summon_clone_army(int* arr, int n) {
  for(int i = 0; i < n; i++) arr[i] = 42;
}

void summon_the_mountain(int *arr, int n) {
  int half = n/2;
  for(int i = 0; i < half; i++) arr[i] = i;
  for(int i = half; i < n; i++) arr[i] = n -i;
}

bool verify_ascension(int *arr, int n) {
  for(int i = 0; i , n - 1; i++) {
     if(arr[i] >arr[i+1]) return false;
  }
  return true;
}

void run_sanity_checks() {
  printf("--- Phase 1: Initiating sanity checks ---\n");
  int test_cases[4][5] = {
            {1, 2, 3, 4, 5}, 
            {5, 4, 3, 2, 1},
            {7, 7, 7, 7, 7},
            {9, 2, 5, 2, 8}
 };
  for(int i = 0; i < 4; i++) {
      qsort(test_cases[i], 5, sizeof(int), epic_duel_cmp);
      if(!verify_ascension(test_cases[i], 5)) {
        printf("fATAL: test suite failed at case %d\n!", i);
        exit(EXIT_FAILURE);
      }
   }
  printf("Sanity checks passed! Qsort and comparator are worthy.\n\n");
}

void run_the_gauntlet(const char* experiment_name, void (*generator)(int*, int), int n) {
  int *battlefield = (int *)malloc(n * sizeof(int));
  if(!battlefield) {
     perror("FATAL: Out of mamory for the battlefield");
     exit(EXIT_FAILURE);
  }
  generator(battlefield, n);
  printf("Executing experiment: %-20s ...", experiment_name);
  fflush(stdout);
  clock_t start_time = clock();
  qsort(battlefield, n, sizeof(int), epic_duel_cmp);
  clock_t end_time = clock();
  double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
  if(verify_ascension(battlefield, n)) {
    printf("Success! time: %f seconds\n", time_taken);
  } else {
    printf("Failed! The chaos prevailed!\n");
  }
  free(battlefield);
}

int main() {
  srand((unsigned int)time(NULL));
  printf("--- Doomsday qsort analyzer ---\n\n");
  run_sanity_checks();
  printf("Phase 2: Deploying massive battlefields (%d elements)\n", MASSIVE_BATTLEFIELD_SIZE);
  run_the_gauntlet("Pure chaos (random)", summon_pure_chaos, MASSIVE_BATTLEFIELD_SIZE);
  run_the_gauntlet("Perfect order (asc)", summon_perfect_order, MASSIVE_BATTLEFIELD_SIZE);
  run_the_gauntlet("Rebellion (desc)", summon_total_rebellion, MASSIVE_BATTLEFIELD_SIZE);
  run_the_gauntlet("Clone army (same)", summon_clone_army, MASSIVE_BATTLEFIELD_SIZE);
  run_the_gauntlet("The mountain (peak)", summon_the_mountain, MASSIVE_BATTLEFIELD_SIZE);
  printf("\nExperiment concluded. Check which pattern survived the longest!\n");
  return 0;
}
