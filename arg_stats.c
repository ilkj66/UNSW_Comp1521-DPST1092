
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        
        return 1; 
    }

    int set[argc - 1];
    int i = 0;

    while (i < argc - 1) {
        set[i] = atoi(argv[i + 1]);
        i++;
    }

    int max = set[0], min = set[0];
    int sum = 0, prod = 1;

    for (int k = 0; k < argc - 1; k++) {
        if (set[k] > max) {
            max = set[k];
        } else if (set[k] < min) {
            min = set[k];
        }
        sum += set[k];
        prod *= set[k];
    }

    int mean = sum / (argc - 1); 

    printf("MIN:  %d\n", min);
    printf("MAX:  %d\n", max);
    printf("SUM:  %d\n", sum);
    printf("PROD: %d\n", prod);
    printf("MEAN: %d\n", mean);

    return 0;
}