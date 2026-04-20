#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MIN_USER_UID 1000
#define BUFFER_SIZE 256

void detect_civilian_intruders(const char *line, uid_t my_uid) {
   char name[64];
   char password[16];
   int uid, gid;
   if(sscanf(line, "%[^:]:%[^:]:%d%d", name, password, &uid, &gid) == 4) {
      if(uid >= MIN_USER_UID && (uid_t)uid != my_uid) {
        printf("[1] Alert! Regular user found: %s (UID: %d)\n", name, uid);
       }
    }
}
 
void initiate_identity_scan() {
   FILE *fp;
   char buffer[BUFFER_SIZE];
   uid_t current_uid = getuid();
   printf("--- Identity Scan Initiated (your UID: %u) --- \n", current_uid);
   fp = popen("getent passwd", "r");
   if(fp == NULL) {
     perror("Failed to execute command");
     exit(1);
   }
   int found_any = 0;
   while (fgets(buffer, sizeof(buffer), fp) != NULL) {
         detect_civilian_intruders(buffer, current_uid);
   }
   pclose(fp);
   printf("--- Scan completed ---\n");
}

int main() {
   initiate_identity_scan();
   return 0;
}
