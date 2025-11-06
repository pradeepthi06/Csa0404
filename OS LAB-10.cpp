#include <stdio.h>
#include <windows.h>
#include <string.h>

int main() {
    HANDLE hMapFile;
    char *buffer;

    // Create Shared Memory (Message Queue Simulation)
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE, 
        NULL, 
        PAGE_READWRITE, 
        0, 
        1024, 
        "MyMessageQueue"
    );

    if (hMapFile == NULL) {
        printf("Error creating shared memory.\n");
        return 1;
    }

    buffer = (char*) MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0, 0,
        1024
    );

    if (buffer == NULL) {
        printf("Error mapping shared memory.\n");
        CloseHandle(hMapFile);
        return 1;
    }

    // PRODUCER: Write message
    strcpy(buffer, "Hello, message queue!");
    printf("Producer: Data sent to message queue: %s\n", buffer);

    // CONSUMER: Read message
    printf("Consumer: Data received from message queue: %s\n", buffer);

    // Close Shared Memory
    UnmapViewOfFile(buffer);
    CloseHandle(hMapFile);

    return 0;
}
