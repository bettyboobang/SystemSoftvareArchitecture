#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void initiate_shadow_protocol() {
   printf("[*] Initiating shadow protocol...\n");
   printf("[*] Requesting elevated privileges...\n");
   pid_t pid = fork();
   if(pid == -1) {
     perror("[-] Fork failed. The mainframe resisted");
     exit(1);
   } else if(pid == 0) {
      execlp("sudo", "sudo", "cat" , "/etc/shadow", NULL);
      perror("[-] Execution failed! Is sudo installed?");
      exit(1);
   } else {
      int status;
      waitpid(pid, &status, 0);
      if(WIFEXITED(status) && WEXITSTATUS(status) == 0) {
        printf("[+] Shadow protocol executed successfully.\n");
      } else {
        printf("[-] Shadow protocol failed or was aborted by the user.\n");
      }
  }
}

int main() {
   initiate_shadow_protocol();
    return 0;
}
