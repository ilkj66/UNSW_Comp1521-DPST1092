
#include <stdio.h>
#include <stdlib.h>

#define SERIES_MAX 30

int fib(int n);

int main(void) {
    //int fnum[SERIES_MAX];
    //fnum[0] = 0;
    //fnum[1] = 1;

    // Generate Fibonacci series
    //for (int i = 2; i < SERIES_MAX; i++) {
    //    fnum[i] = fnum[i - 1] + fnum[i - 2];
    //}

    int num;
    while (scanf("%d", &num) == 1) {
        if (num >= 0 && num < SERIES_MAX) {
            printf("%d\n", fib(num));
        }
    }

    return EXIT_SUCCESS;
}

int fib(int n) {
    if (n <= 1) {
        return n;
    }
    return fib(n - 1) + fib(n - 2);
}