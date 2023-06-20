#include <iostream>
using namespace std;

//Eg. input: 12 16 19 20 25 1 3 4 5 7 10 14

//GETS THE INDEX OF PIVOT ELEMENT IN A ROTATED SORTED ARRAY
int find_pivot(int *a,int low,int high){
    int mid=low+(high-low)/2;
    if(high==low){
        return low;
    }
    else if(low==high-1){
        return (a[low]>a[high])?low:high;
    }
    else if(a[mid]>a[mid+1]){
        return mid;
    }
    else if(a[low]>=a[mid]){
        return find_pivot(a,low,mid);
    }
    else if(a[low]<a[mid]){
        return find_pivot(a,mid,high);
    }
}
int binary_search(int *a,int low,int high,int k){
    if(high>=low){
        int mid=low+(high-low)/2;
        if(k==a[mid]){
            return mid;
        }
        else if(k>a[mid]){
            return binary_search(a,mid+1,high,k);
        }
        else if(k<a[mid]){
            return binary_search(a,low,mid-1,k);
        }
    }
    else{
        return -1;
    }
}
int search(int *a,int n,int k){
    int pivot=find_pivot(a,0,n-1);
    if(a[pivot]==k){
        return pivot;
    }
    else if(k<=a[n-1]){
        return binary_search(a,pivot+1,n-1,k);
    }
    else{
        return binary_search(a,0,pivot-1,k);
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
    cout<<"INDEX WHERE "<<k<<" OCCURS: ";
    cout<<search(arr,n,k);
}