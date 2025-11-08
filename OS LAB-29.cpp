#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty = 10;  // buffer size
int x = 0;

void wait(int *s) {
    (*s)--;
}

void signal(int *s) {
    (*s)++;
}

void producer() {
    wait(&mutex);
    wait(&empty);
    signal(&full);
    x++;
    printf("\nProducer produces item %d", x);
    signal(&mutex);
}

void consumer() {
    wait(&mutex);
    wait(&full);
    signal(&empty);
    printf("\nConsumer consumes item %d", x);
    x--;
    signal(&mutex);
}

int main() {
    int n;

    printf("1. Press 1 for Producer");
    printf("\n2. Press 2 for Consumer");
    printf("\n3. Press 3 for Exit\n");

    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &n);

        switch (n) {
            case 1:
                if ((mutex == 1) && (empty != 0)) {
                    producer();
                } else {
                    printf("\nBuffer is full!");
                }
                break;

            case 2:
                if ((mutex == 1) && (full != 0)) {
                    consumer();
                } else {
                    printf("\nBuffer is empty!");
                }
                break;

            case 3:
                exit(0);
                break;

            default:
                printf("\nInvalid choice!");
        }
    }

    return 0;
}

