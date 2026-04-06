#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>

void decode_permissions_likeaboss(mode_t mode, chat *str) {
 strcpy(str, "-------");
 if(S_ISDIR(mode)) str[0] = 'd';
 if(S_ISCHR(mode)) str[0] = 'c';
 if(S_ISBLK(mode)) str[0] = 'b';
 if(S_ISLNK(mode)) str[0] = 'l';
 if(S_ISFIFO(mode)) str[0] = 'p';
 if(S_ISSOCK(mode)) str[0] = 's';

 if(mode & S_IRUSR) str[1] = 'r';
 if(mode & S_IWUSR) str[2] = 'w';
 if(mode & S_IXUSR) str[3] = 'x';

 if(mode & S_IRGRP) str[4] = 'r';
 if(mode & S_IWGRP) str[5] = 'w';
 if(mode & S_IXGRP) str[6] = 'x';

 if(mode & S_IROTH) str[7] = 'r';
 if(mode & S_IWOTH) str[8] = 'w';
 if(mode & S_IXOTH) str[9] = 'x';
}

void summon_file_metadata(const char *filename) {
 struct stat file_stats;
 if (lstat(filename, &file_stats) == -1) {
  perror("Error: The file spirits refuse to answer");
  return;
 }
 char permissions[11];
 decode_permissions_likeaboss(file_stats.st_mode, permissions);
 struct passwd *owner = getpwuid(file_stats.st_uid);
 struct group *grp = getgrgid(file_stats.st_gid);
 char time_str[256];
 struct tm *time_info = localtime(&file_stats.st_mtime);
 strftime(time_str, sizeof(time_str), "%b %d %H:%M", time_info);
 printf("%s %3lu %-8s %-8s %8ld %s %s\n", permissions, (unsigned long)file_stats.st_nlink, owner ? owner->pw_name :
 "unknown", grp ? grp->gr_name : "unknown", (long)file_stats.st_size, time_str, filename);
}
void reveal_the_secrets_ofdirectory(const char *path) {
 DIR *dir = opendir(path);
 if(dir == NULL) {
  perror("Error: Cannot breach the directory gates");
  return;
 }
 struct dirent *entry;
 printf(">>>Scaning the magical realm of '%s' <<<\n", path);
 printf("PERMISSIONS LINKS OWNER GROUP SIZE TIME  FILENAME\n");
  while ((entry = readdir(dir)) != NULL) {
    if(entry->d_name[0] != '.') {
       summon_file_metadata(entry->d_name);
   }
 }
}

int main() {
 printf("Booting up the manual ls -l simulation...\n\n");
 reveal_the_secrets_ofdirectory(".");
 return 0;
}
