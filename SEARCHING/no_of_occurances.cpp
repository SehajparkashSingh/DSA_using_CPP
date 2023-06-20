#include <iostream>
using namespace std;

//Finds the last occurance of 'k' in a sorted array
int find_last_occurance(int *a,int low,int high,int k){
    if(low<high){
        int mid=low+(high-low)/2;
        if(low==high-1){
            if(a[high]==k)
                return high;
            else if(a[low]==k)
                return low;
        }
        else if(a[mid]==k && a[mid+1]>k){
            return mid;
        }
        else if(a[mid]>k){
            return find_last_occurance(a,low,mid-1,k);
        }
        else if(a[mid]<=k){
            return find_last_occurance(a,mid,high,k);
        }
    }
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
    int k;
    cout<<"ENTER THE ELEMENT TO BE SEARCHED"<<":";
    cin>>k;
    cout<<"INDEX WHERE "<<k<<" LAST OCCURS: ";
    cout<<find_last_occurance(arr,0,n-1,k);
}