#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("input error");
        return 0;
    }

    FILE* file = fopen(argv[1], "r");
    int byte;
    int i = 0;
    while ((byte = fgetc(file)) != EOF) {
        if (byte >= 128 && byte <= 255) {
            printf("%s: byte %d is non-ASCII\n", argv[1], i);
            return 0;
        }
        i++;
    }
    printf("%s is all ASCII\n", argv[1]);
    return 0;
}