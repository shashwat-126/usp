#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;

    // Set umask (mask out write permission for group & others)
    umask(0022);

    // Create file with full permissions (will be masked by umask)
    fd = open("testfile.txt", O_CREAT | O_WRONLY, 0777);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    close(fd);

    printf("File created with umask applied.\n");

    // Change permissions using chmod
    if (chmod("testfile.txt", 0644) == 0)
        printf("Permissions changed using chmod.\n");
    else
        perror("chmod failed");

    return 0;
}