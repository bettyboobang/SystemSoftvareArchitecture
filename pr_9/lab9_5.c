#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define TARGET_FILE "/tmp/classified_artifact.txt"

void evaluate_clearance_level(const char *stage_description) {
   printf("\n[*] Access check phase: %s\n", stage_description);
   if(access(TARGET_FILE, R_OK) == 0) {
      printf("[+] REad access: GRANTED\n");
   } else { 
      printf("[-] REad access: DENIED\n");
   }
   if(access(TARGET_FILE, W_OK) == 0) {
     printf("[+] Write access: GRANTED\n");
   } else {
     printf("[-] Write access: dENIED");
   }
}

void forge_classified_artifact() {
   printf("[*] Forging classified artifact at: %s\n", TARGET_FILE);
   FILE *fp = fopen(TARGET_FILE, "w");
   if(fp == NULL) {
      perror("[-] Failed to forge artifact");
      exit(1);
   }
   fprintf(fp, "Top secret data payload.\n");
   fclose(fp);
   printf("[+] Artifact forged successfully.\n");
}

void invoke_supreme_override() {
   printf("\n[*] Invoking supreme override...\n");
   printf("[*] You may be asked for your sudo password.\n");
   if(system("sudo chown root:root " TARGET_FILE) == 0) {
      printf("[+] Ownership successfully transfered to root\n");
   } else {
      printf("[-] Override failed.\n");
      exit(1);
   }
}

void manipulate_access_matrix(const char *permissions, const char *desc) {
    printf("\n[*] Manipulating access matrix (sudo chmod %s) - %s...\n", permissions, desc);
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "sudo chmod %s %s", permissions, TARGET_FILE);
    system(cmd);
}

void clean_up_evidence() {
   printf("\n[*] Cleaning up evidence...\n");
   system("sudo rm -f "  TARGET_FILE);
   printf("[+] Trace eradicated.\n");
}

int main() {
   printf("---- Operation: permission shifter started ---\n\n");
   forge_classified_artifact();
   evaluate_clearance_level("Initial creation(you are owner)");
   invoke_supreme_override();
   manipulate_access_matrix("600", "Root only RW");
   evaluate_clearance_level("Owned by root, permissions 600");
   manipulate_access_matrix("644", "Root RW, others read-only");
   evaluate_clearance_level("Owned by root, permissions 644");
   manipulate_access_matrix("666", "Everyone RW");
   evaluate_clearance_level("Owned by root, permissions 666");
   clean_up_evidence();
   printf("\n --- Operation completed ---\n");
   return 0;
}
