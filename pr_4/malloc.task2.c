#include <stdio.h>
#include <stdlib.h>
 
int main() {
 int xa = 1000000;
 int xb = 3000;
 int num = xa * xb;
 printf("xa = %d, xb = %d\n", xa, xb);
 printf("Expected number of bytes: 3000000000\n");
 printf("Actual value of num: %d\n", num);
 printf("Value passed to malloc: %zu\n", (size_t)num);
 void *ptr = malloc(num);
 if(ptr == NULL) {
  printf("Malloc returned NULL\n");
 } else {
  printf("Malloc successfully allocated memory\n");
  free(ptr);
 }
 return 0;
}
