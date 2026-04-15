#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
   pid_t clone_id;
   printf("--- Initiating cloning sequence ---\n");
   clone_id = fork();
   if(clone_id == 0) {
     printf("Clone say hello to you! My fork returned : %d\n", clone_id);
   } else if (clone_id > 0) {
     printf("Hello form original! My fork returned: %d\n", clone_id);
   } else {
     printf("FATAL: Cloning failed!\n");
   }
   return 0;
}
