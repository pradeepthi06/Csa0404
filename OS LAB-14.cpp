#include <stdio.h>
#include <stdlib.h>

// Function to copy file content
void copy() {
    FILE *source, *destination;
    char ch;

    source = fopen("source.txt", "r");
    if (source == NULL) {
        printf("Error: Cannot open source.txt for reading.\n");
        return;
    }

    destination = fopen("destination.txt", "w");
    if (destination == NULL) {
        printf("Error: Cannot create destination.txt.\n");
        fclose(source);
        return;
    }

    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, destination);
    }

    fclose(source);
    fclose(destination);
    printf("File copied successfully.\n");
}

// Function to create a file
void createFile() {
    FILE *fp = fopen("source.txt", "w");
    if (fp == NULL) {
        printf("Error creating file.\n");
        return;
    }
    fprintf(fp, "This is a test file created in the single-level directory program.\n");
    fclose(fp);
    printf("File created successfully.\n");
}

// Function to delete a file
void deleteFile() {
    if (remove("source.txt") == 0)
        printf("File deleted successfully.\n");
    else
        printf("Error deleting file (file may not exist).\n");
}

int main() {
    int n;
    printf("1. Create\t2. Copy\t3. Delete\nEnter your choice: ");
    scanf("%d", &n);

    switch (n) {
        case 1:
            createFile();
            break;
        case 2:
            copy();
            break;
        case 3:
            deleteFile();
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    return 0;
}
