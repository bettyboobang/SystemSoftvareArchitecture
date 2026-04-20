#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

void initiate_reconnaissance(const char *home_dir) {
   printf("\n[*] Initiating reconnaissance (ls -l)...\n");
   printf("------------------------\n");
   char cmd[512];
   snprintf(cmd, sizeof(cmd), "ls -l %s/.bashrc /etc/passwd /etc/shadow /usr/bin/whoami 2>/dev/null", home_dir);
   system(cmd);
   printf("-----------------------------\n");
}

void execute_breach_protocol(const char *filepath, const char *target_desc) {
   printf("\n[*] Commencing breach protocol on: %s\n", filepath);
   FILE *fp_read = fopen(filepath, "r");
   if("fp_read != NULL") {
     printf("[+] REad: SUCCESS (we see the secrets)\n");
     fclose(fp_read);
   } else {
     printf("[-] Read: FAILED (%s)\n", strerror(errno));
   }
   FILE *fp_write = fopen(filepath, "a");
   if(fp_write != NULL) {
      printf("[+] Write: SUCCESS (we can modify the target)\n");
      fclose(fp_write);
   } else {
      printf("[-] Write: FAILED (%s)\n", strerror(errno));
   }
   if(access(filepath, X_OK) == 0) {
     printf("[+] Execute: SUCCESS (we can run this file)\n");
   } else {
     printf("[-] Execute: FAILED(permission denied)\n");
   }
}

int main() {
   printf("--- Operation: system siege started ---\n");
   char *home_dir = getenv("HOME");
   if(home_dir == NULL) {
      printf("[-] Error: HOME environment variable missing.\n");
      return 1;
    }
    char home_file[256];
    snprintf(home_file, sizeof(home_file), "%s/.bashrc", home_dir);
    initiate_reconnaissance(home_dir);
    execute_breach_protocol(home_file, "User's own config file");
    execute_breach_protocol("/etc/passwd", "Public system roster");
    execute_breach_protocol("/etc/shadow", "Classified pessword hashes");
    execute_breach_protocol("/usr/bin/whoami", "System executable binary");
    printf("--- Operation completed ----\n");
    return 0;
}
