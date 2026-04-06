#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 2048

void hunt_for_the_magic_word(const char *search_word, const char *filename) {
 FILE *scroll = fopen(filename, "r");
 if(scroll == NULL) {
  perror("Error: The ancient scroll could not be opened");
  return;
 }
 char line_buffer[MAX_LINE_LENGTH];
 int line_number = 1;
 int found_something = 0;
 printf(">>> Initiatinf the hunt for the artifact '%s' in '%s'....<<<\n\n", search_word, filename);
 while (fgets(line_buffer, sizeof(line_buffer), scroll) != NULL) {
   if(strstr(line_buffer, search_word)!= NULL) {
    printf("[Line %d]%s", line_number, line_buffer);
    found_something = 1;
   }
 }
 if(!found_something) {
    printf("\n>>>The artifact was not found in this realm. <<<\n");
  } else {
     printf("\n>>> Search quest completed successfully! <<<\n");
  }
  fclose(scroll);
}
int main(int argc, char *argv[]) {
   if(argc != 3) {
    printf("Error: Incorrect incantation!\n");
    printf("Usage: %s root <word_to_find> <filename>\n", argv[0]);
    printf("Example: %s root /etc/passwd\n", argv[0]);
    return EXIT_FAILURE;
   }
 printf("Booting up the manual grep simulation...\n\n");
 hunt_for_the_magic_word(argv[1], argv[2]);
 return EXIT_SUCCESS;
}
