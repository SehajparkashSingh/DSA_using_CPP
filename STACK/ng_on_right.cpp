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
int *next_greater_on_right(int a[],int size){
    int *rg=(int *)malloc(size*sizeof(int));
    stack *s=create_stack(size);
    for(int i=size-1;i>=0;i--){
        /*if(empty(s)){
            rg[i]=a[i];
            push(s,a[i]);
        }
        else*/{
            while(a[i]>=top_element(s) && (!empty(s))){
                pop(s);
            }
            if(!empty(s)){
                rg[i]=top_element(s);
            }
            else{         //empty(s)
                rg[i]=a[i];
            }
            push(s,a[i]);
        }
    }
    del_stack(&s);
    return rg;
}
int main(){
    int a[]={13,3,2,5,10,7,9,12};
    int *greater_on_right=next_greater_on_right(a,sizeof(a)/sizeof(int));
    cout<<"Element:Next greater element"<<endl;
    int i=0;
    while(i<sizeof(a)/sizeof(int)){
        cout<<"      "<<a[i]<<":"<<*greater_on_right<<endl;
        i++;
        greater_on_right++;
    }
    return 0;
}