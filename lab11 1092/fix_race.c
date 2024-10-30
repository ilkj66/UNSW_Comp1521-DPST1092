//! fix the data race in the below program!


/// You are permitted to add standard headers (useful for atomics)
#include <pthread.h>
#include <stdio.h>
#include <stdatomic.h>


// method 1
/// You are permitted to modify the type of
/// this global variable (useful for atomics)
// int global_counter = 0;

/// You are permitted to create another global
/// variable (useful for mutex)

// pthread_mutex_t -- lock
// PTHREAD_MUTEX_INITIALIZER -- initialize a lock (global variable)

// pthread_mutex_t global_counter_lock = PTHREAD_MUTEX_INITIALIZER;


//method 2

atomic_int global_counter = 0;

/// You are permitted to modify this function
/// (will be necessary for both mutex and atomics)
void perform_increment(void) {

    // method 1
    // pthread_mutex_lock(&global_counter_lock);

    //global_counter = global_counter + 1;


    // pthread_mutex_unlock(&global_counter_lock);


    // method 2
    global_counter += 1;
    // global_counter++
    // it can not be "global_counter = global_counter + 1"


}


///
/// DO NOT CHANGE ANY CODE BELOW THIS POINT
///

void *thread_run(void *data) {
    int n_increments = * (int *) data;

    for (int i = 0; i < n_increments; i++) {
        perform_increment();
    }

    return NULL;
}


int get_global_counter(void) {

    return global_counter;
}