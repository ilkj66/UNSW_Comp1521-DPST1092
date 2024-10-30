#include "bit_rotate.h"

// return the value bits rotated left n_rotations
uint16_t bit_rotate(int n_rotations, uint16_t bits) {
    int BIT_SIZE = 16;

    n_rotations = n_rotations % BIT_SIZE;

    if (n_rotations < 0) {
        n_rotations = BIT_SIZE + n_rotations;
    }

    uint16_t result = (bits << n_rotations) | (bits >> (BIT_SIZE - n_rotations));
    
    return result;
}
