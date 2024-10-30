#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("input error");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    int i = 0;
    int c;
    while (i < argc - 2) {
        fseek(file, atoi(argv[i + 2]), SEEK_SET);
        c = fgetc(file);
        if (isprint(c)) {
            printf("%-2d - 0x%02X - '%c'\n", c, c, c);
        } else {
            printf("%-2d - 0x%02X - '.'\n", c, c);
        }
        
        i++;
    }
    fclose(file);
    return 0;
}