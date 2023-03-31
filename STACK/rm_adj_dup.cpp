#include <iostream>
#include <cstring>
using namespace std;

void remove_adj_duplicates(char *a){
    int i,j;
    i=-1;     //works as stack pointer 
    j=0;      // to access every character of the string
    while(j<strlen(a)){
        if(i==-1 || a[i]!=a[j]){
            i++;
            a[i]=a[j];
            j++;
        }
        else{     //a[i]==a[j]
            i--;
            j++;
        }
    }
    a[i+1]='\0';       //mandatory to end the new shortened string
    return;
}
int main(){
    char a[]="abbacdd";
    cout<<"Initial string : "<<a<<endl;
    remove_adj_duplicates(a);
    cout<<"Final string : "<<a<<endl;
    return 0;
}