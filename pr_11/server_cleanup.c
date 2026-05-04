#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>

int global_socket_fd = -1;
int global_temp_file_fd = -1;
const char *temp_file_path = "/tmp/my_app_temp.tmp";

void safe_print(const char *msg) {
    write(STDOUT_FILENO, msg, strlen(msg));
}

void cleanup_and_exit_handler(int signum) {
    safe_print("\n[Signal] Signal received. Starting safe resource cleanup...\n");

    if (global_socket_fd != -1) {
        close(global_socket_fd);
        safe_print("[Cleanup] Socket closed.\n");
    }

    if (global_temp_file_fd != -1) {
        close(global_temp_file_fd);
        safe_print("[Cleanup] Temporary file descriptor closed.\n");
    }
    
    if (unlink(temp_file_path) == 0) {
        safe_print("[Cleanup] Temporary file deleted.\n");
    }

    safe_print("[Warning] Stream buffers are not flushed to prevent deadlocks.\n");

    safe_print("[Exit] Process terminated gracefully (_exit).\n");
    _exit(1);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = cleanup_and_exit_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    printf("Creating socket...\n");
    global_socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    printf("Creating temporary file...\n");
    global_temp_file_fd = open(temp_file_path, O_CREAT | O_RDWR, 0666);

    printf("Buffered stdout data (no newline) - this will be lost upon signal!");
    
    while(1) {
        sleep(1);
    }

    return 0;
}
