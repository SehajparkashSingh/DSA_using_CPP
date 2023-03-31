#include <iostream>
using namespace std;

struct l_list{
    int data;
    struct l_list *previous;    
};
int stack_len(struct l_list *top){
    int count=0;
    while(top !=NULL){
        count++;
        top=top->previous;
    }
    return count;
}
void push(int d,l_list **dtop){
    struct l_list *ne;
    ne=(l_list*)malloc(sizeof(l_list));
    ne->data=d;
    ne->previous=NULL;
    //cout<<ne->data<<"\n";
    ne->previous=*dtop;
    *dtop=ne;
}
void pop(l_list **dtop){
    if(*dtop==NULL){
        cout<<"The stack is empty"<<endl;
    }
    else{
        cout<<(*dtop)->data<<endl;
        l_list *temp=*dtop;
        *dtop=(*dtop)->previous;
        free(temp);
    }
    return;
}
void del_stack(l_list **dtop){
    l_list *current=*dtop;
    while(current!=NULL){
        l_list *temp=current;
        current=current->previous;
        free(temp);
    }
    *dtop=NULL;
}

int main()
{
    struct l_list *top,**dtop;
    //head=(l_list*)malloc(sizeof(struct l_list));
    top=NULL;
    dtop=&top;
    push(45,dtop);
    push(50,dtop);
    push(55,dtop);
    cout<<"No.of elements in the stack :"<<stack_len(top)<<endl;
    pop(dtop);
    pop(dtop);
    cout<<"No.of elements in the stack :"<<stack_len(top)<<endl;
    del_stack(dtop);
    pop(dtop);
    //cout<<"No.of elements in the stack :"<<stack_len(top)<<endl;
    return 0;
}