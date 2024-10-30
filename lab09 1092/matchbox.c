#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "matchbox.h"

#define BYTE_LENGTH 8


struct packed_matchbox pack_matchbox(char *filename) {
    // TODO: complete this function!
    // You may find the definitions in matchbox.h useful.
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    uint16_t sequence_length;
    if (fread(&sequence_length, sizeof(uint16_t), 1, file) != 1) {
        perror("Error reading sequence length");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    char *sequence = (char *)malloc(sequence_length);
    if (!sequence) {
        perror("Error allocating memory for sequence");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    if (fread(sequence, sizeof(char), sequence_length, file) != sequence_length) {
        perror("Error reading sequence");
        free(sequence);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    size_t num_bytes = num_packed_bytes(sequence_length);

    uint8_t *packed_bytes = (uint8_t *)malloc(num_bytes);
    if (!packed_bytes) {
        perror("Error allocating memory for packed bytes");
        free(sequence);
        fclose(file);
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < num_bytes; i++) {
        packed_bytes[i] = 0;
    }

    for (uint16_t i = 0; i < sequence_length; i++) {
        uint8_t bit = (sequence[i] == '1') ? 1 : 0;
        packed_bytes[i / 8] |= (bit << (7 - (i % 8)));
    }

    free(sequence);

    fclose(file);

    struct packed_matchbox matchbox = {
        .sequence_length = sequence_length,
        .packed_bytes = packed_bytes
    };
    return matchbox;
}
