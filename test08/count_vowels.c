#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("input error");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    int c;
    int count = 0;
    while ((c = fgetc(file)) != EOF) {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            count++;
        } else if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}