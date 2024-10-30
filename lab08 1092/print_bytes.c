#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]){
    if (argc < 2) {
        printf ("input error");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    int character;
    long i = 0;
    while ((character = fgetc(file)) != EOF){
        if (isprint(character)) {
            printf("byte %4ld: %3d 0x%02x '%c'\n", i, character, character, character);
        } else {
            printf("byte %4ld: %3d 0x%02x\n", i, character, character);
        }
        i++;
    }
    fclose(file);
    return 0;
}