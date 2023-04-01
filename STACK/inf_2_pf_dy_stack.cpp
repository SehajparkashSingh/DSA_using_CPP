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
//infinix to postfix conversion
int priority(char a){
    if(a=='(')
        return 0;
    else if(a=='+' || a=='-')
        return 1;
    else if(a=='*' || a=='/')
        return 2;
}
void infinix_2_postfix(char *exp){
    stack *ip=create_stack(8);
    cout<<"Postfix expression: ";
    for(int i=0;i<strlen(exp);i++){
        if(exp[i]=='(')
            push(ip,exp[i]);
        else if(exp[i]=='*' || exp[i]=='+' || exp[i]=='-' || exp[i]=='/'){
            while(priority(top_element(ip))>=priority(exp[i]) && (!empty(ip)))
                cout<<pop(ip);
            push(ip,exp[i]);
        }
        else if(exp[i]==')'){
            char m;
            while((m=pop(ip))!='(')
                cout<<m;
        }
        else{
            cout<<exp[i];
        }
    }
    while(!empty(ip))
        cout<<pop(ip);
    cout<<endl<<endl;
}
int main(){
    char b[]="(a+b)*(c+d)/2";
    infinix_2_postfix(b);
    return 0;
}