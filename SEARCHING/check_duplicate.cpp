#include <iostream>
using namespace std;

//WORKS FOR ONLY NATURAL NUMBERS
bool check_if_duplicate(int *a,int n,int max){
    if(max>n-1){
        a = (int*) realloc(a, (max+1)*sizeof(int));
        for(int i=n;i<=max;i++){
            a[i]=INT_MAX;
        }
    }
    for(int i=0;i<n;i++){
        if(a[abs(a[i])]<0){
            return true;
        }
        else{
            a[abs(a[i])]*=-1;
        }
    }
    return false;
}
int main(){
    int n;
    cout<<"ENTER THE SIZE OF ARRAY:";
    cin>>n;
    int *arr=new int[n];
    cout<<"ENTER THE "<<n<<"  NATURAL NUMBERS"<<":"<<endl;
    int max=-1;
    for(int i=0;i<n;i++){
        cin>>arr[i];
        if(max<arr[i])
            max=arr[i];
    }
    cout<<"IS THERE ANY DUPLICATE ELEMENT: "<<(check_if_duplicate(arr,n,max)?"YES":"NO")<<endl;

}