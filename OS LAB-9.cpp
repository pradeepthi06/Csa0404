#include <windows.h>
#include <stdio.h>
#include <string.h>

int main() {
    HANDLE hMapFile;
    char *buffer;

    // Create shared memory space
    hMapFile = CreateFileMapping(
        INVALID_HANDLE_VALUE,    // Use system memory
        NULL,                    // Default security
        PAGE_READWRITE,          // Read/write permission
        0,                       // Max size (high-order DWORD)
        1024,                    // Max size (low-order DWORD)
        "MySharedMemory"         // Shared memory name
    );

    buffer = (char*) MapViewOfFile(
        hMapFile,
        FILE_MAP_ALL_ACCESS,
        0, 0,
        1024
    );

    // Write to shared memory
    strcpy(buffer, "hello, shared memory");

    printf("Data written to shared memory: %s\n", buffer);

    // Read from shared memory (same process)
    printf("Data read from shared memory: %s\n", buffer);

    // Clean up
    UnmapViewOfFile(buffer);
    CloseHandle(hMapFile);

    return 0;
}
