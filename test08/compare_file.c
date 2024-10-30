#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *file1, *file2;
    int byte1, byte2;
    long position = 0;

    file1 = fopen(argv[1], "rb");
    if (file1 == NULL) {
        perror("Error opening first file");
        exit(EXIT_FAILURE);
    }

    file2 = fopen(argv[2], "rb");
    if (file2 == NULL) {
        perror("Error opening second file");
        fclose(file1);
        exit(EXIT_FAILURE);
    }

    while (1) {
        byte1 = fgetc(file1);
        byte2 = fgetc(file2);

        if (byte1 == EOF && byte2 == EOF) {
            printf("Files are identical\n");
            break;
        }

        if (byte1 == EOF) {
            printf("EOF on %s\n", argv[1]);
            break;
        }
        if (byte2 == EOF) {
            printf("EOF on %s\n", argv[2]);
            break;
        }

        if (byte1 != byte2) {
            printf("Files differ at byte %ld\n", position);
            break;
        }

        position++;
    }

    fclose(file1);
    fclose(file2);

    return 0;
}