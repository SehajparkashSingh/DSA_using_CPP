#include <iostream>
using namespace std;

//Finds the 1st occurance of 'k' in a sorted array
int find_1st_occurance(int *a,int low,int high,int k){
    if(low<high){
        int mid=low+(high-low)/2;
        if(low==high){
            if(a[mid]==k)
                return mid;
        }
        else if(low==high-1){
            if(a[low]==k)
                return low;
            else if(a[high]==k)
                return high;
        }
        else if(a[mid]==k && a[mid-1]<k){
            return mid;
        }
        else if(a[mid]>=k){
            return find_1st_occurance(a,low,mid,k);
        }
        else if(a[mid]<k){
            return find_1st_occurance(a,mid+1,high,k);
        }
    }
}

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

int no_of_occurances(int a[],int n,int k){
    int f_occurance=find_1st_occurance(a,0,n-1,k);   //log n
    int l_occurance=find_last_occurance(a,0,n-1,k);  //log n
    return l_occurance-f_occurance+1;                //O(1)
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
    cout<<"NO. OF OCCURANCES OF "<<k<<" : ";
    cout<<no_of_occurances(arr,n,k);
}