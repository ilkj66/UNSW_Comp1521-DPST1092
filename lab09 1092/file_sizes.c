#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: No input files provided.\n");
        return 1;
    }

    int file_number = argc - 1;
    struct stat s;
    long long total_size = 0;

    for (int i = 1; i <= file_number; i++) {
        const char *pathname = argv[i];
        FILE *file = fopen(pathname, "rb");

        if (file == NULL) {
            perror("Error opening file");
            printf("Error: %s\n", strerror(errno));
            continue;  // Continue to the next file instead of exiting
        }

        if (stat(pathname, &s) != 0) {
            // stat failed, handle error
            perror("Error getting file status");
            printf("Error: %s\n", strerror(errno));
            fclose(file);
            continue;  // Continue to the next file instead of exiting
        }

        printf("%s: %lld bytes\n", pathname, (long long)s.st_size);
        total_size += s.st_size;
        fclose(file);
    }

    printf("Total: %lld bytes\n", total_size);

    return 0;
}