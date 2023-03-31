#include <iostream>
#include <cstring>
using namespace std;

struct stack{
    int top;
    char *arr;
    int capacity;    
};
stack *create_stack(int size= 1){
    stack *s=(stack *)(malloc(sizeof(stack)));
    if(!s){
        return NULL;
    }
    s->capacity=size;
    s->top=-1;
    s->arr=(char *)(malloc(s->capacity*sizeof(char)));
    if(!s->arr){
        return NULL;
    }
    return s;
}
bool empty(stack *s){
    if(s->top==-1)
        return true;
    else
        return false;
}
bool full(stack *s){
    if(s->top==s->capacity-1)
        return true;
    else
        return false;
}
void push(stack *s,char d){
    if(s){
        if(full(s)){
            s->capacity++;
            s->arr=(char *)realloc(s->arr,s->capacity*sizeof(char));
        }
        s->top++;
        //*(s->arr+s->top)==d; 
        s->arr[s->top]=d;
        return;
    }
    else
        cout<<"The stack does not exist"<<endl<<endl;
}
char pop(stack *s){
    if(s){
        if(!empty(s)){
            char d=*(s->arr+s->top--);
            //cout<<"The element popped is :"<<d<<endl;
            return d;
        }
        else{
            cout<<"Stack is already empty"<<endl;
            return '\0';
        }
        cout<<endl;
    }
    else{
        cout<<"The stack does not exist"<<endl<<endl;
        return '\0';
    }
}
char top_element(stack *s){
    if(s){
        if(!empty(s)){
            //cout<<s->arr[s->top]<<endl;
            return s->arr[s->top]; 
        }
    }
    else{
        cout<<"Stack doesn't exist"<<endl<<endl;
        return '\0';
    }
}
void del_stack(stack **s){
    if(*s){
        if((*s)->arr){
            free((*s)->arr);
        }   
        free(*s);
        *s=NULL;
    }
}
//string type----> "_______x_________"
void check_palindrome(char *exp){
    stack *pl=create_stack(8);
    int i=0;
    while(exp[i] && exp[i]!='x'){
        push(pl,exp[i]);
        i++;
    }        //exp[i]=='x'
    i++;
    while(!empty(pl) && exp[i]){
        if(pop(pl)!=exp[i]){
            cout<<exp<<" is not a palindrome"<<endl<<endl;
            return;
        }
        i++;
    }
    if(!empty(pl)||exp[i]){
        cout<<exp<<" is not a palindrome"<<endl<<endl;
        return;
    }
    else    
        cout<<exp<<" is a palindrome"<<endl<<endl;
    return;  
}
int main(){
    char a[]="assaxassa";
    check_palindrome(a);
    return 0;
}