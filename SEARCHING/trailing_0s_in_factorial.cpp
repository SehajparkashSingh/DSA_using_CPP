#include <iostream>
using namespace std;

int trailing_zeroes(int n){
    if(n>0){
        if(n<5){
            return 0;
        }
        else{
            int count=0;
            for(int i=5;n/i>0;i*=5){
                count+=n/i;
            }
            return count;
        }
    }
}
int main(){
    int n;
    cout<<"ENTER THE NATURAL NUMBER:";
    cin>>n;
    cout<<"NO. OF TRAILING ZEROES IN "<<n<<"! : ";
    cout<<trailing_zeroes(n);
}