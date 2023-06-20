#include <iostream>
using namespace std;

//An array is 3)-B#)7 if it is comprised of an increasing sequence 
//of integers followed immediately 
//by a decreasing sequence of integers.

//GETS PEAK ELEMENT POSITION
int find_peak(int a[],int low,int high){
    int mid=low+((high-low)/2);
    if(low==high){
        return low;
    }
    else if(low==high-1){
        return (a[low]>a[high])?low:high;
    }
    else if(a[mid]>a[mid-1] && a[mid]>a[mid+1]){
        return mid;
    }
    else if(a[mid]>a[mid-1]){
        return find_peak(a,mid+1,high);
    }
    else if(a[mid]>a[mid+1]){
        return find_peak(a,low,mid-1);
    }
} 
int binary_search_dec_order(int *a,int low,int high,int k){
    if(low<=high){
        int mid=low+(high-low)/2;
        if(a[mid]==k){
            return mid;
        }
        else if(a[mid]>k){
            return binary_search_dec_order(a,mid+1,high,k);
        }
        else if(a[mid]<k){
            return binary_search_dec_order(a,low,mid-1,k);
        }
    }
    else {
        return -1;
    }
}
int binary_search_inc_order(int *a,int low,int high,int k){
    if(low<=high){
        int mid=low+(high-low)/2;
        if(a[mid]==k){
            return mid;
        }
        else if(a[mid]<k){
            return binary_search_dec_order(a,mid+1,high,k);
        }
        else if(a[mid]>k){
            return binary_search_dec_order(a,low,mid-1,k);
        }
    }
    else {
        return -1;
    }
}
int bitonic_search(int *a,int n,int k){
    int peak=find_peak(a,0,n-1);  //log n
    if(a[peak]==k){
        return peak;
    }
    else if(k>=a[0] && k<=a[peak-1]){
        return binary_search_inc_order(a,0,peak-1,k);  //log n
    }
    else{
        return binary_search_dec_order(a,peak+1,n-1,k);   //log n
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
    cout<<bitonic_search(arr,n,k);
}