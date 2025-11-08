#include <stdio.h>
#include <limits.h>

int predict(int frame[], int frames, int ref[], int n, int index){
    int i,j, farthest = index, res = -1;
    for(i=0;i<frames;i++){
        int j;
        for(j=index;j<n;j++) if(frame[i]==ref[j]) break;
        if(j==n) return i; // not used again
        if(j>farthest){ farthest=j; res=i; }
    }
    return (res==-1)?0:res;
}

int main(){
    int frames = 3;
    int ref[] = {7,0,1,2,0,3,0,4,2,3,0,3,2};
    int n = sizeof(ref)/sizeof(ref[0]);
    int frame[10];
    for(int i=0;i<frames;i++) frame[i]=-1;
    int page_faults=0, i,j;

    for(i=0;i<n;i++){
        int page=ref[i]; int found=0;
        for(j=0;j<frames;j++) if(frame[j]==page){ found=1; break;}
        if(!found){
            int placed=0;
            for(j=0;j<frames;j++) if(frame[j]==-1){ frame[j]=page; placed=1; break;}
            if(!placed){
                int idx = predict(frame, frames, ref, n, i+1);
                frame[idx]=page;
            }
            page_faults++;
        }
        printf("%d : ", page);
        for(j=0;j<frames;j++) printf("%d ", frame[j]);
        printf("\n");
    }
    printf("Total page faults = %d\n", page_faults);
    return 0;
}

