#include <iostream>
using namespace std;

struct dl_list{
     int data;
     struct dl_list *next;  
     struct dl_list *previous;  
};

void print_forward(dl_list *head){
    dl_list *current=head;
    int i=1;
    if(head==NULL){
        cout<<"Empty list"<<endl;
        return;
    }
    while(current!=NULL){
        cout<<"Data item "<<i<<" :"<<current->data<<endl;
        i++;
        current=current->next;
    }
}
void print_backward(dl_list *tail,int length){
    dl_list *current=tail;
    int i=length;
    while(current!=NULL){
        cout<<"Data item "<<i<<" :"<<current->data<<endl;
        i--;
        current=current->previous;
    }
}
int length(dl_list *head){
    dl_list *current=head;
    int count=0;
    while(current!=NULL){
        count++;
        current=current->next;    
    }
    return count;
}
void insert(int d,int pos,dl_list **dhead){
    if(pos<=0||pos>(length(*dhead)+1)){
        cout<<"Wrong position input"<<endl;
        return;
    }
    dl_list *ne;
    ne=(dl_list*)malloc(sizeof(struct dl_list));
    ne->data=d;
    ne->next=NULL;
    ne->previous=NULL;
    if (pos==1)                     //Inserting in the beginning 
    {
        if(*dhead!=NULL){           //If the list is not empty
            (*dhead)->previous=ne;
        }
        ne->next=*dhead;            
        *dhead=ne;
    }
    else {
        dl_list *current=*dhead;
        dl_list *one_before;
        int k=1;
        while (k<pos&&current!=NULL)
        {
            k++;
            one_before=current;
            current=current->next;
        }
        if(current!=NULL){                    //inserting inbetween
            dl_list *temp=current->previous;
            current->previous=ne;
            ne->next=current;
            ne->previous=temp;
            ne->previous->next=ne;
        }
        else{                                  //inserting at the end
            one_before->next=ne;
            ne->previous=one_before;
        }
    }
}
void del_element_at_pos(int pos,dl_list **dhead){
    if(pos<=0||pos>length(*dhead)){
        cout<<"Wrong position input"<<endl;
        return;
    }
    
    dl_list *current=*dhead;
    if(pos==1){
        (*dhead)->next->previous=NULL;
        *dhead=(*dhead)->next;
        free(current);
    }
    else{ 
        int k=1;
        while (k<pos&&current!=NULL)
        {
            k++;
            current=current->next;
        }
        if(current==NULL){
            cout<<"Position does not exist"<<endl;
        }
        else{
            current->previous->next=current->next;
            current->next->previous=current->previous;
            free(current);
        }
    }
}
void del_link_list(dl_list **dhead){
    dl_list *current=*dhead;
    while(current!=NULL){
        dl_list *temp=current;
        current=current->next;
        free(temp);
    }
    *dhead=NULL;
}
void search(int d,dl_list *head){
    dl_list *current=head;
    int k=1;
    while(current!=NULL){
        if(current->data==d){
            cout<<"Element "<<d<<" found at "<<k<<"th position"<<endl;
            return;
        }
        k++;
        current=current->next;
    }
    cout<<"Element "<<d<<" not present in the list"<<endl;
    return;
}
int main(){
    dl_list *head=NULL; 
    insert(23,1,&head);
    insert(33,1,&head);
    print_forward(head);
    print_backward(head->next,length(head));
    insert(76,2,&head);
    insert(19,5,&head);
    print_forward(head);
    del_element_at_pos(3,&head);
    print_forward(head);
    search(76,head);
    del_link_list(&head);
    print_forward(head);
    return 0;
}