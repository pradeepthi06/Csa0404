#include <stdio.h>

// Function to sort array in ascending order
void sort(int a[], int n) {
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if(a[i] > a[j]) {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

// Function to sort array in descending order
void rsort(int a[], int n) {
    for(int i=0; i<n; i++) {
        for(int j=i+1; j<n; j++) {
            if(a[i] < a[j]) {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

// Best Fit Logic
void bestfit(int mp[], int p[], int m, int n) {
    int j = 0;
    for(int i=0; i<n; i++) {
        if(mp[i] > p[j]) {
            printf("\nProcess %d (size %d) fits in Partition %d (size %d)", j+1, p[j], i+1, mp[i]);
            mp[i] = mp[i] - p[j++];
            i = i - 1;
        }
    }
    for(int i=j; i<m; i++) {
        printf("\nProcess %d (size %d) must wait — no suitable partition available", i+1, p[i]);
    }
}

// First Fit Strategy
void firstfit(int mp[], int p[], int m, int n) {
    sort(mp, n);
    sort(p, m);
    bestfit(mp, p, m, n);
}

// Worst Fit Strategy
void worstfit(int mp[], int p[], int m, int n) {
    rsort(mp, n);
    sort(p, m);
    bestfit(mp, p, m, n);
}

int main() {
    int m, n, mp[20], p[20], ch;
    
    printf("Enter number of memory partitions: ");
    scanf("%d", &n);
    printf("Enter number of processes: ");
    scanf("%d", &m);

    printf("Enter memory partition sizes:\n");
    for(int i=0; i<n; i++) {
        scanf("%d", &mp[i]);
    }

    printf("Enter process sizes:\n");
    for(int i=0; i<m; i++) {
        scanf("%d", &p[i]);
    }

    printf("\n1. First Fit\n2. Best Fit\n3. Worst Fit\nEnter your choice: ");
    scanf("%d", &ch);

    switch(ch) {
        case 1: firstfit(mp, p, m, n); break;
        case 2: bestfit(mp, p, m, n); break;
        case 3: worstfit(mp, p, m, n); break;
        default: printf("Invalid choice!"); break;
    }

    return 0;
}
