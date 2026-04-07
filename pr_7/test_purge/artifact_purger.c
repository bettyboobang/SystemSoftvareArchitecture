#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

void decide_artifact_fate(const char *filename) {
 char response;
 printf("Artifact found: '%s'\n", filename);
 printf("Cast this artifact into the void (delete)? (y/n/q to quit): ");
 scanf("%c", &response);
 int c;
 while ((c = getchar()) != '\n' && c != EOF);
 if(response == 'q' || response == 'Q') {
  printf("\n>>> The ritual of destruction has been safely aborted. <<<\n");
 }
 else if(response == 'y' || response == 'Y'){
  if(unlink(filename) == 0) {
     printf("[+] The artifact '%s' has been successfully obliterated.\n\n", filename);
   } else {
    perror("[-] Failed to destroy the artifact");
    printf("\n");
   }
 }
 else{
   printf("[-] The artifact '%s' is spared.\n\n", filename);
 }
} 
void initiate_purge_protocol() {
  DIR *dir = opendir(".");
  if(dir == NULL) {
     perror("Error: Cannot open the current realm");
     return;
  }
  struct dirent *entry;
  printf(">>> Initiating th Purge Protocol in the current directory... <<<\n\n");
  while ((entry == readdir(dir)) != NULL) {
    if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
       continue;
     }
    if(entry->d_type == DT_REG) {
       decide_artifact_fate(entry->d_name);
     }
  }
   closedir(dir);
   printf(">>> THE Purge Protocol has Concluded. <<<\n");
}

int main() {
 printf("Booting up the Interface Artifact Purger...\n");
 printf("Warning! This tool wields real destructiva power! Deleted files cannot be restored!\n\n");
 initiate_purge_protocol();
 return EXIT_SUCCESS;
}

