#include <iostream>
using namespace std;

void swap(int *a,int i,int j);

//Places all the even numbers on the left and odd ones on the right 
void separate_even_odd(int *a,int n){
    int low_ind=0;
    int high_ind=n-1;
    while(low_ind<high_ind){
        while(a[low_ind]%2==0 && low_ind<high_ind){
            low_ind++;
        }
        while(a[high_ind]%2!=0 && low_ind<high_ind){
            high_ind--;
        }
        if(low_ind<high_ind){
            swap(a,low_ind,high_ind);
        }
        low_ind++;
        high_ind--;
    }
}
void swap(int *a,int i,int j){
    int temp=a[i];
    a[i]=a[j];
    a[j]=temp;
}

int main(){
    int n;
    cout<<"ENTER THE SIZE OF ARRAY:";
    cin>>n;
    int *arr=new int[n];
    cout<<"ENTER THE "<<n<<" NUMBERS"<<":"<<endl;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cout<<"ARRAY AFTER SEPARATION : ";
    separate_even_odd(arr,n);
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
}