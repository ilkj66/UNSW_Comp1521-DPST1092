#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

int bcd(int bcd_value);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        long l = strtol(argv[arg], NULL, 0);
        assert(l >= 0 && l <= 0x0909);
        int bcd_value = l;

        printf("%d\n", bcd(bcd_value));
    }

    return 0;
}

// given a  BCD encoded value between 0 .. 99
// return corresponding integer
int bcd(int bcd_value) {

    // PUT YOUR CODE HERE
    
    //int k = bcd_value / (256);
    //int t = bcd_value - (k * 256);
    int mask = (1 << 12) - 1;
    int k = bcd_value & ((1 << 4) - 1);


    return ((mask & bcd_value) >> 8) * 10 + k;
}

