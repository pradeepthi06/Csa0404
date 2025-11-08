#include <stdio.h>
#include <stdlib.h>

struct Record {
    int recordNumber;
    char data[256]; // Adjust size as needed
};

int main() {
    FILE *file;
    struct Record record;
    int recordNumber;

    // Open file in write mode
    file = fopen("sequential_file.txt", "w");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Write records sequentially
    printf("Enter records (Enter 0 as record number to stop):\n");
    while (1) {
        printf("Record Number: ");
        scanf("%d", &record.recordNumber);

        if (record.recordNumber == 0)
            break;

        printf("Data: ");
        scanf(" %[^\n]", record.data);

        fwrite(&record, sizeof(struct Record), 1, file);
    }
    fclose(file);

    // Open file in read mode
    file = fopen("sequential_file.txt", "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Read records sequentially until requested record is found
    while (1) {
        printf("\nEnter the record number to read (0 to exit): ");
        scanf("%d", &recordNumber);

        if (recordNumber == 0)
            break;

        rewind(file); // Move file pointer to start

        while (fread(&record, sizeof(struct Record), 1, file)) {
            printf("\nRecord Number: %d\n", record.recordNumber);
            printf("Data: %s\n", record.data);
            if (record.recordNumber == recordNumber)
                break;
        }
    }

    fclose(file);
    return 0;
}

