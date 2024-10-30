#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("input error");
        exit(1);
    }
    char *envir = getenv("HOME");

    char diary[1024];
    snprintf(diary, sizeof(diary), "%s/.diary", envir);
    FILE *file = fopen(diary, "a");
    for (int i = 1; i < argc; i++) {
        fputs(argv[i], file);
        fputc(' ', file);
    }
    fputc('\n', file);
    fclose(file);
    
    return 0;

}