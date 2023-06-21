#include <iostream>
using namespace std;

//FINDS THE INDEX OF 'K' IN NXN MATRIX
//EACH ROW IS IN INCREASING ORDER AND
//EACH COLUMN IS IN INCREASING ORDER
int *get_index(int **a,int n,int m,int k){    //O(N)
    if(n>0 && m>0){
        if(k==a[0][m-1]){
            int *ind=new int[2];
            ind[0]=0;
            ind[1]=m-1;
            return ind;
        }
        else if(k<a[0][m-1]){
            int *ind=get_index(a,n,m-1,k);
            return ind;
        }
        else if(k>a[0][m-1]){
            int *ind=get_index(a+1,n-1,m,k);
            ind[0]+=1;
            return ind;
        }
    }
    else {
        int *ind=new int[2];
        ind[0]=-1;
        ind[1]=-1;
        return ind;
    }
}
int main(){
    int n;
    cout<<"ENTER THE SIZE OF MATRIX:";
    cin>>n;
    int **arr=new int*[n];
    for(int i=0;i<n;i++){
        arr[i]=new int[n];
    }
    cout<<"ENTER THE "<<n<<"x"<<n<<" NUMBERS"<<":"<<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)
            cin>>arr[i][j];
    }
    int k;
    cout<<"ENTER THE ELEMENT TO BE SEARCHED"<<":";
    cin>>k;
    cout<<"INDEX OF "<<k<<" : ";
    cout<<"ROW: "<<get_index(arr,n,n,k)[0]<<" , COL: "<<get_index(arr,n,n,k)[1];
}