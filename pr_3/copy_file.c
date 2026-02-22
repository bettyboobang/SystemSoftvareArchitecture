#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
 if(argc != 3) {
  printf("Program needs two arguments\n");
  return 1;
 }
 signal(SIGXFSZ, SIG_IGN);
 int fd_in = open(argv[1], O_RDONLY);
 if(fd_in < 0) {
   printf("Cant open file %s for reading\n", argv[1]);
   return 1;
 }
 int fd_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
 if(fd_out < 0) {
  printf("Cant open file %s for writing\n", argv[2]);
  close(fd_in);
  return 1;
 }
 char buffer[BUFFER_SIZE];
 ssize_t bytes_read, bytes_written;
 while((bytes_read = read(fd_in, buffer, BUFFER_SIZE) > 0) {
   bytes_written = write(fd_out, buffer, bytes_read);
   if(bytes_written == -1) {
     if(errno == EBIG) {
       printf("Error. File size limit exceeded while writing to %s!\n", argv[2]);
       printf("Copied only a part of a file.\n");
    } else {
      printf("An unknown error.\n");
    }
    break;
  }
 }
 if(bytes_read == -1) {
   printf("Error reading from file %s\n", argv[1]);
 } else if (bytes_written != -1) {
   printf("File succesfully copied from %s to %s\n", argv[1], argv[2]);
 }
 close(fd_in);
 close(fd_out);
 return 0;
}
