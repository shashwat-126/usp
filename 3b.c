#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir failed");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {

        if (stat(entry->d_name, &fileStat) == 0) {

            printf("Inode: %ld\n", fileStat.st_ino);
            printf("File Name: %s\n", entry->d_name);
            printf("Size: %ld bytes\n", fileStat.st_size);
            printf("Links: %ld\n", fileStat.st_nlink);
            printf("Owner UID: %d\n", fileStat.st_uid);
            printf("Last Modified: %s", ctime(&fileStat.st_mtime));
            printf("---------------------------\n");
        }
    }

    closedir(dir);
    return 0;
}