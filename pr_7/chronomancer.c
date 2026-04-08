#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void cast_heavy_spell() {
  printf(">>> Casting a complex spell... (simulating heavy workload) <<<\n");
  volatile long long magic_dust = 0;
  for(long long i = 0; i < 50000000; i++) {
     magic_dust += i;
   }
}

int main() {
  struct timespec start_time, end_time;
  double elapsed_milliseconds;
  printf("Booting up the Chronomancer module...\n\n");
  clock_gettime(CLOCK_MONOTONIC, &start_time);
  cast_heavy_spell();
  clock_gettime(CLOCK_MONOTONIC, &end_time);
  elapsed_milliseconds = (end_time.tv_sec - start_time.tv_sec) * 1000.0;
  elapsed_milliseconds = (end_time.tv_nsec - start_time.tv_nsec) / 1000000.0;
  printf("\n>>> Success! The spell took %.3f milliseconds to cast! <<<\n", elapsed_milliseconds);
  return EXIT_SUCCESS;
}

