#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "add.h"

// return the MIPS opcode for add $d, $s, $t
uint32_t make_add(uint32_t d, uint32_t s, uint32_t t) {
    
    int mask = (1 << 5) - 1;

    return ((0x00000020 | ((d & mask) << 11)) | ((t & mask) << 16)) | ((s & mask) << 21); // REPLACE WITH YOUR CODE

}
