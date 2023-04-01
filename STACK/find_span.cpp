#include <iostream>
using namespace std;

int *find_span(int *a,int size){
    int *span=(int *)malloc(size);
    int *rspan=span;
    *span=1;
    span++;
    a++;
    while(*a){
        if(*a>=*(a-1)){
            *span=*(span-1)+1;
        }
        else{
            *span=1;
        }
        span++;
        a++;
    }
    return rspan;
}
int main(){
    int arr[]={1,4,6,2,5,4,7,9};
    // cout<<sizeof(arr)/sizeof(int);
    int *span=find_span(arr,sizeof(arr));
    return 0;
}