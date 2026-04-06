#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int is_magical_c_scroll(const char *filename) {
 const char *dot = strrchr(filename, '.');
 if(!dot || dot == filename) return 0;
 return strcmp(dot, ".c") == 0;
}

void bestow_reading_blessing(const char *filename, struct stat *file_stat) {
 char responce;
 printf("\nArtifact found: '%s'\n", filename);
 printf("Grant 'read' permission to outsiders? (y/n): ");
 scanf("%c", &response);
 int c;
 while((c = getchar()) != '\n' && c != EOF);
 if(response == 'y' || response == 'Y') {
   if(chmod(filename, file_stat->st_mode | S_IROTH) == 0) {
     printf("[+] Blessing granted! Outsiders can now read '%s'.\n", filename);
   } else {
     perror("[-] Failed to alter the artifact`s magic wards");
   }
 } else {
     printf("[-] The artifact '%s' remains a secret.\n", filename);
 }
}

void scan_and_bless_scrolls() {
 DIR *dir = opendir(".");
 if(dir == NULL) {
   perror("Error: Cannot open the current realm");
   return;
 }
 struct dirent *entry;
 struct stat file_stat;
 uid_t my_uid = getuid();
 printf(">>> Searching for your personal C scrolls in this directory... <<<\n");
 while ((entry = readdir(dir)) != NULL) {
     if(is_magical_c_scroll(entry->d_name)) {
        if(stat(entry->d_name, &file_stat) == 0) {
           if(file_stat.st_uid == my_uid) {
              bestow_reading_blessing(entry->d_name, &file_stat);
            }
         }
       }
 }
 closedir(dir);
 printf("\n>>> The ritual of permissions is complete! <<<\n");
}

int main() {
 printf("Booting up the Interactive Permission Manager...\n\n");
 scan_and_bless_scrolls();
 return EXIT_SUCCESS;
}
