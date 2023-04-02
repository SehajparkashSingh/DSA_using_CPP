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

int pop(stack *s){
    if(s){
        if(!empty(s)){
            int d=s->arr[s->top];
            s->top--;
            return d;
        }
        else{
            cout<<"Stack is empty"<<endl<<endl;
            return INT_MIN;
        }
    }
    else{
        cout<<"Stack doesn't exist"<<endl;
        return INT_MIN;
    }
}
void print_stack(stack *s){    //recursive function, prints top 2 bottom
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
void del_stack(stack **s){
    if(*s){
        if((*s)->arr){
            free((*s)->arr);
        }   
        free(*s);
        *s=NULL;
    }
}
struct queue{
    stack *s1;         //for enqueue operation
    stack *s2;         //for dequeue operation
};
queue *create_queue(int size=8){
    queue *q=(queue *)malloc(sizeof(queue));
    q->s1=create_stack(size);
    q->s2=create_stack(size);
    return q;
}
bool empty(queue *q){
    return(empty(q->s1) && empty(q->s2));
}
void enqueue(queue *q,int d){
    if(empty(q)){         //if(empty(q->s1) && empty(q->s2))
        push(q->s1,d);
    }
    else{
        if(!empty(q->s1)){             //last operation:enqueue
            push(q->s1,d);
        }
        
        else{                         //last operation:dequeue
            while(!empty(q->s2))
                push(q->s1,pop(q->s2));
            push(q->s1,d);
        }
    }
    return;
}
int dequeue(queue *q){
    if(empty(q)){         //if(empty(q->s1) && empty(q->s2))
        cout<<"The queue is empty"<<endl<<endl;
        return INT_MIN;
    }
    else{
        if(!empty(q->s2)){             //last operation:dequeue
            return pop(q->s2);
        }
        
        else{                         //last operation:enqueue
            while(!empty(q->s1))
                push(q->s2,pop(q->s1));
            return pop(q->s2);
        }
    }
}
void print_queue(queue *q){
    if(empty(q)){         //if(empty(q->s1) && empty(q->s2))
        cout<<endl<<endl;
        return;
    }
    else{
        if(!empty(q->s1)){             //last operation:enqueue
            int t= pop(q->s1);
            print_queue(q);
            cout<<t<<" ";
            push(q->s1,t);
        }
        else{                         //last operation:dequeue
            int t=pop(q->s2);
            cout<<t<<" ";
            print_queue(q);
            push(q->s2,t);
        }
    }
}
void del_queue(queue **q){
    if(*q){
        del_stack(&((*q)->s1));
        del_stack(&((*q)->s2));
        free(*q);
        *q=NULL;
    }
}
int main(){
    queue *q=create_queue(5);
    enqueue(q,1);
    enqueue(q,2);
    enqueue(q,3);
    print_queue(q);
    enqueue(q,4);
    cout<<endl<<dequeue(q)<<" "<<endl<<endl;
    enqueue(q,5);
    enqueue(q,6);
    print_queue(q);
    return 0;
}