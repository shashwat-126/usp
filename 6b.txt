#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    int fd;
    struct flock lock;
    char buffer[51];

    fd = open("sample.txt", O_RDWR);
    if (fd < 0) {
        perror("open failed");
        return 1;
    }

    // Find file size
    off_t size = lseek(fd, 0, SEEK_END);
    if (size == -1) {
        perror("lseek failed");
        close(fd);
        return 1;
    }

    // Define safe lock region (last 100 bytes or whole file)
    off_t lock_start = (size <= 100) ? 0 : size - 100;
    off_t lock_len   = (size < 100) ? size : 100;

    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = lock_start;
    lock.l_len = lock_len;
    lock.l_pid = getpid();

    // Check existing lock
    if (fcntl(fd, F_GETLK, &lock) == -1) {
        perror("fcntl F_GETLK failed");
        close(fd);
        return 1;
    }

    if (lock.l_type != F_UNLCK) {
        printf("Region is locked by process PID: %d\n", lock.l_pid);
    } else {
        printf("Region is not locked. Locking now...\n");

        // Apply lock
        lock.l_type = F_WRLCK;

        if (fcntl(fd, F_SETLK, &lock) == -1) {
            perror("fcntl F_SETLK failed");
            close(fd);
            return 1;
        }

        // Safe read last 50 bytes
        off_t read_start = (size <= 50) ? 0 : size - 50;

        if (lseek(fd, read_start, SEEK_SET) == -1) {
            perror("lseek read failed");
            close(fd);
            return 1;
        }

        int bytes = read(fd, buffer, 50);
        if (bytes < 0) {
            perror("read failed");
            close(fd);
            return 1;
        }

        buffer[bytes] = '\0';

        printf("Last %d bytes:\n%s\n", bytes, buffer);

        // Unlock region
        lock.l_type = F_UNLCK;

        if (fcntl(fd, F_SETLK, &lock) == -1) {
            perror("unlock failed");
            close(fd);
            return 1;
        }

        printf("Region unlocked\n");
    }

    close(fd);
    return 0;
}

//need modification on github
