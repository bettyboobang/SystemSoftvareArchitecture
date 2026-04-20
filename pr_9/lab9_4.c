#include <stdio.h>
#include <stdlib.h>

void reveal_true_identity() {
   printf("\n[*] Querying the oracle for current username...\n");
   printf("[+] You are currently logged in as: ");
   fflush(stdout);
   system("whoami");
}

void enumerate_group_affiliations() {
   printf("\n[*] Extracting detailed acount matrix and group affiliations (id command)...\n");
   printf("[+] Notice the multiple groups listed at the end of the output:\n");
   fflush(stdout);
   system("id");
}

int main() {
   printf("--- Operation: identyty matrix started ---\n");
   reveal_true_identity();
   enumerate_group_affiliations();
   printf("\n--- Operation completed ---\n");
   return 0;
}
