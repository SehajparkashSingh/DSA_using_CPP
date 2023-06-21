#include <iostream>
using namespace std;

//WORKS FOR NATURAL NUMBERS
void store_count(int *a,int n,int max){
    if(max>n){
        a=(int *)realloc(a,(max)*sizeof(int));
        for(int i=n;i<max;i++){
            a[i]=0;
        }
        n=max;
    }
    int pos=0;
    while(pos<n){
        int element_pos=a[pos]-1;
        if(a[pos]>0 && a[element_pos]>0){
            a[pos]=a[element_pos];
            a[element_pos]=-1;
        }
        else if(a[pos]>0){
            a[element_pos]--;
            a[pos]=0;
            pos++;
        }
        else{
            pos++;
        }
    }
}

int main(){
    int n;
    cout<<"ENTER THE SIZE OF ARRAY:";
    cin>>n;
    int *arr=new int[n];
    cout<<"ENTER THE "<<n<<" NATURAL NUMBERS"<<":"<<endl;
    int max=INT_MIN;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        if(max<arr[i]){
            max=arr[i];
        }
    }
    cout<<"ARRAY WITH COUNT OF EACH ELEMENT AT THE INDEX WHICH EQUALS TO THE ELEMENT : ";
    store_count(arr,n,max);
    n=(n>max)?n:max;
    for(int i=0;i<n;i++){
        cout<<"ELEMENT: "<<i+1<<" , COUNT: "<<-arr[i]<<endl;
    }
}