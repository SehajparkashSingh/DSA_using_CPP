#include <iostream>
using namespace std;

struct cl_list{
    int data;
    cl_list *next;
    //cl_list *previous;
};
int length(cl_list *head){
    cl_list *current=head;
    int count=0;
    if(current!=NULL){
        count++;
        current=current->next;
    }
    else{
        return count;
    }
    while(current!=head){
        count++;
        current=current->next;
    }
    return count;
}
void print(cl_list *head){
    cl_list *current=head;
    int k=1;
    if(current!=NULL){
        cout<<"Data item "<<k<<" :"<<current->data<<endl;
        current=current->next;
        k++;
        while(current!=head){
            cout<<"Data item "<<k<<" :"<<current->data<<endl;
            current=current->next;
            k++;
        }
    }
    else{
        cout<<"Empty list"<<endl;
    }
    cout<<endl;
    return;
}
void insert(int d, int pos, cl_list **dhead){
    if(pos<=0||pos>(length(*dhead)+1)){
        cout<<"Wrong position input"<<endl;
        return;
    }
    cl_list *ne=(cl_list *)malloc(sizeof(cl_list));
    ne->data=d;
    ne->next=NULL;
    int l=length(*dhead);
    if(pos==1){
        if(l==0){
            ne->next=ne;
            *dhead=ne;
        }
        else {
            ne->next=*dhead;
            cl_list *current=(*dhead)->next;
            while(current->next!=*dhead){
                current=current->next;
            }
            current->next=ne;
            *dhead=ne;
        }
    }
    else{
        cl_list *current=*dhead;
        cl_list *one_before;
        int k=1;
        while(k<pos&&current->next!=*dhead)
        {
            k++;
            one_before=current;
            current=current->next;
        }
        if((current->next!=*dhead)||pos==l){           //inserting inbetween
            ne->next=current;
            one_before->next=ne;
        }
        else{                                //inserting at the end
            ne->next=current->next;
            current->next=ne;
        }
    }
}
void del_element_at_pos(int pos,cl_list **dhead){
    if(pos<=0||pos>length(*dhead)){
        cout<<"Wrong position input"<<endl;
        return;
    }
    cl_list *current=*dhead;
    if(pos==1){
        while(current->next!=*dhead){
            current=current->next;
        }
        current->next=(*dhead)->next;        //updating the last node
        cl_list *temp=*dhead;
        *dhead=(*dhead)->next;               
        free(temp);                          //deleting the first node
    }
    else{
        cl_list *one_before; 
        int k=1;
        while (k<pos&&current->next!=*dhead)
        {
            k++;
            one_before=current;
            current=current->next;
        }
            one_before->next=current->next;
            free(current);
    }
}
void del_link_list(cl_list **dhead){
    if(*dhead==NULL){
        cout<<"List already empty"<<endl<<endl;
    }
    else{
        cl_list *current=*dhead;
        cl_list *temp;
        current=current->next;
        free(*dhead);
        while(current!=*dhead){
            temp=current;
            current=current->next;
            free(temp);
        }
        *dhead=NULL;
    }
    return;
}
void search(int d,cl_list *head){                     //checks for just one time,can be improved
    int k=1;
    if(head->data==d){
        cout<<"Element "<<d<<" found at "<<k<<"st position"<<endl;
        return;
    }
    else{
        cl_list *current=head->next;    
        while(current!=head){
            k++;
            if(current->data==d){
                cout<<"Element "<<d<<" found at "<<k<<"th position"<<endl;
                return;
            }
            current=current->next;
        }
    }
    cout<<"Element "<<d<<" not present in the list"<<endl;
    return;
}
void del_element_by_val(int d,cl_list **dhead){       //checks for just one time,can be improved
   cl_list *current;
   if((*dhead)->data==d){
        current=*dhead;
        while(current->next!=*dhead){
            current=current->next;
        }
        if(length(*dhead)==1){
            free(*dhead);
            *dhead=NULL;
        }
        else{
            current->next=(*dhead)->next;        //updating the last node
            cl_list *temp=*dhead;
            *dhead=(*dhead)->next;               
            free(temp);   
        }
        return;
    }
    else{
        cl_list *one_before=*dhead;
        current=(*dhead)->next;
        while(current!=*dhead){
            if(current->data==d){
                one_before->next=current->next;
                free(current); 
                break;   
        }
            one_before=current;
            current=current->next;
        }
    }
    if(current==*dhead){
        cout<<"Element "<<d<<" not present in the list"<<endl;
    }
    return;
}
int main(){
    cl_list *head=NULL;
    insert(20,1,&head);
    print(head);
    insert(30,1,&head);
    print(head);
    insert(40,3,&head);
    print(head);
    insert(50,2,&head);
    print(head);
    insert(80,3,&head);
    print(head);
    insert(90,6,&head);
    print(head);
    search(50,head);
    print(head);
    del_element_at_pos(1,&head);
    print(head);
    del_element_at_pos(2,&head);
    print(head);
    del_element_by_val(80,&head);
    print(head);
    del_element_by_val(50,&head);
    print(head);
    del_element_by_val(40,&head);
    print(head);
    del_element_by_val(20,&head);
    print(head);
    del_element_by_val(90,&head);
    print(head);
    del_link_list(&head);
    print(head);
    return 0;
}