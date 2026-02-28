#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main() {
 size_t initial_size = 50;
 char *original_ptr = (char *)malloc(initial_size);
 if(original_ptr == NULL) {
   perror("Malloc error");
   return 1;
 }
 strcpy(original_ptr, "Data is intact. Hello potato!");
 printf("Initial string: %s/n", original_ptr);
 printf("Original pointer address: %p\n", (void*)original_ptr);
 size_t massive_size = SIZE_MAX;
 printf("Attempting realloc for %zu bytes\n", massive_size);
 char *temp_ptr = (char *)realloc(original_ptr, massive_size);
 if(temp_ptr == NULL) {
  printf("Realloc returned NULL(allocation failed)\n");
  printf("Checking the original memory blaock: \n");
  printf("Address is still: %p\n", (void*)original_ptr);
  printf("Original data: %s\n", original_ptr);
 } else {
  printf("Realloc succseded, omg\n");
  original_ptr = temp_ptr;
 }
 free(original_ptr);
 printf("Memory freed. Exit\n");
 return 0;
}
