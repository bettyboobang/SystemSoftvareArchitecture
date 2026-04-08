#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#define DISK_NAME "virtual_disk.bin"
#define MAX_FILES 10
#define MAX_DATA_SIZE 1024

typedef struct {
 int is_used;
 char filename[32];
 int file_size;
 char data[MAX_DATA_SIZE];
} VirtualBlock;

void format_disk() {
  FILE *disk = fopen(DISK_NAME, "wb");
  if(!disk) {perror("[-] Error creating disk"); return; }
  VirtualBlock empty_block = {0};
  for (int i = 0; i < MAX_FILES; i++) {
      fwrite(&empty_block, sizeof(VirtualBlock), 1, disk);
  }
  fclose(disk);
  printf("[+] Virtual disk '%s' formatted successfully!\n", DISK_NAME);
}

void create_file() {
 FILE *disk = fopen(DISK_NAME, "rb+");
 if(!disk) {printf("[-] Disk not found. Please format first.\n"); return; }
 VirtualBlock block;
 char name[32], content[MAX_DATA_SIZE];
 printf("Enter new filename: ");
 scanf("%31s", name);
 int c;
 while ((c = getchar()) != '\n' && c != EOF);
 printf("Enter file content: ");
 fgets(content, MAX_DATA_SIZE, stdin);
 content[strcspn(content, "\n")] = 0;
 for (int i = 0; i < MAX_FILES; i++) {
     fread(&block, sizeof(VirtualBlock), 1, disk);
     if(block.is_used == 0) {
        block.is_used = 1;
        strncpy(block.filename, name, 31);
        block.file_size = strlen(content);
        strncpy(block.data, content, MAX_DATA_SIZE - 1);
        fseek(disk, i * sizeof(VirtualBlock), SEEK_SET);
        fwrite(&block, sizeof(VirtualBlock), 1, disk);
        printf("[+] File '%s' saved succesfully!\n", name);
        fclose(disk);
        return;
      }
  }
  printf("[-] Disk id full! Cannot create file.\n");
  fclose(disk);
}

void read_file() {
  FILE *disk = fopen(DISK_NAME, "rb");
  if(!disk) {printf("[-] Disk not found. \n"); return;}
  char name[32];
  printf("Enter filename to read: ");
  scanf("%31s", name);
  VirtualBlock block;
  for(int i = 0; i < MAX_FILES; i++) {
      fread(&block, sizeof(VirtualBlock), 1, disk);
      if(block.is_used == 1 && strcmp(block.filename, name) == 0) {
        printf("\n--- Content of '%s' ---\n", name);
        printf("%s\n", block.data);
        printf("-------------\n");
        fclose(disk);
        return;
      }
   }
   printf("[-] File '%s' not found.\n", name);
   fclose(disk);
}

void delete_file() {
 FILE *disk = fopen(DISK_NAME, "rb+");
 if(!disk) {printf("[-] Disk not found.\n"); return;}
 char name[32];
 printf("Enter filename to delete:");
 scanf("%31s", name);
 VirtualBlock block;
 for(int i = 0; i < MAX_FILES; i++) {
     fread(&block, sizeof(VirtualBlock), 1, disk);
     if(block.is_used == 1 && strcmp(block.filename, name) == 0) {
       block.is_used = 0;
       block.filename[0] = '\0';
       fseek(disk, i * sizeof(VirtualBlock), SEEK_SET);
       fwrite(&block, sizeof(VirtualBlock), 1, disk);
       printf("[+] File '%s' deleted. \n", name);
       fclose(disk);
       return;
     }
  }
  printf("[-] File '%s' not found.\n", name);
  fclose(disk);
}

void list_files() {
  FILE *disk = fopen(DISK_NAME, "rb");
  if(!disk) {printf("[-] Disk not found. \n"); return;}
  VirtualBlock block;
  printf("\n--- Files on Virtual Disk ---\n");
  int count = 0;
  for(int i = 0; i < MAX_FILES; i++) {
      fread(&block, sizeof(VirtualBlock), 1, disk);
      if(block.is_used == 1) {
        printf("- %s (%d bytes)\n", block.filename, block.file_size);
        count++;
      }
  }
  if(count == 0) printf("(Disk is empty)\n");
  printf("--------------\n");
  fclose(disk);
}

int main() {
  int choice;
  printf("Formatting new disk...\n");
  FILE *check = fopen(DISK_NAME, "rb");
  if(!check) {
    printf("Formating new disk...\n");
    format_disk();
  } else {
    fclose(check);
  }
  while(1) {
    printf("\n[1] List files [2] Create file [3] Read file [4] Delete file [5] Exit\n");
    printf("Choice: ");
    if(scanf("%d", &choice) != 1) break;
    switch(choice) {
       case 1: list_files(); break;
       case 2: create_file(); break;
       case 3: read_file(); break;
       case 4: delete_file(); break;
       case 5: printf("Shutting down VFS...\n"); return EXIT_SUCCESS;
       default: printf("Invalid choice!\n");
   }
  }
 return 0;
}
