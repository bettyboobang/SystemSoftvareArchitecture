#include <stdio.h>
#include <stdlib.h>

void recursive_function(int depth) {
 char buffer[1024];
  if(depth % 1000 == 0) {
    printf("Current recursion depth: %d\n", depth);
  }
 recursive_function(depth +1);
}
int main() {
 printf("Starting infinite recursion to make stack overflow...\n");
 printf("How deep it can go before the system kills it?\n\n");
 recursive_function(1);
 return 0;
}
