#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void listFilesRecursively(char *basePath) {
    char path[1000];
    struct dirent *dp;
    struct stat statbuf;
    DIR *dir = opendir(basePath);

    if (!dir) {
        return;
    }

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            sprintf(path, "%s/%s", basePath, dp->d_name);

            if (stat(path, &statbuf) != -1 && S_ISDIR(statbuf.st_mode)) {
                printf("\nDirectory: %s\n", path);
                listFilesRecursively(path);
            } else {
                printf("File: %s\n", path);
            }
        }
    }

    closedir(dir);
}

int main() {
    char basePath[1000];

    printf("Enter the path to the directory: ");
    scanf("%s", basePath);

    printf("Contents of the directory:\n");
    listFilesRecursively(basePath);

    return 0;
}
