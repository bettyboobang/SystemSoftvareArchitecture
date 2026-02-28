#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

int main() {
 size_t array_size = 256*1024*1024;
 long long accesses = 5000000;
 uint8_t *arr = (uint8_t*)malloc(array_size);
 if(arr == NULL) {
  printf("Error");
  return 1;
 }
 printf("Initializing array...\n");
 fflush(stdout);
 for(size_t i = 0; i < array_size; i++) arr[i] = 0;
 printf("Initialization is complete. Starting benchmarks\n");
 int strides[] = {1, 4, 16, 64, 4096};
 int num_strides = 5;
 printf("%-20s | %-15s\n", "Stride(bytes)", "Time(ms)");
 printf("----------------------------\n");
 for(int s = 0; s < num_strides; s++) {
  int stride = strides[s];
  size_t index = 0;
  clock_t start = clock();
  for(long long i = 0; i < accesses; i++) {
    arr[index] += 1;
    index = (index +stride) % array_size;
  }
  clock_t end = clock();
  double time_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

  printf("%-20d | %-15.2f\n", stride, time_ms);
 }
 free(arr);
 return 0;
}

