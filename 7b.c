#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int src, dest;
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead, bytesWritten;

    // Check arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        exit(1);
    }

    // Open source file
    src = open(argv[1], O_RDONLY);
    if (src < 0) {
        perror("Error opening source file");
        exit(1);
    }

    // Open destination file
    dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest < 0) {
        perror("Error opening destination file");
        close(src);
        exit(1);
    }

    // Copy loop
    while ((bytesRead = read(src, buffer, BUFFER_SIZE)) > 0) {
        bytesWritten = write(dest, buffer, bytesRead);

        if (bytesWritten != bytesRead) {
            perror("Write error");
            close(src);
            close(dest);
            exit(1);
        }
    }

    if (bytesRead < 0) {
        perror("Read error");
    }

    printf("File copied successfully\n");

    close(src);
    close(dest);

    return 0;
}

//gcc copy.c -o copy
//./copy file1.txt file2.txt