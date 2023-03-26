#include <iostream>
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
void pop(stack *s){
    if(s){
        if(!empty(s)){
            int d=*(s->arr+s->top--);
            //free(s->arr+s->top);       //or- free(s->arr[s->top])
            //s->capacity--;
            //s->arr=(int *)realloc(s->arr,s->capacity*sizeof(int));
            //cout<<s->capacity*sizeof(int)<<endl;           //size of a stack array
            //return (s->arr[s->top--]);
            cout<<"The element popped is :"<<d<<endl;;
        }
        else{
            cout<<"Stack is already empty"<<endl;
        }
        cout<<endl;
    }
    else
        cout<<"The stack does not exist"<<endl<<endl;
}
void print_top_2_bottom(stack *s){        //recursive function
    if(s){
        if(!(empty(s))){
            static int size=s->capacity;
            static int i=1;
            static int t=s->top;
            cout<<s->arr[t]<<" ";
            t--;
            if(t>=0){
                print_top_2_bottom(s);
            }
            else
                cout<<endl<<endl;               //when the function is called for the last time
            return;
        }
    }
    else
        cout<<"The stack does not exist"<<endl<<endl;   
}
int top_element(stack *s){
    if(!empty(s))
        return s->arr[s->top];
    else
        return -1;
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
//used in reverse function
int pop1(stack *s){
    if(s){
        if(!empty(s)){
            int d=s->arr[s->top];
            //free(s->arr+s->top);       //or- free(s->arr[s->top])
            s->top--;
            //s->capacity--;
            return d;
        }
        else{
            return -1;
        }
    }
    else
        return -1;
}
void recursive_reverse(stack *s){
    static int *temp=(int *)malloc(s->capacity*sizeof(int));
    static int size=s->capacity;
    static int i=0;
    int t=pop1(s);
    //cout<<"T:"<<t<<endl;
    if(t!=-1){
        temp[i]=t;
        i++;
        recursive_reverse(s);
    }
    else if(t==-1)
        return;

    if(i==size){       // run during the last second call to the function;
        for(int j=0;j<i;j++)
            push(s,temp[j]);     //storing in reverse order
        i=0;
    }
    return;
}

//to obtain O(1) time complexity for getting minimum element in the stack
//-------->
struct stack_maintaining_min{      //both the below stacks will be of same length
    stack *main;      //main stack to store the elements
    stack *min;       //stack which stores the current minimum element at the top
};
stack_maintaining_min *create_stack_min(int size=1){
    stack_maintaining_min *s=(stack_maintaining_min*)malloc(sizeof(stack_maintaining_min));
    s->main=create_stack(size);
    s->min=create_stack(size);
    return s;
}
bool empty(stack_maintaining_min *s){
    if(empty(s->main))
        return true;
    else 
        return false;
}
void push(stack_maintaining_min *s,int d){
    if(s){
        push(s->main,d);

        int top=top_element(s->min);
        if(top!=-1){                              
            if(top<=d)               //Current element is compared with the current minimum element in 'min' stack
                push(s->min,top);
            else
                push(s->min,d);
        }
        else{
            push(s->min,d);
        }
    }
    else    
        cout<<"The stack does not exist"<<endl<<endl;
}
void pop(stack_maintaining_min *s){
    if(s){
        if(!empty(s)){
            cout<<"Element of the main stack :";
            pop(s->main);
            cout<<"Element of the min stack :";
            pop(s->min);
        }
        else
            cout<<"The stack is already empty"<<endl;
        cout<<endl;
    }
    else
        cout<<"The stack does not exist"<<endl<<endl;
}
void get_minimum(stack_maintaining_min *s){
    if(s){
        int min=top_element(s->min);
        if(min!=-1)
            cout<<"The minimum element in the stack is :"<<min<<endl<<endl;
        else
            cout<<"The stack is empty"<<endl<<endl;
    }
    else
        cout<<"The stack does not exist"<<endl<<endl;
}
void del_stack(stack_maintaining_min **s){
    if(*s){
        del_stack(&((*s)->main));
        del_stack(&((*s)->min));
    }
    free(*s);
    *s=NULL;
}
// <--------
int main(){
    stack *s=create_stack();
    push(s,5);
    pop(s);

    push(s,109);
    push(s,5);
    push(s,9);
    push(s,11);
    print_top_2_bottom(s);
    recursive_reverse(s);
    //print_top_2_bottom(s);
    pop(s);
    pop(s);
    pop(s);
    //push(s,50);
    //push(s,10);
    pop(s);
    //del_stack(&s);
    pop(s);

    stack_maintaining_min *S=create_stack_min();
    push(S,5);
    push(S,9);
    push(S,1);
    get_minimum(S);
    pop(S);
    get_minimum(S);
    del_stack(&S);
    pop(S);
    return 0;
}