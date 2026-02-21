#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

volatile sig_atomic_t keep_running = 1;
long long count = 0;
void handle_sigxcpu(int sig) {
  printf("\n\n SIXCPU signal received. CPU time limit exceeded\n");
  printf("Total double tickets generated: %lld\n", count);
  keep_running = 0;
} 
void generate_numbers(int k, int n) {
 int nums[50];
 for (int i = 0; i < n; i++) {
   int j = i + rand() % (n-i);
   int temp = nums[i];
   nums[i] = nums[j];
   nums [j] = temp;
 }
}

int main() {
 signal(SIGXCPU, handle_sigxcpu);
 srand(time(NULL));
 printf("Lottery ticket generation started...\n");
 printf("The program will run at full capacity until CPU limit is reached\n");
 while (keep_running) {
  generate_numbers(7, 49);
  generate_numbers(6, 36);
  count++;
  if(count % 2000000 == 0) {
    printf("%lld tickets generated...\n", count);
  }
 }
 printf("Program terminated succesfully :)");
 return 0;
}
