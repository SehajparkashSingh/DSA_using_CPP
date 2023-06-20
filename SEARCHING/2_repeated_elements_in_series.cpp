#include <iostream>
using namespace std;

//FOR NUMBERS B/W 1 TO N-2
void get_2_repeating_elements(int *a,int n){
    int *count=new int[n-1];
    for(int i=0;i<n;i++){
        if(count[a[i]]==1){
            cout<<a[i]<<" ";
        }
        else
            count[a[i]]=1;
    }
}

int main(){
    int n;
    cout<<"ENTER THE SIZE OF ARRAY:";
    cin>>n;
    int *arr=new int[n];
    cout<<"ENTER THE "<<n<<"  NATURAL NUMBERS"<<":"<<endl;
    //int max=-1;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        //if(max<arr[i])
        //    max=arr[i];
    }
    cout<<"ELEMENTS OCCURING TWICE IN THE SERIES ARE: ";
    get_2_repeating_elements(arr,n);
}