#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    struct stat fileStat;

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if (stat(argv[1], &fileStat) < 0) {
        perror("stat error");
        return 1;
    }

    printf("File: %s\n", argv[1]);

    if (S_ISREG(fileStat.st_mode))
        printf("Type: Regular File\n");
    else if (S_ISDIR(fileStat.st_mode))
        printf("Type: Directory\n");
    else if (S_ISCHR(fileStat.st_mode))
        printf("Type: Character Device\n");
    else if (S_ISBLK(fileStat.st_mode))
        printf("Type: Block Device\n");
    else if (S_ISFIFO(fileStat.st_mode))
        printf("Type: FIFO (Pipe)\n");
    else if (S_ISLNK(fileStat.st_mode))
        printf("Type: Symbolic Link\n");
    else if (S_ISSOCK(fileStat.st_mode))
        printf("Type: Socket\n");
    else
        printf("Type: Unknown\n");

    return 0;
}

//gcc filetype.c -o filetype
//./filetype sample.txt