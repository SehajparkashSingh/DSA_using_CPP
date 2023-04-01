#include <iostream>
using namespace std;

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
            cout<<"Memory allocated to queue"<<endl<<endl;
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

struct stack{
    queue *q1;
    queue *q2;
};
stack *create_stack(int size){
    stack *s=(stack *)malloc(sizeof(stack));
    s->q1=create_queue(size);
    s->q2=create_queue(size);
    return s;
}
bool empty(stack *s){
    return(empty(s->q1) && empty(s->q2));
}
void push(stack *s,int d){
    if(empty(s->q1) && empty(s->q2))
        enqueue(s->q1,d);
    else if(!empty(s->q1))
        enqueue(s->q1,d);
    else
        enqueue(s->q2,d);
    return;
}
int pop(stack *s){
    if(!empty(s)){
        if(!empty(s->q1)){
            int size=s->q1->present_sz;
            for(int i=0;i<size-1;i++){
                enqueue(s->q2,dequeue(s->q1));
            }
            return dequeue(s->q1);
        }
        else{
            int size=s->q2->present_sz;
            for(int i=0;i<size-1;i++){
                enqueue(s->q1,dequeue(s->q2));
            }
            return dequeue(s->q2);
        }
    }
    else{
        cout<<"The stack is empty"<<endl<<endl;
        return INT_MIN;
    }
}
int size(stack *s){
    if(!empty(s)){
        if(!empty(s->q1)){
            return s->q1->present_sz;
        }
        else{
            return s->q2->present_sz;
        }
    }
    else{
        return 0;
    }
}
void print_stack(stack *s,int size){   //prints top2bottom
    if(!empty(s)){
        if(size){
            if(!empty(s->q1)){
                int t=dequeue(s->q1);
                enqueue(s->q1,t);
                print_stack(s,--size);
                cout<<t<<" ";
            }
            else{
                int t=dequeue(s->q2);
                enqueue(s->q2,t);
                print_stack(s,--size);
                cout<<t<<" ";
            }
        }
        else
            return;     
    }
    else
        cout<<"The stack is empty";
}
int main(){
    stack *s=create_stack(5);
    push(s,1);
    push(s,2);
    push(s,3);
    push(s,4);
    push(s,5);
    print_stack(s,size(s));
    cout<<endl<<endl;
    cout<<pop(s)<<" "<<pop(s)<<" "<<pop(s)<<endl<<endl;
    print_stack(s,size(s));
    cout<<endl<<endl; 
    cout<<pop(s)<<" "<<pop(s)<<" "<<endl<<endl; 
    print_stack(s,size(s));
    cout<<endl<<endl;  
    cout<<"Size:"<<size(s)<<endl<<endl;
    return 0;
}