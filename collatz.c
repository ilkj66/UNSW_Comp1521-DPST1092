#include <stdio.h>
#include <stdlib.h>

int alg(int *num) {
    printf("%d\n", *num);
    if (*num % 2 == 0) {
        *num = *num / 2;
    } else {
        *num = (*num * 3) + 1;
    }
    if (*num == 1) {
        return 1;
    } else {
        
        return alg(num);
    }
}


int main(int argc, char *argv[])
{
	(void) argc, (void) argv; // keep the compiler quiet, should be removed
    int num = atoi(argv[1]);
    if (num == 1) {
        printf("%d\n", num);
        return 0;
    }
    printf("%d\n", alg(&num));
	return EXIT_SUCCESS;
}
