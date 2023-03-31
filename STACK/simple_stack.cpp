#include <iostream>
using namespace std;

struct stack{
    int top;
    int *arr;
    int capacity;    
};
stack *create_stack(int size= 20){
    stack *s=(stack *)(malloc(sizeof(stack)));           //memory allocation for stack
    if(!s){
        return NULL;
    }
    s->capacity=size;
    s->top=-1;                                           //initially, the stack is empty
    s->arr=(int *)(malloc(s->capacity*sizeof(int)));     //memory allocation for stack capacity
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
void push(stack *s,int d){
    if(!full(s)){
        s->top++;
        //*(s->arr+s->top)==d; 
        s->arr[s->top]=d;
    }
    else{
        cout<<"Stack already full"<<endl<<endl;
    }
}
void pop(stack *s){
    if(!empty(s)){
        //return (s->arr[s->top--]);
        cout<<*(s->arr+s->top--)<<endl;
    }
    else{
        cout<<"Stack already empty"<<endl;
        return;
    }
}
void del_stack(stack *s){
    if(s){
        if(s->arr){
            free(s->arr);
        }
        free(s);
    }
}
int main(){
    stack *s=create_stack(10);
    //cout<<s->top<<endl;
    push(s,5);
    //cout<<s->top<<endl;
    push(s,109);
    //cout<<s->top<<endl;
    pop(s);
    pop(s);
    pop(s);
    push(s,5);
    push(s,109);
    pop(s);
    del_stack(s);
    //pop(s);
    return 0;
}