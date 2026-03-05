#include <stdio.h>

int main() {
 int target = 5;
 int buffer[3] = {1, 2, 3};
 printf("Before overwrite: target = %d\n", target);
 buffer[3] = 99;
 printf("After overwrite: target = %d\n", target);
 return 0;
}
