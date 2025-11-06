#include <stdio.h>

int main() {
    int n, m, i, j, k;
    int alloc[10][10], max[10][10], avail[10];
    int need[10][10], finish[10], safeSeq[10];
    int count = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Maximum Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Calculate Need matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];

    for (i = 0; i < n; i++)
        finish[i] = 0;

    printf("\nNeed Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }

    int y = 0;
    for (k = 0; k < 5; k++) { // Repeat multiple times to check all processes
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    safeSeq[count++] = i;
                    for (y = 0; y < m; y++)
                        avail[y] += alloc[i][y];
                    finish[i] = 1;
                }
            }
        }
    }

    int flag = 1;
    for (i = 0; i < n; i++) {
        if (finish[i] == 0) {
            flag = 0;
            printf("\nSystem is not in safe state.\n");
            break;
        }
    }

    if (flag == 1) {
        printf("\nSystem is in a safe state.\nSafe sequence is: ");
        for (i = 0; i < n - 1; i++)
            printf("P%d -> ", safeSeq[i]);
        printf("P%d\n", safeSeq[n - 1]);
    }

    return 0;
}
