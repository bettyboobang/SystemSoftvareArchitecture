#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

int main() {
 printf("Trying to allocate SIZE_MAX\n");
 void *ptr1 = malloc(SIZE_MAX);
 if(ptr1 == NULL) {
   printf("Error: %s\n", strerror(errno));
  } else {
    printf("Success!\n");
    free(ptr1);
  }
 printf("Trying to allocate SIZE_MAX / 2\n");
 void *ptr2 = malloc(SIZE_MAX /2);
 if(ptr2 == NULL) {
   printf("Error: %s\n", strerror(errno));
 } else {
  printf("Success!\n");
  free(ptr2);
 }
 return 0;
}
