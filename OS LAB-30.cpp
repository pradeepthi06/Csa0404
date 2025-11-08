#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Thread function
void* func(void* arg) {
    printf("Inside the thread\n");
    pthread_exit(NULL);  // exits this thread
}

// Function demonstrating thread operations
void fun() {
    pthread_t ptid;

    // Create a new thread
    pthread_create(&ptid, NULL, &func, NULL);
    printf("This line may be printed before the thread terminates\n");

    // Compare thread IDs
    if (pthread_equal(ptid, pthread_self())) {
        printf("Threads are equal\n");
    } else {
        printf("Threads are not equal\n");
    }

    // Wait for the thread to finish
    pthread_join(ptid, NULL);
    printf("This line will be printed after thread ends\n");
}

int main() {
    fun();
    return 0;
}

