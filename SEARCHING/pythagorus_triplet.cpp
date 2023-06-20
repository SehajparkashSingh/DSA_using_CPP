#include <iostream>
#include <cmath>
using namespace std;

//FINDS TRIPLETS WHERE A[i]^2 + A[j]^2 = A[k]^2 
void find_pythagorus_triplet(int *sorted_array,int n){
    for(int i=0;i<n;i++)
        sorted_array[i]*=sorted_array[i];
    for(int i=n-1;i>=2;i--){
        for(int lo_ind=0,high_ind=i-1;lo_ind<high_ind;){
            int sum=sorted_array[lo_ind]+sorted_array[high_ind];
            if(sum==sorted_array[i]){
                cout<<sqrt(sorted_array[lo_ind])<<"^2 + "<<sqrt(sorted_array[high_ind])<<"^2 ="<<sqrt(sorted_array[i])<<"^2"<<endl;
                break;
            }
            else if(sum<sorted_array[i])
                lo_ind++;
            else if(sum>sorted_array[i])
                high_ind--;
        }
    }
}
int main(){
    int n;
    cout<<"ENTER THE SIZE OF ARRAY:";
    cin>>n;
    int *arr=new int[n];
    cout<<"ENTER THE "<<n<<" WHOLE NUMBERS"<<":"<<endl;
    int max=-1;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    cout<<"PYTHAGORUS TRIPLET: ";
    find_pythagorus_triplet(arr,n);

}