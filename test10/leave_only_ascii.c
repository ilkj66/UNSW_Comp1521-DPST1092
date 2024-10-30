#include <stdio.h>

int main(int argc, char* argv[]) {
    FILE* file = fopen(argv[1], "r");
    FILE* file_tep = fopen("temp_file", "w");
    int c;
    while ((c = fgetc(file)) != EOF) {
        if (c < 128 || c > 255) {
            fputc(c, file_tep);
        }
    }
    fclose(file);
    fclose(file_tep);
    FILE* file1 = fopen(argv[1], "w");
    FILE* file2 = fopen("temp_file", "r");
    while ((c = fgetc(file2)) != EOF) {
        fputc(c, file1);
    }
    fclose(file1);
    fclose(file2);
    return 0;
}