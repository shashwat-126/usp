#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd, fd_dup, fd_dup2;

    fd = open("sample.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    // Write using original fd
    write(fd, "Original FD\n", 12);

    // dup() → gets next available fd
    fd_dup = dup(fd);
    write(fd_dup, "Written using dup()\n", 20);

    // dup2() → force to specific fd (e.g., 5)
    fd_dup2 = dup2(fd, 5);
    write(fd_dup2, "Written using dup2()\n", 21);

    printf("Original FD: %d\n", fd);
    printf("dup FD: %d\n", fd_dup);
    printf("dup2 FD: %d\n", fd_dup2);

    close(fd);
    close(fd_dup);
    close(fd_dup2);

    return 0;
}