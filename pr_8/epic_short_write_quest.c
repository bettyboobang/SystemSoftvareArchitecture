#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define MASSIVE_CHONK_SIZE 1048576

void unleash_the_kraken_write() {
  int dimentional_portals[2];
  if(pipe(dimentional_portals) == -1) {
    perror("FATAL: The dimentional portals collapsed (pipe failed)");
    exit(EXIT_FAILURE);
  }
  int flags = fcntl(dimentional_portals[1], F_GETFL, 0);
  fcntl(dimentional_portals[1], F_SETFL, flags | O_NONBLOCK);
  char *mega_chonk_buffer = (char *)malloc(MASSIVE_CHONK_SIZE);
  if(!mega_chonk_buffer) {
    perror("FATAL: Ran out of magic dust (malloc failed)");
    exit(EXIT_FAILURE);
  }
  printf("--- Mission start ---\n");
  printf("Attempting to shove %d bytes into the pipe portal...\n", MASSIVE_CHONK_SIZE);
  ssize_t bytes_swallowed = write(dimentional_portals[1], mega_chonk_buffer, MASSIVE_CHONK_SIZE);
  if(bytes_swallowed < 0) {
    perror("OOps, the shoving failed completely");
 }
 else if (bytes_swallowed < MASSIVE_CHONK_SIZE) {
     printf("\n>>> Successful short write detected! <<<\n");
     printf("We ordered to write (nbytes): %d bytes\n", MASSIVE_CHONK_SIZE);
     printf("But the system wrote(count) : %zd bytes\n", bytes_swallowed);
     printf("result: count != nbytes. Mission accomplished!\n");
   } else{
     printf("Wait, it swallowed the wholethng? Your pipe buffer is abnormally huge.\n");
   }
   free(mega_chonk_buffer);
   close(dimentional_portals[0]);
   close(dimentional_portals[1]);
}
int main() {
  printf("Welcome to the epic short write quest!\n");
  unleash_the_kraken_write();
  return 0;
}
