#include <iostream>
using namespace std;

// WORKS FOR ONLY NATURAL NUMBERS
int most_frequent(int *a,int n,int max){
    int n1=n;
    if(max>n-1){
        a=(int *)realloc(a,(max+1)*sizeof(int));
        for(int i=n;i<=max;i++){
            a[i]=0;
        }
        n=max+1;
    }
    for(int i=0;i<n1;i++){
        a[a[i]%n]+=n;
    }
    int max_ind=-1;
    int max_val=0;
    for(int i=0;i<n;i++){
        if(a[i]/n>max_val){
            max_val=a[i]/n;
            max_ind=i;
        }
    }
    return max_ind;
}
int main(){
    int n;
    cout<<"ENTER THE SIZE OF ARRAY:";
    cin>>n;
    int *arr=new int[n];
    cout<<"ENTER THE "<<n<<"  NATURAL NUMBERS"<<":"<<endl;
    int max=-1;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        if(max<arr[i])
            max=arr[i];
    }
    cout<<"ELEMENT OCCURING MOST FREQUENTLY: "<<most_frequent(arr,n,max)<<endl;
}