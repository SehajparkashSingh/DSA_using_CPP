#include <iostream>
using namespace std;

//IN THE GIVEN INPUT, JUST ONE ELEMENT OCCURS ODD NO. OF TIMES
//WORKS ON ALL INTEGER VALUES
int element_with_odd_occurance(int *a,int n){
    int x=a[0];
    for(int i=1;i<n;i++){
        x^=a[i];
    }
    return x;
}
int main(){
    int n;
    cout<<"ENTER THE SIZE OF ARRAY:";
    cin>>n;
    int *arr=new int[n];
    cout<<"ENTER THE "<<n<<" NUMBERS"<<":"<<endl;
    //int max=-1;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        //if(max<arr[i])
        //    max=arr[i];
    }
    cout<<"ELEMENT OCCURING ODD TIMES FROM IS: "<<element_with_odd_occurance(arr,n)<<endl;
}