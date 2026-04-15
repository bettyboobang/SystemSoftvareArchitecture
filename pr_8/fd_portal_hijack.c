#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define SECRET_LOG "hijacked_output.txt"

void demonstrate_blind_clone_dup() {
   printf("Phase 1: The blind clone(dup)\n");
   int original_fd = open(SECRET_LOG, O_CREAT | O_WRONLY | O_TRUNC, 0644);
   if(original_fd < 0) {
     perror("FATAL: Failed to open the target file");
     exit(EXIT_FAILURE);
   }
   printf("Opened the file. The original file descriptor is: %d\n", original_fd);
   int cloned_fd = dup(original_fd);
   printf("Executed dup(). The system blindly assigned the lowest free FD: %d\n", cloned_fd);
   char *msg = "[dup] System wrote this using the randomly assigned clone FD.\n";
   write(cloned_fd, msg, strlen(msg));
   close(original_fd);
   close(cloned_fd);
}

void demonstrate_targeted_hijack_dup2() {
   printf("Phase 2: The targeted hijack (dup2)\n");
   int file_fd = open(SECRET_LOG, O_WRONLY | O_APPEND);
   int real_stdout = dup(1);
   printf("Executing dup2(). Forsing FD 1 to point to our file...\n");
   fflush(stdout);
   if(dup2(file_fd, 1) < 0) {
     perror("Fatal: Hijack failed");
     exit(EXIT_FAILURE);
   }
   printf("[dup2] Successful hijack! If you are reading this in the text file, dup2 worked perfectly.\n");
   printf("[dup2] All standard output is now secretly routed here.\n");
   fflush(stdout);
   dup2(real_stdout, 1);
   printf("Hijack reversed! We are back in the main terminal.\n");
   close(file_fd);
   close(real_stdout);
}

int main() {
   printf("=== Terminal hijack protocol initiated ===\n");
   demonstrate_blind_clone_dup();
   demonstrate_targeted_hijack_dup2();
   printf("\n=== Mission Accomplished. Check the file: %s ===\n", SECRET_LOG);
   return 0;
}
