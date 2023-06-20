#include <iostream>
using namespace std;

//ACCEPS ALL INTEGERS AS INPUT
void sum_equal_2_k(int *sorted_array,int n,int k){
    
    for(int i=0;i<n-2;i++){
        for(int lo_ind=i+1,high_ind=n-1;lo_ind<high_ind;){
            int sum=sorted_array[i]+sorted_array[lo_ind]+sorted_array[high_ind];
            if(sum==k){
                cout<<sorted_array[i]<<" + "<<sorted_array[lo_ind]<<" + "<<sorted_array[high_ind]<<" = "<<k<<endl;
                break;
            }
            else if(sum<k)
                lo_ind++;
            else if(sum>k)
                high_ind--;
        }
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
    cout<<"TRIPLET WHOSE SUM EQUALS "<<k<<" : ";
    sum_equal_2_k(arr,n,k);
}