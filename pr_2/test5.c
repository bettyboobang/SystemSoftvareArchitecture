#include <stdio.h>

void my_function() {
 int temp_var = 5;
 printf("Function is working, variable = %d\n", temp_var);
}

int main() {
 printf("Before function call.\n");
 my_function();
 printf("After functin call.\n");
 return 0;
}
