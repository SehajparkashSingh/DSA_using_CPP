#include <iostream>
using namespace std;

//Let A be an array of # distinct integers. Suppose A has the following property: 
//there exists an index 1 ≤ K ≤ N	# such that 'A[1], . . . , 'A[K] is an increasing sequence 
//and 'A[K +1], . . . , 'A[N] is a decreasing sequence. 
//Design and analyze an efficient algorithm for finding K.

int find_k(int a[],int low,int high){
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
        return find_k(a,mid+1,high);
    }
    else if(a[mid]>a[mid+1]){
        return find_k(a,low,mid-1);
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
    cout<<"INDEX WHERE THE PEAK ELEMENT OCCURS: ";
    cout<<find_k(arr,0,n-1);
}