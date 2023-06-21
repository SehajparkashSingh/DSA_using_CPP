#include <iostream>
using namespace std;

void swap(int *a,int i,int j);

//PLACE ALL THE ZEROES FIRST, THEN 1s AND AT LAST 2s
void separate(int *a,int n){
    int low=0,mid=0,high=n-1;
    while(mid<high){
        int e=a[mid];
        switch(e){
            case 0:
                swap(a,low,mid);
                low++;
                mid++;
                break;
            case 1:
                mid++;
                break;
            case 2:
                swap(a,mid,high);
                high--;
                break;
        }
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
    cout<<"ENTER THE "<<n<<" 0s , 1s or 2s NUMBERS"<<":"<<endl;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cout<<"ARRAY AFTER SEPARATION : ";
    separate(arr,n);
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
}