#include <iostream>
using namespace std;

struct l_list{
     int data;
     struct l_list *next;    
};

void print_list(l_list *head){
    l_list *current=head;
    int i=1;
    while(current!=NULL){
        cout<<"Data item "<<i<<" :"<<current->data<<endl;
        current=current->next;
        i++;
    }
    cout<<endl;
}
void print_in_reverse(l_list *head){
    if(head!=NULL){
        print_in_reverse(head->next);
        cout<<head->data<<endl;
    }
    return;
}
int list_len(struct l_list *head){
    struct l_list *current=head;
    int count=0;

    while(current !=NULL){
        count++;
        current=current->next;
    }
    return count;
}
void insert(int d,int pos,struct l_list **dhead){
    if(pos<=0||pos>list_len(*dhead)+1){
        cout<<"Wrong position entered"<<endl;
        return;
    }
    struct l_list *ne;
    ne=(l_list*)malloc(sizeof(struct l_list));
    ne->data=d;
    ne->next=NULL;
    //cout<<ne->data<<"\n";
    if(pos==1){
        ne->next=*dhead;
        *dhead=ne;
    }
    else
    {
        int k=1;
        struct l_list *current=*dhead;
        l_list *one_before;
        while (k<pos&&current!=NULL)
        {
          k++;
          one_before=current;
          current=current->next;
        }
        one_before->next=ne;
        ne->next=current;
    }
    
}
void del_element_at_pos(int pos,l_list **dhead){
    struct l_list *current=*dhead;
    if(pos<1){
        cout<<"Wrong input"<<endl;
    }
    else if(pos==1&&(*dhead)!=NULL){
        *dhead=(*dhead)->next;    //*dhead=current->next;
        free(current);
    }
    else{
        int k=1;
        while (k<pos-1&&current!=NULL)
        {
            current=current->next;
            k++;
        }
        if(current==NULL|| current->next==NULL){
            cout<<"Position does not exist"<<endl;
        }
        else{
            l_list *to_del_element_at_pos=current->next;
            l_list *in_front=to_del_element_at_pos->next;
            current->next=in_front;
            free(to_del_element_at_pos);
        }
    }
}
void del_link_list(l_list **dhead){
    l_list *current=*dhead;
    while(current!=NULL){
        l_list *temp=current;
        current=current->next;
        free(temp);
    }
    *dhead=NULL;
}
l_list *reverse(l_list *head){
    l_list *temp,*temp1;
    l_list *current=head;
    l_list *h=NULL;
    while (current!=NULL)
    {
        temp=h;              //NULL  , a
        h=current;           //head(a),b
        temp1=current->next; //b      ,c
        current->next=temp;  //NULL   ,a
        current=temp1;       //b      ,c
    }
    return h;
}
void n_node_from_end(int n,l_list *head){
    l_list *nth_node_f,*nth_node_b;
    nth_node_f=head;
    nth_node_b=head;
    int k=1;
    while(k<=n && nth_node_f!=NULL){
        nth_node_f=nth_node_f->next;
        k++;
    }
    if(n>=k){
       cout<<"Not enough elements in the list"<<endl<<endl;
    }
    else
    {
        while(nth_node_f!=NULL){
            nth_node_f=nth_node_f->next;
            nth_node_b=nth_node_b->next;
        }
        cout<<n<<"th node :"<<nth_node_b->data<<endl<<endl;
    }
    return;
}
void reverse_in_pairs(l_list **dhead){
    l_list *current=*dhead;
    l_list *one_before;
    int k=1;
    while(current!=NULL && current->next!=NULL){
            l_list *temp=current->next;
            current->next=current->next->next;
            temp->next=current;
            if(k==1){
                *dhead=temp;
                //cout<<(*dhead)->data<<endl;
            }
            else{
                one_before->next=temp;
                //cout<<one_before->next->data<<endl;
            }
            k+=2;
            //cout<<temp->next->data<<endl;
            one_before=current;
            current=current->next;
    }
    return;
}
void reverse_in_grps_of_n(int n,l_list **head){
    if(n==1){
        return;
    }
    l_list *current=*head;
    l_list *current_previous=*head;
    cout<<(*head)->data<<endl;
    int l=1;
    while(current!=NULL && current->next!=NULL){
        l_list *last=current;
        for(int i=2;i<=n;i++){
            last=last->next;
            if(last->next==NULL)
                break;
        }
        //cout<<"l="<<l++<<endl;
        //cout<<last->data<<endl;        //2
        l_list *previous=current;  //a
        l_list *temp=previous->next;  //b
        l_list *temp1; 
        //cout<<temp->data<<endl;           //2
        int k=10;
        while(temp!=last){
            temp1=temp->next;//c  d 
            temp->next=previous;//b-a  c-b
            previous=temp;//b   c
            temp=temp1;//c     d
            //cout<<temp->data<<endl;
            //cout<<"k="<<k<<endl;
        }
        temp1=temp->next;    //f
        temp->next=previous;  //e-d
        //cout<<temp->next->data<<endl;

        current->next=temp1; //a-f
        if(current_previous==*head)
            *head=temp;
        else
            current_previous->next=temp;  //head-e

        current_previous=current;
        current=current->next;
    }
}
void middle(l_list *head){
    if(head==NULL){
        cout<<"List is empty"<<endl;
        return;
    }
    l_list *temp2=head->next;      //points to 2nd element
    l_list *temp=head;           //points to 1st element
    while (temp2!=NULL)
    {   
        if(temp2->next!=NULL){       //to handle even no. of elements
            temp2=temp2->next->next;
            temp=temp->next;
        }
        else{
            break;
        }
    }
    cout<<temp2<<endl;
    cout<<"Middle element :"<<temp->data<<endl<<endl;
    return;
}
void odd_even(l_list *head){
    if(head==NULL){
        cout<<"List is empty"<<endl;
        return;
    }
    l_list *temp2=head->next;      //points to 2nd elements
    while (temp2!=NULL)
    {   
        if(temp2->next!=NULL){       //to handle even no. of elements
            temp2=temp2->next->next;    //jump two nodes at a time
        }
        else{                 //temp2->next=NULL //even no. of elements
            break;
        }
    }
    if(temp2==NULL){
        cout<<"ODD no. of elements in the list"<<endl;
    }
    else{
        cout<<"EVEN no. of elements in the list"<<endl;
    }
    return;   
}
void merge_2_lists(int pos,l_list *h1,l_list *h2){  //list 2 points to the node after position 'pos' in list 1
    if(h1==NULL||h2==NULL){
        cout<<"Either one or both the lists are empty"<<endl;
        return;
    }
    if(pos<0||pos>=list_len(h1)){
        cout<<"Wrong position input"<<endl;
        return;
    }
    l_list *last_node2=h2;
    while(last_node2->next!=NULL){
        last_node2=last_node2->next;
    }
    int k=0;
    while(k<pos){
        h1=h1->next;
        k++;
    }
    last_node2->next=h1;
    //cout<<h1->data<<endl;
    return;
}
void merge_pnt_of_2_lists(l_list *h1,l_list *h2){
    if(h1&&h2){
        int l1=list_len(h1);
        //cout<<l1<<endl;
        int l2=list_len(h2);
        int d=l1-l2;
        if(d>0){
            while((d--)>0)
                h1=h1->next;
        }
        else{
            d=-d;
            while((d--)>0)
                h2=h2->next;
        }
        //cout<<h2<<endl;
        while(h1!=h2){
            h1=h1->next;
            h2=h2->next;
        }
        cout<<h1->data<<" "<<h2->data<<endl;
    }
    else{
        cout<<"Either one or both the lists are empty"<<endl;
    }
    return ;
}
l_list *merge_sorted_lists_1(l_list *h1,l_list *h2){
    l_list *h3=NULL;
    int pos=1;
    while(h1&&h2){
        if(h1->data<=h2->data){
            insert(h1->data,pos,&h3);
            h1=h1->next;
        }
        else{
            insert(h2->data,pos,&h3);
            h2=h2->next;
        }
        pos++;
    }
    l_list *current;
    if(h1!=NULL){
        current=h1;
    }
    else{
        current=h2;
    }
    while(current!=NULL){
        insert(current->data,pos,&h3);
        current=current->next;
        pos++;
    }
    return h3;
}
void merge_sorted_lists_2(l_list *h1,l_list *h2){   //without using additional memory space
     l_list *head_node,*head;
     head_node=(l_list *)malloc(sizeof(l_list));
     head_node->next=NULL;
     head=head_node;
     //head_node->next;
     while(h1&&h2){
        if(h1->data<=h2->data){
            head_node->next=h1;
            head_node=head_node->next;
            h1=h1->next;
        }
        else{
            head_node->next=h2;
            head_node=head_node->next;
            h2=h2->next;
        }
    }
    l_list *current;
    if(h1!=NULL){
        current=h1;
    }
    else{
        current=h2;
    }
    head_node->next=current;
    head=head->next;
    while ((head!=NULL))
    {
        cout<<"DATA ITEM :"<<head->data<<endl;
        head=head->next;
    }
}
void sort_even_odd1(l_list **dhead){
    l_list *current=*dhead;
    l_list *previous=NULL;
    int k=1;
    l_list *update_sub_current;      // to update the nodes to be checked ahead of the nodes already checked
    while(current!=NULL){
        l_list *sub_current;
        if((current->data%2)!=0){
            if(k>1){
                sub_current=update_sub_current;
            }
            else{
                sub_current=current;
            }
            l_list *one_before;
            while((sub_current->data%2)!=0){
                one_before=sub_current;
                sub_current=sub_current->next;
                if(sub_current==NULL)
                    return;
            }
            update_sub_current=sub_current->next;  //updating
            if(previous==NULL)
                *dhead=sub_current;
            else
                previous->next=sub_current;
            one_before->next=sub_current->next;
            sub_current->next=current;
            previous=sub_current;
        }
        else{
            previous=current;
            current=current->next;
        }
    }
}
void sort_even_odd2(l_list **dhead){
    l_list *current=*dhead;
    l_list *new_node,*temp;
    new_node=(l_list *)malloc(sizeof(l_list));
    new_node->next=NULL;
    temp=new_node;
    l_list *previous=NULL;
    while(current!=NULL){
        if((current->data%2)!=0){
            temp->next=current;
            if(current==*dhead)
                *dhead=current->next;
            else
                previous->next=current->next;
            current->next=NULL;
            temp=current;
            if(previous==NULL)
                current=*dhead;
            else
                current=previous->next;
        }
        else{
            previous=current;
            current=current->next;
        }
    }
    previous->next=new_node->next;
    free(new_node);
}
void last_modular_node_from_front(int k,l_list *head){
    if(head==NULL){
        cout<<"List is empty"<<endl;
        return;
    }
    int i=1,count=0;
    l_list *current=head;
    l_list *modular_node;
    //cout<<"Modular node :"<<modular_node->data<<endl;
    while(current->next!=NULL){
        if(count>=1){
            i=0;
        }
        while(i<k&&current->next!=NULL){
            current=current->next;
            i++;
        }
        if(i==k){
            modular_node=current;
            cout<<current->data<<endl;
        }
        count++;
    }
    if(count==0){               //When list length==1
        if(i==k)
            modular_node=head;
        else{
            cout<<"Value of 'k' more than that of length of the list"<<endl;
            return;
        }
    }
    else if(count==1&&i!=k){        
        cout<<"Value of 'k' more than that of length of the list"<<endl;
        return;
    }
    cout<<"Modular node :"<<modular_node->data<<endl;
}
void first_modular_node_from_end(int k,l_list *head){
    if(head==NULL){
        cout<<"List is empty"<<endl;
        return;
    }
    l_list *current=head;
    l_list *modular=head;
    int i=1;
    while(i<k && current->next!=NULL){
        current=current->next;
        i++;
    }
    if(i<k){
        cout<<"Only "<<i<<" nodes in the list"<<endl;
        return;
    }
    while(current->next!=NULL){
        current=current->next;
        modular=modular->next;
    }
    cout<<"First "<<k<<" modular node from end :"<<modular->data<<endl;
}
bool compare(l_list *head,l_list *tail){
    if(head->data==tail->data)
        return true;
    else 
        return false;
}
bool recursive_palindrome(l_list *current,l_list **head){    
    if(current->next!=NULL){
        bool res = recursive_palindrome(current->next,head);
        if(res==false){
            return false;
        }
    }
    if(compare(current,*head)==false){
        *head=(*head)->next;
        return false;
    }
    else{
        *head=(*head)->next;
        return true;
    }
}
bool check_palindrome(l_list *head){
    l_list **dhead=&head;
    return recursive_palindrome(head,dhead);
}
void fractional_node_using_2_pntrs(int k,l_list *head){
    if(k<=0){
        cout<<"Wrong value of K has been input"<<endl<<endl;
        return;
    }
    l_list *kp=head;
    l_list *p;
    int itr=0;
    int i;
    //cout<<p->data<<endl;
    while(1){
        itr++;
        for(i=1,kp;i<k && kp!=NULL;i++,kp=kp->next){}
        if(i==k && kp!=NULL){
            if(itr==1){
                p=head;
                //cout<<p->data<<endl;
            }
            else{
                p=p->next;
                //cout<<p->data<<endl;
            }
        }
        if(kp==NULL || kp->next==NULL){
            //cout<<p->data<<endl;
            break;
        }
        kp=kp->next;
    }
    if(itr==1 && kp==NULL){
        cout<<"K="<<k<<" greater than length of list"<<endl<<endl;
        return;
    }
    cout<<"Fractional node "<<k<<" :"<<p->data<<endl<<endl;
}
void fractional_node_using_modulus(int k,l_list *head){
    if(k<=0){
        cout<<"Wrong value of K has been input"<<endl<<endl;
        return;  
    }
    int i;
    l_list *modular=NULL,*current=head;
    for(i=1,current;current!=NULL;i++,current=current->next){
        if(i%k==0){
            if(modular==NULL)
                modular=head;
            else
                modular=modular->next;
        }
    }
    if(modular==NULL)
        cout<<"K="<<k<<" greater than length of list"<<endl<<endl;
    else      
        cout<<"Modular node "<<k<<" :"<<modular->data<<endl<<endl;
}
void root_n_node(l_list *head){    //'n' is the total no.of nodes
    if(head==NULL){
        cout<<"List is empty"<<endl<<endl;
        return;
    }
    int i=1;      //node index
    int j=1;      //root node index
    l_list *current=head;
    l_list *root=head;
    while(current->next!=NULL){
        current=current->next;
        i++;
        if(i==(j+1)*(j+1)){
            root=root->next;
            j++;
        }
    }
    cout<<"Total no. of elements in the list :"<<i<<endl<<"Root node "<<j<<" :"<<root->data<<endl<<endl;
    return;
}
//recursive functions
void add_2_equal_lists(l_list *h1,l_list *h2,int *carry,l_list **result);
void add_carry_to_remaining_elements(l_list *h,l_list *last,int *carry,l_list **result);

