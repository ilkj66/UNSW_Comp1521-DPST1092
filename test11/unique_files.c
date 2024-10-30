#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc < 2) {
        return EXIT_SUCCESS;
    }

    ino_t inodes[1000];  
    int inode_count = 0;

    for (int i = 1; i < argc; i++) {
        struct stat file_stat;

        // Get file status
        if (stat(argv[i], &file_stat) != 0) {
            perror(argv[i]);
            continue;
        }

        ino_t current_inode = file_stat.st_ino;

        int found = 0;
        for (int j = 0; j < inode_count; j++) {
            if (inodes[j] == current_inode) {
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("%s\n", argv[i]);
            if (inode_count < 1000) {
                inodes[inode_count++] = current_inode;
            } else {
                fprintf(stderr, "Too many unique files, increase MAX_FILES\n");
                return EXIT_FAILURE;
            }
        }
    }
    return EXIT_SUCCESS;
}
