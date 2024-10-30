#include <stdio.h>

int main(int argc, char *argv[]) {
	//(void) argc, (void) argv; // keep the compiler quiet, should be removed
    printf("Program name: %s\n", argv[0]);
    if (argc < 2) {
        printf("There are no other arguments\n");
    } else {
        printf("There are %d arguments:\n", argc - 1);
        int i = 1;
        while (i < argc) {
            printf("\tArgument %d is \"%s\"\n", i, argv[i]);
            i++;
        }

    }
	return 0;
}
