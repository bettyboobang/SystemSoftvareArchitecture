#include <stdio.h>
#include <stdlib.h>

int main() {
 void *ptr0 = malloc(0);
 if(ptr0 == NULL) {
  printf("Malloc(0) returned NULL\n");
 } else {
  printf("Malloc(0) returned pointer %p\n", ptr0);
 }
 free(ptr0);
 void *ptr3 = malloc(3);
 if(ptr3 == NULL) {
  printf("Malloc(3) returned NULL\n");
 } else {
  printf("Malloc(3) retuned pointer %p\n", ptr3);
 }
 free(ptr3);
 return 0;
}
