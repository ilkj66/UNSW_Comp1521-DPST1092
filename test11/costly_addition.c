#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

void increment_and_sleep(void *arg);

void costly_addition(int num)
{
    pthread_t threads[num];

    for (int i = 0; i < num; i++) {
        if (pthread_create(&threads[i], NULL, (void *(*)(void *))increment_and_sleep, NULL) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < num; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }
}