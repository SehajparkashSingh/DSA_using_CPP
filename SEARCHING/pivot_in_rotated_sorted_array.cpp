#include <iostream>
using namespace std;

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
int main(){
    int n;
    cout<<"ENTER THE SIZE OF ARRAY:";
    cin>>n;
    int *arr=new int[n];
    cout<<"ENTER THE "<<n<<" NUMBERS"<<":"<<endl;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cout<<"INDEX WHERE THE PIVOT ELEMENT OCCURS: ";
    cout<<find_pivot(arr,0,n-1);
}