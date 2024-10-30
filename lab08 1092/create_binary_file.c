#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc < 3) {
        printf("input error");
        return 1;
    }
    FILE *file = fopen(argv[1], "w");
    int input;
    for (int i = 0; i < (argc - 2); i++) {
        input = atoi(argv[i + 2]);
        fputc(input,file);
    }
    fclose(file);
    return 0;
}