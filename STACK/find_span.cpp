#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

// int *find_span(int *a,int size){
//     int *span=(int *)malloc(size);
//     int *rspan=span;
//     *span=1;
//     span++;
//     a++;
//     while(*a){
//         if(*a>=*(a-1)){
//             *span=*(span-1)+1;
//         }
//         else{
//             *span=1;
//         }
//         span++;
//         a++;
//     }
//     return rspan;
// }
// void find_span(vector <int> a,int k){
//     int *span=(int *)malloc((a.size()*(sizeof(int))));
//     int *rspan=span;
//     span[0]=1;
//     int j=1;
//     //a++;
//     //cout<<a.size()<<" ";
//     for(int i=1;i<a.size();i++){
//         if(a[i]>a[i-1]) {
//             span[j]=span[j-1]+1;
//         }
//         else{
//             span[j]=1;
//         }
//         j++;
//     }
//     int count=0;
//     for(int i=0;i<a.size();i++){
//         cout<<span[i]<<" ";
//         }
//         cout<<endl;
//     for(int i=0;i<a.size();i++){
//         if(span[i]>=k){
//             count++;
//         }
//     }
//     cout<<count<<endl;
// }
// int main(){
//     vector <int> arr{5,3,5,7,8};
//     // cout<<sizeof(arr)/sizeof(int);
//     find_span(arr,3);
//     // for(int i=0;i<8;i++){
//     //     cout<<span[i]<<" ";
//     // }
//     return 0;
// }
// bool ans=true;
//     string out;
//     if(a>c || b>d){
//         out="No";
//         goto ss;
//     }
//     if(a==c && b==d){
//         out="Yes";
//         goto ss;
//     }
//     if(c<=d){
//         while(ans){
//             if(a<c){
//                 a=a+b;
//             }
//             if(a>c){
//                 out="No";
//                 break;
//             }
//             if(a==c){
//                 b=a+b;
//                 if(b>d){
//                   out="No";
//                   break;  
//                 }
//                 if(b==d){
//                     out="Yes";
//                     break;
//                 }
//             }
//         }
//     }
//     else{
//         while(1){
//             if(b<d){
//                 b=a+b;
//             }
//             if(b>d){
//                 out="No";
//                 break;
//             }
//             if(b==d){
//                 a=a+b;
//                 if(a>c){
//                   out="No";
//                   goto ss;  
//                 }
//                 if(a==c){
//                     out="Yes";
//                     break;
//                 }
//             }
//         }
//     }
//     ss:
//     return out;
//     #include <iostream>
// using namespace std;
// bool isPossible(int a, int b, int c, int d) {
//     if (a > c || b > d) {
//         return false;
//     }
//     if (a == c && b == d) {
//         return true;
//     }
//     return isPossible(a + b, b, c, d) || isPossible(a, a + b, c, d);
// }

// string canConvert(int a, int b, int c, int d) {
//     if (isPossible(a, b, c, d)) {
//         return "YES";
//     }
//     return "NO";
// }

int main() {
    // int a, b, c, d;
    // cin >> a >> b >> c >> d;
    // cout << canConvert(a, b, c, d) << endl; // Output: YES
    // string a="abcd";
    // cout<<a.length();
    //return 0;
    int s=sentence.length();
    int l=0;
    string a;
    for(int i=0;i<s;i++){
        int m= sentence[i].length();
        if(m%2==0){
            if(m>l){
                a=sentence[i];
                l=m;
            }
        }
    }
    

}
// int flip=0;
//     int i=0;
//     while(i<size){
//         if(target[i]==0){
//             i++;
//         }
//         else if(target[i]==1){
//             int j=i+1;
//             while(target[j]!=0 && j<size){
//                 j++;
//             }
//             if(j<size){
//                 flip++;
//             }
//             flip++;
//             i=j;
//         }
//     }
// }