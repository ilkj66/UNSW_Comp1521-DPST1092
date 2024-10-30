#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "floats.h"

// Separate out the 3 components of a float
float_components_t float_bits(uint32_t f) {
    float_components_t components;

    components.sign = (f >> 31) & 0x1;
    components.exponent = (f >> 23) & 0xFF;
    components.fraction = f & 0x7FFFFF;

    return components;
}

// Return 1 if the float is NaN, 0 otherwise
int is_nan(float_components_t f) {
    return (f.exponent == 0xFF) && (f.fraction != 0);
}

// Return 1 if the float is positive infinity, 0 otherwise
int is_positive_infinity(float_components_t f) {
    return (f.sign == 0) && (f.exponent == 0xFF) && (f.fraction == 0);
}

// Return 1 if the float is negative infinity, 0 otherwise
int is_negative_infinity(float_components_t f) {
    return (f.sign == 1) && (f.exponent == 0xFF) && (f.fraction == 0);
}

// Return 1 if the float is zero or negative zero, 0 otherwise
int is_zero(float_components_t f) {
    return (f.exponent == 0) && (f.fraction == 0);
}
