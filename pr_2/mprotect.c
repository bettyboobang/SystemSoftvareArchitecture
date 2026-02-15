#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main() {
 void *buffer;
 long pagesize;
 pagesize = sysconf(_SC_PAGESIZE);
 if(pagesize == -1) {
    perror("sysconf error");
    return 1;
 }
 printf("Size of memory page: %ld bite\n", pagesize);
 if(posix_memalign(&buffer, pagesize, pagesize) != 0) {
    perror("posix_memalign error");
    return 1;
 }
 printf("Memory was succesfully allocated and aligned.\n");
 strcpy((char *)buffer, "Initial data: Hello berry:)");
 printf("Data in memory: %s\n", (char *)buffer);
 printf("Apply mprotect: establish rights PROT_READ...\n");
 if(mprotect(buffer, pagesize, PROT_READ) == -1) {
    perror("mprotect error");
    free(buffer);
    return 1;
 }
 printf("Rights changed for 'Read only'.\n");
 printf("Trying to read: %s\n", (char *)buffer);
 printf("\nTrying to write(will cause segmentation fault)\n");
 strcpy((char *)buffer, "Overwrite attempt");
 printf("If you see this massage mprotect didnt work :(\n");
 free(buffer);
 return 0;
}
