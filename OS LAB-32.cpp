#include <stdio.h>

int search(int arr[], int n, int x){
    for(int i=0;i<n;i++) if(arr[i]==x) return i;
    return -1;
}

int findLRU(int time[], int n){
    int i, min = time[0], pos = 0;
    for(i=1;i<n;i++) if(time[i]<min){ min=time[i]; pos=i; }
    return pos;
}

int main(){
    int frames = 3;
    int ref[] = {7,0,1,2,0,3,0,4,2,3,0,3,2};
    int n = sizeof(ref)/sizeof(ref[0]);
    int frame[10], time[10];
    for(int i=0;i<frames;i++) frame[i]=-1, time[i]=0;
    int page_faults=0, t=0;

    for(int i=0;i<n;i++){
        int page = ref[i];
        int idx = search(frame, frames, page);
        if(idx==-1){
            int freeIndex = -1;
            for(int j=0;j<frames;j++) if(frame[j]==-1){ freeIndex=j; break; }
            if(freeIndex!=-1){
                frame[freeIndex]=page; time[freeIndex]=++t;
            } else {
                int lru = findLRU(time, frames);
                frame[lru]=page; time[lru]=++t;
            }
            page_faults++;
        } else {
            time[idx]=++t; // update recently used timestamp
        }
        printf("%d : ", page);
        for(int j=0;j<frames;j++) printf("%d ", frame[j]);
        printf("\n");
    }
    printf("Total page faults = %d\n", page_faults);
    return 0;
}

