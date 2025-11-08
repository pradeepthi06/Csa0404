// worst_fit.c
#include <stdio.h>
#define MAX 10

int main(){
    int m, n;
    int blocks[MAX], process[MAX], alloc[MAX];

    printf("Enter no. of memory blocks: "); scanf("%d",&m);
    printf("Enter %d block sizes:\n", m);
    for(int i=0;i<m;i++) scanf("%d",&blocks[i]);

    printf("Enter no. of processes: "); scanf("%d",&n);
    printf("Enter %d process sizes:\n", n);
    for(int i=0;i<n;i++) { scanf("%d",&process[i]); alloc[i]=-1; }

    for(int i=0;i<n;i++){
        int worst = -1;
        for(int j=0;j<m;j++){
            if(blocks[j] >= process[i]){
                if(worst == -1 || blocks[j] > blocks[worst]) worst = j;
            }
        }
        if(worst != -1){
            alloc[i] = worst;
            blocks[worst] -= process[i];
        }
    }

    printf("Process No.\tProcess Size\tBlock Allocated\n");
    for(int i=0;i<n;i++){
        printf("%d\t\t%d\t\t", i+1, process[i]);
        if(alloc[i] != -1) printf("%d\n", alloc[i]+1);
        else printf("Not Allocated\n");
    }
    return 0;
}

