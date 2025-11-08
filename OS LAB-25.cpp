#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

extern int errno;

int main() {
    int fd;

    // Try opening file "foo.txt" for reading (creates if not exists)
    fd = open("foo.txt", O_RDONLY | O_CREAT, 0644);

    printf("fd = %d\n", fd);

    if (fd == -1) {
        printf("Error Number: %d\n", errno);
        perror("Program");
    } else {
        printf("File opened successfully.\n");
        close(fd);
    }

    return 0;
}

