#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, size, seek_time = 0;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int request_queue[n];
    printf("Enter the disk request queue:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &request_queue[i]);

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    printf("Enter total disk size (maximum track number): ");
    scanf("%d", &size);

    // Sort the request queue
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (request_queue[i] > request_queue[j]) {
                int temp = request_queue[i];
                request_queue[i] = request_queue[j];
                request_queue[j] = temp;
            }
        }
    }

    // Find the index where head is located relative to the request queue
    int index = 0;
    for (int i = 0; i < n; i++) {
        if (head < request_queue[i]) {
            index = i;
            break;
        }
    }

    printf("\nC-SCAN Disk Scheduling:\n");
    printf("Head Movement Sequence: %d", head);

    // Move from head to the end (right side)
    for (int i = index; i < n; i++) {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];
        printf(" -> %d", head);
    }

    // Move from last track to end of disk
    if (head != size - 1) {
        seek_time += abs((size - 1) - head);
        head = size - 1;
        printf(" -> %d", head);
    }

    // Jump from end of disk to beginning (0)
    seek_time += abs(head - 0);
    head = 0;
    printf(" -> %d", head);

    // Continue from start to the remaining requests (left side)
    for (int i = 0; i < index; i++) {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);

    return 0;
}

