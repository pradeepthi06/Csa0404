#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    char filename[] = "file.txt";

    // 0664 = rw-rw-r-- (user & group read/write, others read only)
    int new_permissions = 0664;

    if (chmod(filename, new_permissions) == 0) {
        printf("File permissions changed successfully to rw-rw-r--.\n");
    } else {
        perror("chmod");
        return 1;
    }

    return 0;
}

