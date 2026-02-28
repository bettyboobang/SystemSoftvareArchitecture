#include <stdio.h>
#include <stdlib.h>

int main() {
 printf("Calling realloc: ");
 void *ptr1 = realloc(NULL, 100);
 if(ptr1 != NULL) {
   printf("Success. Memory allocated. Works like malloc(100)\n");
 } else {
   printf("Errror. Memory allocation failed. \n");
 }
 printf("Calling realloc for previous pointer: \n ");
 void *ptr2 = realloc(ptr1, 0);
 if(ptr2 == NULL) {
  printf("Success. Returned null. Memory freed\n");
 } else {
  printf("Warning. Returned pointer %p\n", ptr2);
  free(ptr2);
 }
 printf("Calling realloc: \n");
 void *ptr3 = realloc(NULL, 0);
 if(ptr3 == NULL) {
   printf("Result. REturned null\n");
 } else {
   printf("Result. Returned a unique pointer %p that can be freed. \n", ptr3);
   free(ptr3);
 }
 return 0;
}
