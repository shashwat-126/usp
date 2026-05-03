#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    char path[1024];

    dir = opendir(".");  // current directory
    if (dir == NULL) {
        perror("opendir failed");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s", entry->d_name);

        if (stat(path, &fileStat) == 0) {
            if (S_ISREG(fileStat.st_mode) && fileStat.st_size == 0) {
                if (remove(path) == 0)
                    printf("Removed empty file: %s\n", path);
                else
                    perror("remove failed");
            }
        }
    }

    closedir(dir);
    return 0;
}