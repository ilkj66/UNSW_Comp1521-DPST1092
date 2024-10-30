#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf ("error input");
        exit(1);
    }

    FILE *file = fopen(argv[1], "w");
    int input = atoi(argv[2]);

    for (int i = atoi(argv[2]); i <= atoi(argv[3]); i++, input++) {
        fputc(((input >> 8) & 0xff),file);
        fputc(input & 0xff,file);
    }

    fclose(file);
    return 0;
}