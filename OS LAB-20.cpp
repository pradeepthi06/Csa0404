#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;
pthread_mutex_t mutex;
int readCount = 0;
int data = 0;  // Shared resource

void* writer(void* arg) {
    int writer_id = *(int*)arg;

    sem_wait(&wrt); // Wait for access
    data++; // Writing operation
    printf("Writer %d is writing... updated data = %d\n", writer_id, data);
    sleep(1);
    sem_post(&wrt); // Release access

    return NULL;
}

void* reader(void* arg) {
    int reader_id = *(int*)arg;

    pthread_mutex_lock(&mutex);
    readCount++;
    if (readCount == 1)
        sem_wait(&wrt); // First reader locks writer
    pthread_mutex_unlock(&mutex);

    printf("Reader %d is reading... data = %d\n", reader_id, data);
    sleep(1);

    pthread_mutex_lock(&mutex);
    readCount--;
    if (readCount == 0)
        sem_post(&wrt); // Last reader releases writer
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t read[5], write[3];
    int reader_ids[5] = {1, 2, 3, 4, 5};
    int writer_ids[3] = {1, 2, 3};

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // Create threads (writers and readers)
    pthread_create(&write[0], NULL, writer, &writer_ids[0]);
    pthread_create(&read[0], NULL, reader, &reader_ids[0]);
    pthread_create(&read[1], NULL, reader, &reader_ids[1]);
    pthread_create(&write[1], NULL, writer, &writer_ids[1]);
    pthread_create(&read[2], NULL, reader, &reader_ids[2]);
    pthread_create(&read[3], NULL, reader, &reader_ids[3]);
    pthread_create(&write[2], NULL, writer, &writer_ids[2]);
    pthread_create(&read[4], NULL, reader, &reader_ids[4]);

    // Wait for all threads
    for (int i = 0; i < 3; i++)
        pthread_join(write[i], NULL);
    for (int i = 0; i < 5; i++)
        pthread_join(read[i], NULL);

    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);

    printf("\nFinal data value = %d\n", data);
    return 0;
}
