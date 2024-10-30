// count bits in a uint64_t

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

// return how many 1 bits value contains
int bit_count(uint64_t value) {
    // PUT YOUR CODE HERE
    uint64_t mask;
    int count = 0;
    for (int i = 0; i < 64; i++) {
        mask = 0x0000000000000001;
        mask = (mask << i) & value;
        if ((mask >> i) == 1) {
            count++;
        }
        
    }

    return count;
}
