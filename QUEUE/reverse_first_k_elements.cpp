#include <iostream>
using namespace std;

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
void print_queue(queue *q){
    int temp=q->front;
    int count=0;
    while(count!=q->present_sz){
        cout<<q->arr[temp]<<" ";
        if(temp==q->capacity-1)
            temp=0;
        else    
            temp++;
        count++;
    }
    cout<<endl<<endl;
}
//STACK
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
void del_stack(stack **s){
    if(*s){
        if((*s)->arr){
            free((*s)->arr);
        }   
        free(*s);
        *s=NULL;
    }
}
void reverse_queue(queue *q,int k){      //recursive function
    if(k){
       int t=dequeue(q);
       reverse_queue(q,--k);
       enqueue(q,t);   
    }
    else 
        return;
}
void reverse_k_elements(queue *q,int k){    //uses only QUEUE operations 
    if(k>q->present_sz)          //Eg. 1 2 3 4 5 6
        return;
    reverse_queue(q,k);          //5 6 4 3 2 1
    for(int i=0;i<q->present_sz-k;i++){
        enqueue(q,dequeue(q));    //3 2 1 4 5 6
    }
}
void reverse_k_elements1(queue *q,int k){    //uses QUEUE and STACK operations 
    if(k>q->present_sz)          //Eg. 1 2 3 4 5 6
        return;
    stack *s=create_stack(q->present_sz/2);
    for(int i=0;i<k;i++){
        push(s,dequeue(q));       // 1 2 3 4
    }
    for(int i=0;i<k;i++){
        enqueue(q,pop(s));        //5 6 4 3 2 1
    }
    for(int i=0;i<q->present_sz-k;i++){
        enqueue(q,dequeue(q));    //3 2 1 4 5 6
    }
}
int main(){
    queue *q=create_queue(5);
    enqueue(q,1);
    enqueue(q,2);
    enqueue(q,3);
    enqueue(q,4);
    enqueue(q,5);
    enqueue(q,6);
    print_queue(q);
    reverse_k_elements(q,4);
    print_queue(q);
    reverse_k_elements1(q,4);
    print_queue(q);
}