#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    struct dirent *entry;
    DIR *dp = opendir(".");

    if (dp == NULL) {
        perror("opendir");
        return 1;
    }

    while ((entry = readdir(dp))) {
        printf("%s\n", entry->d_name);
    }

    closedir(dp);
    return 0;
}
