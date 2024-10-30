// generate the encoded binary for an addi instruction, including opcode and operands

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

#include "addi.h"

// return the encoded binary MIPS for addi $t,$s, i
uint32_t addi(int t, int s, int i) {
    //001000ssssstttttIIIIIIIIIIIIIIII
    uint32_t result = 0;
    result = result | ((0b001000) << 26);
    result = result | ((s & 0b11111) << 21);
    result = result | ((t & 0b11111) << 16);
    result = result | (i & 0xffff);
    return result; // REPLACE WITH YOUR CODE

}
