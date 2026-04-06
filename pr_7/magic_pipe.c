#include <stdio.h>
#include <stdlib.h>

void summon_network_spirits(){
 FILE *rwho_source;
 FILE *more_destination;
 char buffer[1024];
 rwho_source = popen("rwho", "r");
 if(rwho_source == NULL) {
   perror("Error:Failed to summon the rwho spirits");
   exit(EXIT_FAILURE);
 }
 more_destination = popen("more", "w");
 if(more_destination == NULL) {
   perror("Error: Failed to awaken the more monster");
   pclose(rwho_source);
   exit(EXIT_FAILURE);
 }
 printf(">>> Initiating the epic data transfer from 'rwho' to 'more'...<<<\n\n");
 while (fgets(buffer, sizeof(buffer), rwho_source)!= NULL) {
  fputs(buffer, more_destination);
 }
 pclose(rwho_source);
 pclose(more_destination);
 printf("\n>>> The data transfer has been succesfully completed! <<<\n");
}
int main() {
 printf("Booting up the UNIX magic...\n");
 summon_network_spirits();
 return 0;
}
