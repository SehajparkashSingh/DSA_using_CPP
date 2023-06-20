#include <iostream>
using namespace std;

//WORKS ON ALL INTEGER VALUES
void triplet_with_sum_closest_2_zero(int *sorted_array,int n){
    int final_sum=INT_MAX;
    //int neg_sum=INT_MIN;
    int i,j,k;
    for(int s=0;s<n-2;s++){  
        for(int lo_ind=s+1,high_ind=n-1;lo_ind<high_ind;){
            int sum=sorted_array[s]+sorted_array[lo_ind]+sorted_array[high_ind];
            if(sum>0){
                if(sum<abs(final_sum)){
                    final_sum=sum;
                    i=s;
                    j=lo_ind;
                    k=high_ind;
                }
                high_ind--;
            }
            else if(sum<0){
                if(abs(sum)<abs(final_sum)){
                    final_sum=sum;
                    i=s;
                    j=lo_ind;
                    k=high_ind;
                }
                lo_ind++;
            }
            else{
                cout<<sorted_array[s]<<" + "<<sorted_array[lo_ind]<<" + "<<sorted_array[high_ind]<<" = "<<sum<<endl;
                return;
            }
        }
    }
    cout<<sorted_array[i]<<" + "<<sorted_array[j]<<" + "<<sorted_array[k]<<" = "<<final_sum<<endl;
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
    cout<<"PAIR WHOSE SUM IS CLOSEST TO ZERO : ";
    triplet_with_sum_closest_2_zero(arr,n);
}