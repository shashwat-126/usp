#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Signal handler
void handler(int signo) {
    printf("\nSIGINT caught! Custom handler executed.\n");

    // Reset SIGINT to default behavior
    signal(SIGINT, SIG_DFL);
}

int main() {
    struct sigaction sa;

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    // Register handler
    sigaction(SIGINT, &sa, NULL);

    while (1) {
        printf("Running... Press Ctrl+C\n");
        sleep(2);
    }

    return 0;
}