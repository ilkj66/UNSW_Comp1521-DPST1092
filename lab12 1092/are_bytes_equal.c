#include<stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    FILE* file1 = fopen(argv[1], "r");
    FILE* file2 = fopen(argv[3], "r");

    fseek(file1, atoi(argv[2]), SEEK_SET);
    fseek(file2, atoi(argv[4]), SEEK_SET);

    int byte1 = fgetc(file1);
    int byte2 = fgetc(file2);

    if (byte1 == byte2 && byte1 != -1 && byte2 != -1) {
        printf("byte %d in %s and byte %d in %s are the same\n", atoi(argv[2]), argv[1], atoi(argv[4]), argv[3]);
    } else {
        printf("byte %d in %s and byte %d in %s are not the same\n", atoi(argv[2]), argv[1], atoi(argv[4]), argv[3]);
    }

    fclose(file1);
    fclose(file2);

    return 0;
}