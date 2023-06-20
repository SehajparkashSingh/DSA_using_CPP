#include <iostream>
using namespace std;

//WORKS FOR A CONTIGUOUS RANGE OF NUMBERS
//IN THIS CASE, 1 TO N-1
//ONLY ONE NO. SHOULD OCCUR EVEN TIMES IN THE INPUT
int element_with_even_occurance(int *a,int n){
    int x=a[0];
    for(int i=1;i<n;i++){
        x^=a[i];
    }
    for(int i=1;i<=n-1;i++){
        x^=i;
    }
    return x;
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
    cout<<"ELEMENT OCCURING EVEN TIMES FROM IS: "<<element_with_even_occurance(arr,n)<<endl;
}