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
//Balancing paranthesis '{}','()','[]'
int match(char m,char n){
    if(m=='{' && n=='}')
        return 1;
    else if(m=='(' && n==')')
        return 1;
    else if(m=='[' && n==']')
        return 1;
    else
        return 0;
}
void check_paranthesis(char *exp){
    stack *cp=create_stack(5);
    for(int i=0;i<strlen(exp);i++){
        if(exp[i]=='{' || exp[i]=='(' || exp[i]=='['){
            push(cp,exp[i]);
        }
        else if(exp[i]=='}' || exp[i]==')' || exp[i]==']'){
            if(empty(cp)){
                cout<<"Imbalanced:Right paranthesis are more than left paranthesis"<<endl<<endl;
                del_stack(&cp);
                return;
            }
            else{
                if(!match(pop(cp),exp[i])){
                    cout<<"Imbalanced:Symbols mismatch"<<endl<<endl;
                    del_stack(&cp);
                    return;
                }
            }
        }
    }
    if(!empty(cp)){
        cout<<"Imbalanced:Left paranthesis are more than right paranthesis"<<endl<<endl;
        del_stack(&cp);
        return;
    }
    else{
        cout<<"Balanced expression: "<<exp<<endl<<endl;
        del_stack(&cp);
        return;
    }        
}

int main(){
    char a[]="a*[{(a+b)/(c-d)}/s]";
    check_paranthesis(a);
    return 0;
}