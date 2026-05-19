#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

volatile sig_atomic_t magical_counter = 0;
volatile sig_atomic_t show_stats_flag = 0;
volatile sig_atomic_t time_to_say_goodbye = 0;

void signal_catcher_supreme(int signum) {
    if (signum == SIGUSR1) {
        magical_counter++; //increment the secret counter
    } else if (signum == SIGUSR2) {
        show_stats_flag = 1; //trigger the statistics reveal
    } else if (signum == SIGINT) {
        time_to_say_goodbye = 1; //trigger the termination prompt
    }
}

void setup_wizardry() {
    struct sigaction sa;
    sa.sa_handler = signal_catcher_supreme;
    sa.sa_flags = 0; 
    sigemptyset(&sa.sa_mask);

    //trap SIGUSR1 and check for errors
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        perror("Failed to tame SIGUSR1");
        exit(EXIT_FAILURE);
    }
    //trap SIGUSR2 and check for errors
    if (sigaction(SIGUSR2, &sa, NULL) == -1) {
        perror("Failed to tame SIGUSR2");
        exit(EXIT_FAILURE);
    }
    //trap SIGINT (Ctrl+C) and check for errors
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("Failed to tame SIGINT");
        exit(EXIT_FAILURE);
    }
}

int main() {
    //initialize signal handlers
    setup_wizardry();

    printf("Welcome to the Signal Tamer!\n");
    printf("My Process ID (PID) is: %d\n", getpid());
    printf("Open another terminal and use the 'kill' command to interact with me:\n");
    printf("  kill -SIGUSR1 %d -> Increment the magical counter\n", getpid());
    printf("  kill -SIGUSR2 %d -> Reveal the secret statistics\n", getpid());
    printf("  kill -SIGINT %d  -> Initiate termination (or just press Ctrl+C)\n", getpid());
    printf("\nWaiting for your commands...\n");

    //the main loop of destiny
    while (true) {
        //put the process to sleep until a signal arrives
        pause();

        //process flags set by the signal handler
        if (show_stats_flag) {
            printf("\n The magical counter currently holds the power of: %d\n", magical_counter);
            show_stats_flag = 0; //reset flag
        }

        if (time_to_say_goodbye) {
            char response;
            printf("\n Termination sequence initiated!\n");
            printf("Are you absolutely sure you want to quit? (y/n): ");

            //read the user's response safely
            int c;
            response = getchar();
            //clear the input buffer to prevent infinite loops on weird inputs
            while ((c = getchar()) != '\n' && c != EOF); 

            if (response == 'y' || response == 'Y') {
                printf("Goodbye, brave soul! Program terminating...\n");
                break; //exit the loop
            } else {
                printf("Termination aborted. Continuing the mission!\n");
                time_to_say_goodbye = 0; //reset flag and continue
            }
        }
    }

    return EXIT_SUCCESS;
}
