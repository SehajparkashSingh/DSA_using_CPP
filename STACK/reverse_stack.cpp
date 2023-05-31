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
//QUEUE
struct queue{
    int *arr;
    int capacity;
    int present_sz;
    int front;
    int rear;
};
queue *create_queue(int size=10){
    queue *current=(queue*)malloc(sizeof(queue));
    if(current){
        current->capacity=size;
        current->front=-1;
        current->rear=-1;
        current->present_sz=0;
        current->arr=(int *)malloc(current->capacity*sizeof(int));
        if(current->arr){
            //cout<<"Memory allocated to queue"<<endl<<endl;
            return current;
        }
        else{
            cout<<"Couldn't create a new queue"<<endl<<endl;
            return NULL;
        }
    }
    else{
        cout<<"Couldn't create a new queue"<<endl<<endl;
        return NULL;
    }
}
bool full(queue *q){
    return(q->present_sz==q->capacity);
}
bool empty(queue *q){
    return(q->present_sz==0);
    //return(q->front==q->rear==-1);
}
int size(queue *q){
    return q->present_sz;
}
int reallocate(queue *q){
    int prev_cap=q->capacity;
    q->capacity*=2;
    q->arr=(int *)realloc(q->arr,q->capacity*sizeof(int));
    if(!q->arr)
        return -1;
    if(q->front>q->rear){
        for(int i=0;i<q->front;i++){
            q->arr[prev_cap+i]=q->arr[i];
        }
    }
    return 1;
}
void enqueue(queue *q,int d){
    if(full(q))
        if(reallocate(q)==-1){
            cout<<"Queue already full,cannot assign more memory"<<endl<<endl;
            return;
        }
    //if(!full(q))
    {
        if(empty(q)){
            q->front++;
            q->rear++;        //q->arr[++q->rear]==d;
            q->arr[q->rear]=d;         
        }
        else if(q->rear!=q->capacity-1){
            q->rear++;       //q->arr[++q->rear]=d;
            q->arr[q->rear]=d;
        }
        else{            //rear==capacity-1
            q->rear=0;
            q->arr[q->rear]=d;
        }
        q->present_sz++;
    }
    return;
}
int dequeue(queue *q){
    int d;
    if(!empty(q)){
        if(q->present_sz>1){          //q->front!=q->rear
            if(q->front!=q->capacity-1){
                d=q->arr[q->front++];
            }
            else{
                d=q->arr[q->front];
                q->front=0;
            }
        }
        else{                  //q->front==q->rear
            d=q->arr[q->front];
            q->front=q->rear=-1;
        }
        q->present_sz--;
        return d;
    }
    else
        cout<<"Queue already empty"<<endl<<endl;
    return INT_MIN;
}
void del_queue(queue **q){
    if(*q){
        if((*q)->arr){
            free((*q)->arr);
            free(*q);
        }
        *q=NULL;
    }
}
void print_stack(stack *s){    //recursive function, prints top2bottom
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
void reverse_with_queue(stack *s){
    queue *q=create_queue(s->capacity);
    while(!empty(s)){
        enqueue(q,pop(s));
    }
    while(!empty(q)){
        push(s,dequeue(q));
    }
    del_queue(&q);
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
    reverse_with_queue(s);
    print_stack(s);
    string q="bbxbb";
    int ind;
    int l=q.length();
    int i;
       for(i=0;i<l;i++){
            if(q[i]=='a'){
                continue;
            }
            else if(q[i]!='a'){
                ind=i;
                break;
            }
       }
       if(i==l){
        q[i-1]='b';
       }
       else if(l%2==0){
        q[ind]='a';
       }
       else if(ind+1==(l/2)+1){
        q[l-1]='b';
       }
       else {
        q[ind]='a';
       }
       cout<<q<<endl;

       q="gagadeab";
       l=q.length();
       int j;
       int la=0;
       for(j=1;j<l;j++){
            if(q[j]>q[j-1]){
                la=j;
            }
       }
       if(la>0){
        char t=q[la];
        q[la]=q[la-1];
        q[la-1]=t;
       }
       cout<<q<<endl;
}