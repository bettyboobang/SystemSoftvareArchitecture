#include <stdio.h>

void grow_stack() {
 int large_array[10000];
 int stack_var_deep;
 printf("Top of stack inside the function: %p\n", (void*)&stack_var_deep);
}
int main() {
 int stack_var_main;
 printf("Top of stack in main function: %p\n", (void*)&stack_var_main);
 grow_stack();
 return 0;
}
