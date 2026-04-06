#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void map_the_endless_labyrinths(const char *base_path, int depth) {
 DIR *dir = opendir(base_path);
 if(dir == NULL) {
   return;
 }
 struct dirent *entry;
 char new_path[2048];
 while((entry = readdir(dir)) != NULL) {
   if(strcmp(entry->d_name, ".") ==0 || strcmp(entry->d_name, "..") == 0) {
     continue;
   }
  for (int i = 0; i < depth; i++) {
    printf("   ");
  }
  if(entry->d_type == DT_DIR) {
    printf("[+] %s/\n", entry->d_name);
   } else {
    printf("| %s\n", entry->d_name);
   }
   if (entry->d_type == DT_DIR) {
    snprintf(new_path, sizeof(new_path), "%s/%s", base_path, entry->d_name);
    map_the_endless_labyrinths(new_path, depth +1);
 }
 closedir(dir);
}

int main() {
 printf("Booting up the Recursive Labyrinth Mapper...\n");
 printf(">>> Mapping the entire realm starting form '.' <<<\n\n");
 map_the_endless_labyrinths(".", 0);
 printf("\n>>> The labyrinth has been fully charted! <<<\n");
 return EXIT_SUCCESS;
}
