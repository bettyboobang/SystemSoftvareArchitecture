#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

int main() {
 int fd, count = 0;
 char buf[10];
 signal(SIGXFSZ, SIG_IGN);
 fd = open("rolls.txt", O_WRONLY, O_CREAT, O_TRUNC, 0644);
 printf("Trowing the dice...\n");
 while(1) {
  int len = snprintf(buf, 10, "%d\n", (rand()%6)+1);
  if(write(fd, buf, len) == -1) {
     if(errno == EFBIG) {
       printf("Limit is reached. File is full.\n");
       printf("Throws made: %d\n");
     } else {
       printf("Another error.\n");
     }
     break;
   }
   count++;
 }
 close(fd);
 return 0;
}
