#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#define PATH_MAX 512

void fabricate_civilian_document(const char *orig_path) {
   printf("[*] Fabricating civilian document at: %s\n", orig_path);
   FILE *fp = fopen(orig_path, "w");
   if(fp == NULL) {
     perror("[-] Failed to create original document");
     exit(1);
   }
   fprintf(fp, "This is top secret civilian data shhhhhhh\n");
   fclose(fp);
   printf("[+] Document fabricated successfully.\n");
}

void execute_root_replication(const char *orig_path, const char *copy_path) {
   printf("\n[*] Executing root replication protocol...\n");
   printf("[*] You may be asked for your password\n");
   char cmd[PATH_MAX * 2];
   snprintf(cmd, sizeof(cmd), "sudo cp %s $s", orig_path, copy_path);
   int status = system(cmd);
   if(status == 0) {
     printf("[+] File replicated as root to: %s\n", copy_path);
   }else {
     printf("[-] Root replication failed.\n");
     exit(1);
   }
}

void attempt_unauthorized_modification(const char *copy_path) {
   printf("\n[*] Attempting to modify the root-owned file as regular user....\n");
   FILE *fp = fopen(copy_path, "a");
   if(fp == NULL) {
     printf("[-] Modification blocked! Reason: %s\n", strerror(errno));
   } else {
     fprintf(fp, "Trying to inject unauthorized data.\n");
     fclose(fp);
     printf("[!] Anomaly: modification succeeded(this shouldnt happen)\n");
   }
}

void initiate_rm_eradication(const char *copy_path) {
   printf("\n[*] Initiating eradicstion protocol on root-owned file...\n");
   char cmd[PATH_MAX + 10];
   snprintf(cmd, sizeof(cmd), "rm -f %s", copy_path);
   int status = system(cmd);
   if(status == 0) {
     printf("[+] File successfully eradicated by regular user!\n");
   } else {
     printf("[-] Eradication failed.\n");
   }

}

int main() {
   char orig_path[PATH_MAX];
   char copy_path[PATH_MAX];
   char *home_dir = getenv("HOME");
   if(home_dir == NULL) {
     printf("[-] Error. HOME environment variable not found.\n");
     return 1;
   }
   snprintf(orig_path, sizeof(orig_path), "%s/civilian_doc.txt", home_dir);
   snprintf(copy_path, sizeof(copy_path), "%s/root_copy.txt", home_dir);
   printf("--- Operation privilege mirage started ---\n\n");
   fabricate_civilian_document(orig_path);
   execute_root_replication(orig_path, copy_path);
   attempt_unauthorized_modification(copy_path);
   initiate_rm_eradication(copy_path);
   remove(orig_path);
   printf("\n --- Operation completed ---\n");
   return 0;
}
