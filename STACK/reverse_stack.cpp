#include <iostream>
#include <cstring>
using namespace std;

struct stack{
    int top;
    int *arr;
    int capacity;    
};
stack *create_stack(int size= 1){
    stack *s=(stack *)(malloc(sizeof(stack)));
    if(!s){
        return NULL;
    }
    s->capacity=size;
    s->top=-1;
    s->arr=(int *)(malloc(s->capacity*sizeof(int)));
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
    if(s){
        if(full(s)){
            s->capacity++;
            s->arr=(int *)realloc(s->arr,s->capacity*sizeof(int));
        }
        s->top++;
        //*(s->arr+s->top)==d; 
        s->arr[s->top]=d;
        return;
    }
    else
        cout<<"The stack does not exist"<<endl<<endl;
}
int pop(stack *s){
    if(s){
        if(!empty(s)){
            int d=*(s->arr+s->top--);
            //cout<<"The element popped is :"<<d<<endl;
            return d;
        }
        else{
            cout<<"Stack is already empty"<<endl;
            return INT_MIN;
        }
        cout<<endl;
    }
    else{
        cout<<"The stack does not exist"<<endl<<endl;
        return INT_MIN;
    }
}
int top_element(stack *s){
    if(s){
        if(!empty(s)){
            //cout<<s->arr[s->top]<<endl;
            return s->arr[s->top]; 
        }
    }
    else{
        cout<<"Stack doesn't exist"<<endl<<endl;
        return INT_MIN;
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
void print_stack(stack *s){    //recursive function
    if(!empty(s)){
        int d=pop(s);
        cout<<d<<" ";
        print_stack(s);
        push(s,d);
    }
    else{
        cout<<endl<<endl;
        return;
    }
}
void push_at_bottom(stack *s,int t){  //recursive function, puts 't' at bottom of stack
    if(!empty(s)){
        int k=pop(s);
        push_at_bottom(s,t);
        push(s,k);
    }
    else{
        push(s,t);
    }

}
void reverse_stack(stack **ds){  //recursive function
    stack *s=*ds;
    if(!empty(s)){
        int t=pop(s);
        reverse_stack(&s);
        push_at_bottom(s,t);
    }
    else
        return;
}
int main(){
    stack *s=create_stack(8);
    push(s,1);
    push(s,2);
    push(s,3);
    push(s,4);
    push(s,5);
    print_stack(s);
    reverse_stack(&s);
    print_stack(s);
}