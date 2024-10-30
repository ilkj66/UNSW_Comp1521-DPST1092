#include <pthread.h>
#include "thread_chain.h"
#include <stdio.h>

void *my_thread(void *data) {

    // *data -> *(int*)data
    int num = *(int*)data;

    thread_hello();

    if (num < 50) {

        // create the next hread
        pthread_t th_new;
        // num_2 -- the number of threads
        int num_2 = num + 1;
        // create
        pthread_create(&th_new, NULL, my_thread, &num_2);
        // wait
        pthread_join(th_new, NULL);
    }
    
    return NULL;
}

void my_main(void) {
    pthread_t thread_handle;
    // num_1 -- the number of start thread(1)
    int num_1 = 1;
    // 
    pthread_create(&thread_handle, NULL, my_thread, &num_1);
    // wait
    pthread_join(thread_handle, NULL);
    
}