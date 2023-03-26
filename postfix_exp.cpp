#include <iostream>
#include <string.h>
#include <stdint.h>

using namespace std;

void hello(int n){
    cout<<n<<" "<<endl;
}
void hello(char a){
    cout<<a<<endl;
}
int main(){
    hello(7);
    char a[]={10+'0',2+'0','+',3+'0',4+'0','*','+'};
    for(int i=0;i<7;i++){
        cout<<a[i]<<" "; 
    }
    //cout<<endl<<int(a[0])+int(a[1])<<endl;
    cout<<endl<<a[1]-48<<endl;
    int num[7];
    int j=0;
   for(int i=0; i<7; i++)
   {
      if(a[i]>='0' && a[i]<='9')
      {
         num[j] = a[i];
         num[j] = num[j] - 48;
         j++;
      }
   }
    for(int i=0; i<j; i++)
         cout<<num[i]<<" ";
}