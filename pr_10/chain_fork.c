#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int max_depth = 5;

    printf("Main process started (PID: %d)\n", getpid());

    for (int i = 1; i <= max_depth; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            printf("Step %d: created child process (PID: %d), parent (PID: %d)\n",
                   i, getpid(), getppid());
            
            if (i == max_depth) {
                printf(">>> Last process (PID: %d) has finished its task and is exiting.\n", getpid());
                exit(EXIT_SUCCESS);
            }
        } else {
            wait(NULL);
            printf("<<< Process (PID: %d) waited for child (PID: %d) and is exiting.\n",
                   getpid(), pid);
            
            exit(EXIT_SUCCESS); 
        }
    }

    return 0;
}
