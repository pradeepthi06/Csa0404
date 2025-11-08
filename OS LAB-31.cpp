#include <stdio.h>
#define MAX_REF 50

int main() {
    int frames = 3;
    int ref[] = {7,0,1,2,0,3,0,4,2,3,0,3,2};
    int n = sizeof(ref)/sizeof(ref[0]);
    int frame[10], i, j, k, page_faults = 0;
    for(i=0;i<frames;i++) frame[i] = -1;
    int front = 0; // index to replace (FIFO)

    printf("Reference string: ");
    for(i=0;i<n;i++) printf("%d ", ref[i]);
    printf("\n\nFrame status after each reference:\n");

    for(i=0;i<n;i++){
        int found = 0;
        for(j=0;j<frames;j++) if(frame[j]==ref[i]) { found=1; break;}
        if(!found){
            frame[front] = ref[i];
            front = (front+1)%frames;
            page_faults++;
        }
        printf("%2d : ", ref[i]);
        for(k=0;k<frames;k++) printf("%d ", frame[k]);
        printf("\n");
    }
    printf("\nTotal page faults = %d\n", page_faults);
    return 0;
}

