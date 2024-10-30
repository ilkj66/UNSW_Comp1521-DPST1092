// Convert string of binary digits to 16-bit signed integer

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

#define N_BITS 16

int16_t sixteen_in(char *bits);

int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        printf("%d\n", sixteen_in(argv[arg]));
    }

    return 0;
}

//
// given a string of binary digits ('1' and '0')
// return the corresponding signed 16 bit integer
//
int16_t sixteen_in(char *bits) {

    // PUT YOUR CODE HERE
    int length = strlen(bits);
    int16_t result = 0;
    int k = 1;
    for (int i = 0; i < length; i++) {
        k = 1;
        result = result << 1;
        if (bits[i] == '1') {
            result = k | result;
        } 

    }
    

    return result;
}

