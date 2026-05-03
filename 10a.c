#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    pid_t pid;

    // Step 1: Fork
    pid = fork();
    if (pid < 0) {
        exit(1);
    }
    if (pid > 0) {
        // Parent exits
        exit(0);
    }

    // Step 2: Create new session
    if (setsid() < 0) {
        exit(1);
    }

    // Step 3: Set file permissions
    umask(0);

    // Step 4: Change working directory
    chdir("/");

    // Step 5: Close standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Example daemon work loop
    while (1) {
        // You can write logs to a file here
        sleep(5);
    }

    return 0;
}