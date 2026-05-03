#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char buffer[21];
    off_t size;

    fd = open("sample.txt", O_RDONLY);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    // i. Read first 20 characters
    read(fd, buffer, 20);
    buffer[20] = '\0';
    printf("First 20 characters:\n%s\n\n", buffer);

    // ii. Seek to 10th byte from beginning
    lseek(fd, 10, SEEK_SET);
    read(fd, buffer, 20);
    buffer[20] = '\0';
    printf("From 10th byte (20 chars):\n%s\n\n", buffer);

    // iii. Seek 10 bytes ahead from current position
    lseek(fd, 10, SEEK_CUR);
    read(fd, buffer, 20);
    buffer[20] = '\0';
    printf("After seeking 10 bytes ahead (20 chars):\n%s\n\n", buffer);

    // iv. Display file size
    size = lseek(fd, 0, SEEK_END);
    printf("File size: %ld bytes\n", size);

    close(fd);
    return 0;
}