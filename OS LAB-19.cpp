#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t lock;   // mutex lock variable
int counter = 0;        // shared resource

// Function executed by each thread
void* process(void* arg) {
    int id = *(int*)arg;

    pthread_mutex_lock(&lock);  // enter critical section
    printf("Thread %d has entered the critical section.\n", id);

    int temp = counter;
    temp++;
    sleep(1);                   // simulate processing delay
    counter = temp;

    printf("Thread %d is leaving the critical section. Counter = %d\n", id, counter);
    pthread_mutex_unlock(&lock); // leave critical section

    return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    int id1 = 1, id2 = 2, id3 = 3;

    // initialize the mutex
    pthread_mutex_init(&lock, NULL);

    // create threads
    pthread_create(&t1, NULL, process, &id1);
    pthread_create(&t2, NULL, process, &id2);
    pthread_create(&t3, NULL, process, &id3);

    // wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("\nFinal Counter Value = %d\n", counter);

    // destroy the mutex
    pthread_mutex_destroy(&lock);

    return 0;
}
