#include <iostream>
using namespace std;

struct l_list{
     int data;
     struct l_list *next;    
};
struct queue{
    l_list *front;
    l_list *rear;
};
queue *create_queue(){
    queue *q=(queue *)malloc(sizeof(queue));
    if(q){
        q->front=NULL;
        q->rear=NULL;
        return q;
    }
    else{
        cout<<"Couldn't create the queue"<<endl<<endl;
        return NULL;
    }   
}
bool empty(queue *q){
    return(q->front==NULL);
}
void enqueue(queue *q,int d){
    if(q){
        if(empty(q)){
            q->front=(l_list *)malloc(sizeof(l_list));
            //q->rear=(l_list *)malloc(sizeof(l_list));
            q->rear=q->front;

            q->front->data=d;
            q->front->next=NULL;
            //q->rear->data=d;
            //q->rear->next=NULL;
        }
        else{
            l_list *temp=q->rear;
            q->rear=(l_list *)malloc(sizeof(l_list));
            q->rear->data=d;
            q->rear->next=NULL;
            temp->next=q->rear;
        }
    }
    else{
        cout<<"Queue doesn't exist"<<endl<<endl;
    }
}
void dequeue(queue *q){
    if(q){
        if(!empty(q)){
            cout<<"The element at front is :"<<q->front->data<<endl<<endl;
            l_list *temp=q->front;
            q->front=q->front->next;
            if(temp==q->rear){    //only 1 element in the queue
                q->rear=NULL;     //q->rear=q->rear->next;
            }
            free(temp);
        }
        else{
            cout<<"Queue already empty"<<endl<<endl;
        }
    }
    else{
        cout<<"Queue doesn't exist"<<endl<<endl;
    }
}
void delete_queue(queue **q){
    if(*q){
        if((*q)->front){
            while((*q)->front){
                l_list *temp=(*q)->front;
                (*q)->front=(*q)->front->next;
                free(temp);
            }
        }
        free(*q);
        *q=NULL;
    }
}
void size(queue *q){
    if(q){
        l_list *temp=q->front;
        int count=0;
        while(temp!=NULL){
            count++;
            temp=temp->next;
        }
        cout<<"Size of the queue is :"<<count<<endl<<endl;
    }
    else{
        cout<<"Queue doesn't exist"<<endl<<endl;
    }
}
int rear_element(queue *q){
    if(q){
        if(q->rear!=NULL)    //if(!empty(q))
            return q->rear->data;
        else 
            return INT_MIN;
    }
    else{
        cout<<"Queue doesn't exist"<<endl<<endl;
        return INT_MIN;
    }
}
int front_element(queue *q){
    if(q){
        if(q->front!=NULL)    //if(!empty(q))
            return q->front->data;
        else 
            return INT_MIN;
    }
    else{
        cout<<"Queue doesn't exist"<<endl<<endl;
        return INT_MIN;
    }
}
void print_queue(queue *q){
    if(q){
        l_list *temp=q->front;
        while(temp!=NULL){
            cout<<temp->data<<"  ";
            temp=temp->next;
        }
        cout<<endl<<endl;
    }
    else{
        cout<<"Queue doesn't exist"<<endl<<endl;
    }
}
int main()
{
    queue *q=create_queue();
    return 0;
}