#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    
    const char *path = argv[1];
    struct stat statbuf;

    if (stat(path, &statbuf) != 0) {
        printf("0\n");
        return 0;
    }

    if (S_ISDIR(statbuf.st_mode)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}