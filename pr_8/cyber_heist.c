#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#define VAULT_FILENAME "secret_vault_8_2.dat"

void setup_the_vault() {
   unsigned char precious_data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
   int fd = open(VAULT_FILENAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
   if(fd == -1) {
      perror("FATAL: Failed to construct the vault");
      exit(EXIT_FAILURE);
  }
   write(fd, precious_data, sizeof(precious_data));
   close(fd);
   printf("Vault initialized with 10 bytes of encrypted data.\n");
}

void execute_data_heist() {
   unsigned char loot_bag[4];
   int fd = open(VAULT_FILENAME, O_RDONLY);
   if(fd == -1) {
      perror("FATAL: Failed to crack the vault open");
      exit(EXIT_FAILURE);
   }
   printf("Executing lseek: jumping to offset 3...\n");
   lseek(fd, 3, SEEK_SET);
   printf("Executing read: snatching 4 bytes...\n");
   ssize_t bytes_snatched = read(fd, loot_bag, 4);
   if(bytes_snatched == 4) {
     printf("\n>>> Heist Successfull! <<<\n");
     printf("The loot bag contains: [");
     for(int i = 0; i < 4; i++) {
        printf("%d", loot_bag[i]);
     }
     printf("]\n");
  } else {
     printf("Mission Failed. Expected 4 bytes, got %zd.\n", bytes_snatched);
  }
  close(fd);
  unlink(VAULT_FILENAME);
}

int main() {
   printf("---- Mission the offset job ----\n\n");
   setup_the_vault();
   execute_data_heist();
   return 0;
}

