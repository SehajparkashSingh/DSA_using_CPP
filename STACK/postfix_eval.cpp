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
//Evaluate postfix for single digit numbers
void postfix_eval(char *exp){
    stack *pe=create_stack(8);
    for(int i=0;i<strlen(exp);i++){
        if(isdigit(exp[i]))
            push(pe,exp[i]-'0');
        else{
            int top=pop(pe);
            int top2=pop(pe);
            switch(exp[i]){
                case '*':
                        push(pe,top2*top);
                        break;
                case '/':
                        if(top==0){
                            cout<<"ERROR:0 in denominator"<<endl<<endl;
                            return;
                        }
                        push(pe,top2/top);
                        break;
                case '+':
                        push(pe,top2+top);
                        break;
                case '-':
                        push(pe,top2-top);
                        break;
            }
        }
    }
    cout<<exp<<"="<<pop(pe)<<endl<<endl;
}
int main(){
    char a[]="50/";
    postfix_eval(a);
    return 0;
}