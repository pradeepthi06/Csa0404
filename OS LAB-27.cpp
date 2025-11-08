#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char fn[100], pat[100], temp[500];
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", fn);

    printf("Enter the pattern to search: ");
    scanf("%s", pat);

    fp = fopen(fn, "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    printf("\nLines containing '%s':\n", pat);

    while (fgets(temp, sizeof(temp), fp) != NULL) {
        if (strstr(temp, pat)) { // check if pattern exists in line
            printf("%s", temp);
        }
    }

    fclose(fp);
    return 0;
}

