#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char *argv[]) {

    time_t now = time(NULL);

    for (int i = 1; i < argc; i++) {
        struct stat file_stat;
        if (stat(argv[i], &file_stat) == -1) {
            perror("stat");
            continue;
        }

        if (file_stat.st_atime > now || file_stat.st_mtime > now) {
            printf("%s has a timestamp that is in the future\n", argv[i]);
        }
    }

    return 0;
}