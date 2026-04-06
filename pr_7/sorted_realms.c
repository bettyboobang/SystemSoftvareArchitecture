#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int filter_realms_only(const struct dirent *entry) {
 if(entry->d_type != DT_DIR) {
    return 0;
  }
  if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
   return 0;
   }
 return 1;
}
void chronicle_the_ordered_realms(const char *path) {
 struct dirent **namelist;
 int number_of_realms;
 printf(">>> Consulting the alphabetically sorted archives of '%s'...<<<\n\n", path);
 number_of_realms = scandir(path, &namelist, filter_realms_only, alphasort);
 if(number_of_realms < 0) {
   perror("Error: the archives are sealed or corrupted");
   return;
 }
 for(int i = 0; i < number_of_realms; i++) {
   printf("[+] %s/\n", namelist[i]->d_name);
   free(namelist[i]);
 }
 free(namelist);
 printf("\n>>> The chronicles are complete! Found %d realms. <<<\n", number_of_realms);
}

int main() {
 printf("Booting up the Alphabetical Realm Sorter...\n");
 chronicle_the_ordered_realms(".");
 return EXIT_SUCCESS;
}