//each node of a list represents a digit(0-9)
l_list * add_two_lists_representing_2_numbers(l_list *h1,l_list *h2){
   // cout<<0<<endl;
    if(h1==NULL && h2==NULL){
        cout<<"Both the lists are empty"<<endl<<"NULL pointer returned"<<endl<<endl;
        //cout<<0<<endl;
        return NULL;
    }
    else if(h1==NULL){
        //cout<<0<<endl;
        return h2;
    }
    else if(h2==NULL){
        cout<<0<<endl;
        return h1;
    }
    else{
        int len1=1,len2=1;
        l_list *current=h1;
        while(current->next!=NULL){         //length of list1 
            current=current->next;
            len1++;
        }

        current=h2;
        while (current->next!=NULL)         //length of list2
        {
            current=current->next;
            len2++;
        }
        l_list *current1,*current2;
        l_list *previous=NULL;
        if(len1-len2>0){                  //if list1 is longer than list2
            int diff=len1-len2;
            current1=h1;
            previous=NULL;
            int i=1;
            while(i<=diff){
                previous=current1;
                current1=current1->next;
                i++;
            }
            current2=h2;
        }
        else if(len1-len2<0){                              //if list2 is longer than list1
            int diff=len2-len1;
            current1=h2;
            previous=NULL;
            int i=1;
            while(i<=diff){
                previous=current1;
                current1=current1->next;
                i++;
            }
            current2=h1;
        }
        else{
            current1=h1;
            current2=h2;
        }
        l_list *result=NULL;
        int i=0;
        int *carry=&i;
        add_2_equal_lists(current1,current2,carry,&result);
        if(previous!=NULL){    //last element of the longer list before its length equals the other list's length
            if(current2==h2)    //when list1 is longer
                add_carry_to_remaining_elements(h1,previous,carry,&result);
            else               //when list2 is longer
                add_carry_to_remaining_elements(h2,previous,carry,&result);
        }
        if(*carry!=0){         //add 1 more node if there's a remaining carry
            l_list *new_node=(l_list *)malloc(sizeof(l_list));
            new_node->data=*carry;
            new_node->next=result;
            result=new_node;
        }
        return result;
    }
}
void add_carry_to_remaining_elements(l_list *h,l_list *last,int *carry,l_list **result){  //recursive function
    if(h!=last){
        add_carry_to_remaining_elements(h->next,last,carry,result);
    }
    l_list *new_node=(l_list *)malloc(sizeof(l_list));
    int sum=h->data+(*carry);
    *carry=sum/10;                //check if the sum is a 2-digit no.
    new_node->data=sum%10;
    new_node->next=*result;
    *result=new_node;
    return;
}
void add_2_equal_lists(l_list *h1,l_list *h2,int *carry,l_list **result){  //recursive function
    if(h1->next!=NULL){
        add_2_equal_lists(h1->next,h2->next,carry,result);
    }

    l_list *new_node=(l_list *)malloc(sizeof(l_list));
    int sum=h1->data+h2->data+(*carry);
    *carry=sum/10;                //check if the sum is a 2-digit no.
    new_node->data=sum%10;
    new_node->next=*result;
    *result=new_node;
    return;
}
void common_elements_in_2_sorted_lists(l_list *h1,l_list *h2){
    while(h1!=NULL && h2!=NULL){
        if(h1->data==h2->data){
            cout<<h1->data<<" ";
            h1=h1->next;
            h2=h2->next;
        }
        else if(h1->data<h2->data){
            h1=h1->next;
        }
        else{
            h2=h2->next;
        }
    }
    cout<<endl<<endl;
}
int main()
{
    struct l_list *head,*h2,**dhead;
    //head=(l_list*)malloc(sizeof(struct l_list));
    head=h2=NULL;
    dhead=&head;
    print_list(head);
    insert(30,1,dhead);
    //last_modular_node_from_front(1,head);
    insert(41,2,dhead);
    //root_n_node(head);
    insert(50,3,dhead);
    insert(55,4,dhead);
    //root_n_node(head);
    insert(450,5,dhead);
    insert(500,6,dhead);
    print_list(head);
    common_elements_in_2_sorted_lists(head,head);
    root_n_node(head);
    bool palindrome=check_palindrome(head);
    if(palindrome==true)
        cout<<"List is palindrome"<<endl;
    else
        cout<<"List is not palindrome"<<endl;
    first_modular_node_from_end(7,head);
    fractional_node_using_2_pntrs(0,head);
    fractional_node_using_modulus(7,head);
    print_list(head);
    sort_even_odd1(dhead);
    sort_even_odd2(dhead);
    print_list(head);
    odd_even(head);
    //cout<<head->next->next->next->next->next<<endl;
    print_list(head);
    print_in_reverse(head);
    middle(head);
    //reverse_in_pairs(dhead);
    //print_list(head);
    n_node_from_end(5,head);
    print_list(head);
    //head=reverse(head);
    //print_list(head);
    del_element_at_pos(1,dhead);
    print_list(head);
    //del_element_at_pos(3,dhead);
    //del_link_list(dhead);
    //print_list(head);

    insert(1,1,&h2);
    insert(2,2,&h2);
    insert(200,3,&h2);
    insert(210,4,&h2);
    insert(220,5,&h2);
    insert(230,6,&h2);
    insert(240,7,&h2);
    insert(250,8,&h2);
    print_list(h2);
    reverse_in_grps_of_n(8,&h2);
    print_list(h2);
    //cout<<h2->data<<endl;
  
    //merge_sorted_lists_2(head,h2);
    /* l_list *h3=merge_sorted_lists_1(head,h2);
    print_list(h3);

    merge_2_lists(2,head,h2);
    print_list(head);
    print_list(h2);

    merge_pnt_of_2_lists(head,h2); */

    l_list *h3=NULL;
    insert(1,1,&h3);
    insert(2,2,&h3);
    insert(3,3,&h3);
    insert(4,4,&h3);

    l_list *h4=NULL;
    insert(9,1,&h4);
    insert(8,2,&h4);
    insert(7,3,&h4);
    //insert(4,4,&h4);

    l_list *result=add_two_lists_representing_2_numbers(h3,h4);
    print_list(result);
    return 0;
}
