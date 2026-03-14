#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void* thread_func(void* arg) {
 int thread_num = *(int*)arg;
 void* thread_heap = malloc(1024 * 1024);//1mb
 snprintf((char*)thread_heap, 1024, "Hello from thread %d", thread_num);
 sleep(2);
 free(thread_heap);
 return NULL;
}

void print_maps() {
 printf("\n-----/proc/self/maps------------\n");
 FILE *f = fopen("/proc/self/maps", "r");
 if(f == NULL) {
   perror("Errrr occured while opening /proc/self/maps");
   return;
  }
  char line[512];
  while (fgets(line, sizeof(line), f)) {
      printf("%s", line);
  }
  fclose(f);
  printf("-------------------\n\n");
}

int main() {
   printf("PID of process: %d\n", getpid());
   void *heap_ptr = malloc(10 * 1024 * 1024);//10mb
   if(!heap_ptr) {perror("malloc"); exit(1); }
   strcpy((char*)heap_ptr, "Data on heap");
   pthread_t thread1, thread2;
   int t1_id = 1;
   int t2_id = 2;
   pthread_create(&thread1, NULL, thread_func, &t1_id);
   pthread_create(&thread2, NULL, thread_func, &t2_id);
   size_t mmap_size = 20 * 1024 * 1024;//20mb
   void *mmap_ptr = mmap(NULL, mmap_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
   if(mmap_ptr == MAP_FAILED) {perror("mmap"); exit(1); }
   strcpy((char*)mmap_ptr, "Data in mmap");
   sleep(1);
  print_maps();
   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);
   free(heap_ptr);
   munmap(mmap_ptr, mmap_size);
   return 0;
}
