#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

void print_permissions(const char *pathname, struct stat *s) {
    if (S_ISDIR(s->st_mode)) {
        printf("d");
    } else if (S_ISREG(s->st_mode)) {
        printf("-");
    } else {
        printf("?");
    }

    printf((s->st_mode & S_IRUSR) ? "r" : "-");
    printf((s->st_mode & S_IWUSR) ? "w" : "-");
    printf((s->st_mode & S_IXUSR) ? "x" : "-");

    printf((s->st_mode & S_IRGRP) ? "r" : "-");
    printf((s->st_mode & S_IWGRP) ? "w" : "-");
    printf((s->st_mode & S_IXGRP) ? "x" : "-");

    printf((s->st_mode & S_IROTH) ? "r" : "-");
    printf((s->st_mode & S_IWOTH) ? "w" : "-");
    printf((s->st_mode & S_IXOTH) ? "x" : "-");

    printf(" %s\n", pathname);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: No input files provided.\n");
        return 1;
    }

    struct stat s;

    for (int i = 1; i < argc; i++) {
        const char *pathname = argv[i];

        if (stat(pathname, &s) != 0) {
            perror("Error getting file status");
            printf("Error: %s\n", strerror(errno));
            continue;  
        }

        print_permissions(pathname, &s);
    }

    return 0;
}