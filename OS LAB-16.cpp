#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct employee {
    int empno;
    char name[30];
    float salary;
};

void addRecord(FILE *fp) {
    struct employee e;
    printf("Enter Employee Number: ");
    scanf("%d", &e.empno);
    printf("Enter Name: ");
    scanf("%s", e.name);
    printf("Enter Salary: ");
    scanf("%f", &e.salary);
    fwrite(&e, sizeof(e), 1, fp);
    printf("Record added successfully.\n");
}

void displayRecords(FILE *fp) {
    struct employee e;
    rewind(fp);
    printf("\n--- Employee Details ---\n");
    while (fread(&e, sizeof(e), 1, fp)) {
        printf("Emp No: %d\tName: %s\tSalary: %.2f\n", e.empno, e.name, e.salary);
    }
}

void searchRecord(FILE *fp) {
    struct employee e;
    int empno, found = 0;
    printf("Enter Employee Number to Search: ");
    scanf("%d", &empno);
    rewind(fp);
    while (fread(&e, sizeof(e), 1, fp)) {
        if (e.empno == empno) {
            printf("Record Found:\nEmp No: %d\tName: %s\tSalary: %.2f\n", e.empno, e.name, e.salary);
            found = 1;
            break;
        }
    }
    if (!found)
        printf("Record not found.\n");
}

void modifyRecord(FILE *fp) {
    struct employee e;
    int empno, found = 0;
    long pos;
    printf("Enter Employee Number to Modify: ");
    scanf("%d", &empno);
    rewind(fp);
    while (fread(&e, sizeof(e), 1, fp)) {
        if (e.empno == empno) {
            found = 1;
            pos = ftell(fp) - sizeof(e);
            printf("Enter New Name: ");
            scanf("%s", e.name);
            printf("Enter New Salary: ");
            scanf("%f", &e.salary);
            fseek(fp, pos, SEEK_SET);
            fwrite(&e, sizeof(e), 1, fp);
            printf("Record modified successfully.\n");
            break;
        }
    }
    if (!found)
        printf("Record not found.\n");
}

int main() {
    FILE *fp;
    int choice;

    fp = fopen("employee.dat", "rb+");
    if (fp == NULL) {
        fp = fopen("employee.dat", "wb+");
        if (fp == NULL) {
            printf("Error opening file.\n");
            exit(1);
        }
    }

    while (1) {
        printf("\n--- RANDOM ACCESS FILE MENU ---\n");
        printf("1. Add Record\n2. Display Records\n3. Search Record\n4. Modify Record\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRecord(fp);
                break;
            case 2:
                displayRecords(fp);
                break;
            case 3:
                searchRecord(fp);
                break;
            case 4:
                modifyRecord(fp);
                break;
            case 5:
                fclose(fp);
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

