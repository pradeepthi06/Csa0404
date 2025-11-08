#include <stdio.h>
#include <stdlib.h>

struct Block {
    int blockNumber;
    char data[256];  // Block data
};

int main() {
    FILE *file;
    struct Block block;
    int blockNumber;
    int indexBlock[100] = {0}; // Index table (simulated)

    // Open or create a file for writing blocks
    file = fopen("indexed_file.txt", "w+b");
    if (file == NULL) {
        printf("Error opening the file.\n");
        return 1;
    }

    // Write data blocks sequentially and store their positions in indexBlock
    printf("Enter blocks (Enter 0 as block number to stop):\n");
    while (1) {
        printf("Block Number: ");
        scanf("%d", &block.blockNumber);

        if (block.blockNumber == 0)
            break;

        printf("Data: ");
        scanf(" %[^\n]", block.data);

        long pos = ftell(file); // Current position before writing
        fwrite(&block, sizeof(struct Block), 1, file);
        indexBlock[block.blockNumber] = (int)pos;
    }

    printf("\nAll blocks written successfully.\n");

    // Read specific blocks using the index block
    while (1) {
        printf("\nEnter block number to read (0 to exit): ");
        scanf("%d", &blockNumber);

        if (blockNumber == 0)
            break;

        if (indexBlock[blockNumber] == 0) {
            printf("Block not found.\n");
        } else {
            fseek(file, indexBlock[blockNumber], SEEK_SET);
            fread(&block, sizeof(struct Block), 1, file);
            printf("\nBlock Number: %d\n", block.blockNumber);
            printf("Data: %s\n", block.data);
        }
    }

    fclose(file);
    return 0;
}

