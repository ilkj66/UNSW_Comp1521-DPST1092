#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("input error");
        return 1;
    }
    FILE *file = fopen(argv[1], "w");
    if (file == NULL) {
        printf ("openfile error");
        return 1;
    }
    int first = atoi(argv[2]);
    int last = atoi(argv[3]);
    int i = first;
    while (i <= last) {
        fprintf(file,"%d\n",i);
        i++;
    }
    fclose(file);
    return 0;
}