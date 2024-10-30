#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc < 3) {
        printf("input error");
        return 1;
    }
    FILE *file1 = fopen(argv[1], "r");
    FILE *file2 = fopen(argv[2], "w");
    int c;
    while ((c = fgetc(file1)) != EOF) {
        if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' 
        && c != 'A' && c != 'E' && c != 'I' && c != 'O' && c != 'U') {
            fputc(c, file2);
        } 
        
    }
    return 0;
}
