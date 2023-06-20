#include <iostream>
using namespace std;

//For natural no. series
int missing_element_using_sum(int *a,int n){ 
    int sum=(n*(n+1))/2;
    int org_sum=0;
    for(int i=0;i<n;i++){
        org_sum+=a[i];
    }
    return sum-org_sum;
}
int missing_element_using_xor(int *a,int n){
    int x=a[0];
    int y=1;
    for(int i=1;i<n;i++){
        x^=a[i];
    }
    for(int i=2;i<=n;i++){
        y^=i;
    }
    return x^y;
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
    cout<<"ELEMENT MISSING FROM THE SERIES IS: "<<missing_element_using_sum(arr,n)<<endl;
    cout<<"ELEMENT MISSING FROM THE SERIES IS: "<<missing_element_using_xor(arr,n)<<endl;

}