#include <iostream>
using namespace std;

//FINDS THE MAX INDEX DIFFERENCE(j-i) FOR A[j]>A[i], j>i
int max_ind_diff(int *a,int n){
    int max_diff=-1;
    int *min_from_left_to_right=new int[n];
    int *max_from_right_to_left=new int[n];
    
    min_from_left_to_right[0]=a[0];
    for(int i=1;i<n;i++){
        min_from_left_to_right[i]=min(min_from_left_to_right[i-1],a[i]);
    }

    max_from_right_to_left[n-1]=a[n-1];
    for(int i=n-2;i>=0;i--){
        max_from_right_to_left[i]=max(max_from_right_to_left[i+1],a[i]);
    }
    
    int i=0;
    int j=0;
    while(j<n && i<n){
        if(min_from_left_to_right[i]<max_from_right_to_left[j]){
            max_diff=max(max_diff,j-i);
            j++;
        }
        else{
            i++;
        }
    }
    return max_diff;
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
    cout<<"MAX DIFFERENCE IN INDEX : ";
    cout<<max_ind_diff(arr,n);
}