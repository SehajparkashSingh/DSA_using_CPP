#include <iostream>
using namespace std;

//WORKS FOR ALL INTEGERS
//FINDS PAIRS WHERE A[i]+A[j]=K 
void sum_equal_2_k(int *sorted_array,int n,int k){
    
        for(int lo_ind=0,high_ind=n-1;lo_ind<high_ind;){
            int sum=sorted_array[lo_ind]+sorted_array[high_ind];
            if(sum==k){
                cout<<sorted_array[lo_ind]<<" + "<<sorted_array[high_ind]<<" = "<<k<<endl;
                break;
            }
            else if(sum<k)
                lo_ind++;
            else if(sum>k)
                high_ind--;
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
    cout<<"ENTER THE VALUE OF K"<<":";
    cin>>k;
    cout<<"PAIR WHOSE SUM EQUALS "<<k<<" : ";
    sum_equal_2_k(arr,n,k);
}