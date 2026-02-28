#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
 char *ptr = NULL;
 int n = 100;
 printf("Starting exrcutuion\n");
 for(int i = 1; i <= 2; i++) {
   printf("Iteration %d\n");
  if(!ptr) {
    printf("[+] ptr is null. Allocating mamory using malloc\n");
    ptr = malloc(n);
  } else {
    printf("[-] ptr is not null. Skipping malloc\n");
  }
  printf("[*] Writting data to memory\n");
  strcpy(ptr, "Data written successfully!");
  printf("[*] Data: %s\n", ptr);
  printf("[*] Calling free(ptr)\n");
  free(ptr);
 }
 printf("Execution completed successfully\n");
 return 0;
}
