#include <stdio.h>
#include <stdlib.h>

int global_init = 42;
int global_uninit;

int main() {
 int stack_var;
 void *heap_var = malloc(10);
 printf("Segments in memory:");
 printf("text segment: %p\n", (void*)main);
 printf("data segment: %p\n", (void*)&global_init);
 printf("bss segment: %p\n", (void*)&global_uninit);
 printf("heap segment: %p\n",heap_var);
 printf("stack segment: %p\n", (void*)&stack_var);
 free(heap_var);
 return 0;
}
