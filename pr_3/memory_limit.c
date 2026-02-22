#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CHUNK_SIZE (1024 * 1024)

int main() {
  int count = 0;
  char *ptr;
  printf("Starting memory allocation (1 mb per chunk)\n");
  while(1) {
   ptr = (char *)malloc(CHUNK_SIZE);
   if(ptr == NULL) {
      printf(" Memory allocation failed! Reached the virtual memory limit\n");
      printf("Total succesfully allocated: %d mb\n", count);
      break;
    }
    memset(ptr, 0, CHUNK_SIZE);
    count++;
  if(count % 10 == 0) {
    printf("Allocated %d mb...\n", count);
  }
  if(count >= 2000) {
    printf("safety stop reached. Exit");
    break;
  }
 }
 return 0;
}
