#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void print_error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_error("Error: Invalid number of arguments. Usage: ./read_lit_file <filename>");
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        print_error("Error: File does not exist or cannot be opened.");
    }

    // Read and check the magic number
    char header[3];
    if (fread(header, 1, 3, file) != 3) {
        print_error("Failed to read magic");
    }

    if (header[0] != 0x4C || header[1] != 0x49 || header[2] != 0x54) {
        print_error("Error: Magic number is not correct.");
    }

    while (1) {
        int byte_count = fgetc(file);
        if (byte_count == EOF) {
            if (feof(file)) break;
            print_error("Failed to read record");
        }

        if (byte_count < '1' || byte_count > '8') {
            print_error("Invalid record length");
        }

        int num_bytes = byte_count - '0';
        unsigned char value[8] = {0};
        if (fread(value, 1, num_bytes, file) != num_bytes) {
            print_error("Failed to read record");
        }

        // Combine the bytes into a single value (little-endian)
        uint64_t result = 0;
        for (int i = 0; i < num_bytes; i++) {
            result |= ((uint64_t)value[i]) << (i * 8);
        }

        printf("%lu\n", result);
    }

    fclose(file);
    return 0;
}