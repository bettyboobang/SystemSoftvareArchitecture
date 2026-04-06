#include <stdio.h>
#include <stdlib.h>
#define LINES_PER_PAGE 20
#define MAX_LINE_LENGTH 2048

void hold_the_gates_until_user_ready() {
 printf("\033[7m--- Press ENTER to unveil more secrets ---\033[0m");
 int c;
 while ((c = getchar()) != '\n'&& c != EOF);
}

void paginate_the_ancient_scroll(const char *filename) {
 FILE *scroll = fopen(filename, "r");
 if(scroll == NULL) {
   printf("Error: Failed to unroll the scroll");
   return;
  }
  printf("\n>>> Unveiling the contents of: %s <<<\n\n", filename);
  char line_buffer[MAX_LINE_LENGTH];
  int line_count = 0;
  while (fgets(line_buffer, sizeof(line_buffer), scroll)!= NULL) {
    printf("%s", line_buffer);
    line_count++;
    if(line_count >= LINES_PER_PAGE) {
       hold_the_gates_until_user_ready();
       line_count = 0;
    }
  }
 fclose(scroll);
 printf("\n>>> Reached the end of %s <<<\n", filename);
}

int main(int argc, char *argv[]) {
  if(argc < 2) {
     printf("Error: No scrolls provided for the reading ritual.\n");
     printf("Usage: %s <file1> <file2>...\n", argv[0]);
     return EXIT_FAILURE;
   }
 printf("Booting up the manual 'more' simulation...\n");
 for(int i = 1; i < argc; i++) {
   paginate_the_ancient_scroll(argv[i]);
  }
 printf("\n>>> All reading quests have been completed\n <<<");
 return EXIT_SUCCESS;
}

