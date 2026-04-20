#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define REQUIRED_FIELDS 4

void analyze_account_matrix(const char *line) {
   char username[64] = {0};
   char password[64] = {0};
   int uid = -1, gid = -1;
   char safe_line[256];
   strncpy(safe_line, line, sizeof(safe_line) -1);
   safe_line[sizeof(safe_line) -1] = '\0';
   safe_line[strcspn(safe_line, "\n")] = 0;
   int parsed_fields = sscanf(safe_line, "%63[^:]:%63[^:]:%d%d", username, password, &uid, &gid);
   if(parsed_fields == REQUIRED_FIELDS) {
      printf("[+] Valid entry  : User '%s' (UID: %d)\n)", username, uid);
   } else {
      printf("[-] Anomaly detected: Corrupted data stream!\n");
      printf(" -> Raw data  : \"%s\"\n", safe_line);
      printf(" -> Error     : Expected %d fields, but parsed only %d.\n", REQUIRED_FIELDS, parsed_fields);
   }
}

void simulate_nss_failure() {
   printf("--- Operation: Data corruption protocol ---\n\n");
   const char *healthy_stream = "bettyboobang:x:1000:1000:chikawa,,,/home/chikawa:/bin/bash\n";
   const char *truncated_stream = "brokenuser:x:100\n";
   const char *type_mismatch = "alienuser:x:NOT_A_NUMBER:1002::/home/alien:/bin/bash\n";
   const char *missing_delimeter = "mutantuserx:1005:1005::/home/mutant:/bin/bash\n";
   printf("[*] Injecting healthy stream...\n");
   analyze_account_matrix(truncated_stream);
   printf("\n[*] Injecting truncated stream...\n");
   analyze_account_matrix(truncated_stream);
   printf("\n[*] Injecting type mismatch stream...\n");
   analyze_account_matrix(type_mismatch);
   printf("\n[*] Injecting missing delimiter stream...\n");
   analyze_account_matrix(missing_delimeter);
   printf("\n--- Protocol concluded ---\n");
}

int main() {
   simulate_nss_failure();
   return 0;
}
