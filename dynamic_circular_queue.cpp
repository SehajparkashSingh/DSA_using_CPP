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
void dequeue(queue *q){
    if(!empty(q)){
        if(q->present_sz>1){          //q->front!=q->rear
            if(q->front!=q->capacity-1){
                cout<<"The element at the front is :"<<q->arr[q->front++]<<endl<<endl;
            }
            else{
                cout<<"The element at the front is :"<<q->arr[q->front]<<endl<<endl;
                q->front=0;
            }
        }
        else{                  //q->front==q->rear
            cout<<"The element at the front is :"<<q->arr[q->front]<<endl<<endl;
            q->front=q->rear=-1;
        }
        q->present_sz--;
    }
    else
        cout<<"Queue already empty"<<endl<<endl;
    return;
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
int main(){
    
}