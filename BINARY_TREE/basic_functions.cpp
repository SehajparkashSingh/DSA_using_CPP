#include <iostream>
using namespace std;

struct bt{
    int data;
    struct bt *left;
    struct bt *right;
};
struct queue{
    int capacity;
    int size;
    int front;
    int rear;
    struct bt **node_arr;
};
struct queue *create_queue(int capacity=10){
    struct queue *q=(struct queue*)malloc(sizeof(queue));
    if(q){
        q->capacity=capacity;
        q->size=0;
        q->node_arr=(struct bt**)malloc(capacity*sizeof(struct bt*));
        q->front=-1;
        q->rear=-1;
    }
    return q;
}
int reallocate(queue *q){
    int prev_cap=q->capacity;
    q->capacity*=2;
    q->node_arr=(struct bt**)realloc(q->node_arr,q->capacity*sizeof(struct bt*));
    if(!q->node_arr)
        return -1;
    if(q->front>q->rear){
        for(int i=0;i<q->front;i++){
            q->node_arr[prev_cap+i]=q->node_arr[i];
        }
    }
    return 1;
}
void enqueue(queue *q,struct bt *node){
    if(q->size==q->capacity)        //full
        if(reallocate(q)==-1){
            cout<<"Queue already full,cannot assign more memory"<<endl<<endl;
            return;
        }
    //if(!full(q))
    {
        if(q->size==0){       //empty
            q->front++;
            q->rear++;        //q->arr[++q->rear]==d;
            q->node_arr[q->rear]=node;         
        }
        else if(q->rear!=q->capacity-1){
            q->rear++;       //q->arr[++q->rear]=d;
            q->node_arr[q->rear]=node;
        }
        else{            //rear==capacity-1
            q->rear=0;
            q->node_arr[q->rear]=node;
        }
        q->size++;
    }
    return;
}
struct bt *dequeue(queue *q){
    struct bt *node;
    if(!(q->size==0)){           //not empty
        if(q->size>1){                 //q->front!=q->rear
            if(q->front!=q->capacity-1){
                node=q->node_arr[q->front++];
            }
            else{
                node=q->node_arr[q->front];
                q->front=0;
            }
        }
        else{                  //q->front==q->rear
            node=q->node_arr[q->front];
            q->front=q->rear=-1;
        }
        q->size--;
        return node;
    }
    else
        cout<<"Queue already empty"<<endl<<endl;
    return NULL;
}
void del_queue(queue *q){
    if(q){
        free(q->node_arr);
        free(q);
        q=NULL;
    }
}
struct bt *level_order_transverse(struct bt *root){
    struct queue *q=create_queue(10);
    enqueue(q,root);
    while (q->size>0){
        struct bt *node=dequeue(q);
        if(node->left){
            enqueue(q,node->left);
        }
        else{
            del_queue(q);
            return node;
        }
        if(node->right){
            enqueue(q,node->right);
        }
        else{
            del_queue(q);
            return node;
        }
    }
    return NULL;
}
struct bt *new_node(int data){
    struct bt *node=(struct bt *)malloc(sizeof(struct bt));
    node->data=data;
    node->left=NULL;
    node->right=NULL;
    return node;
}
void insert(struct bt **droot,int data){
    struct bt *root=*droot;
    if(!(root)){
        root=new_node(data);
        *droot=root;
    }
    else{
        struct bt *last_node_precursor=level_order_transverse(root);
        if(last_node_precursor->left==NULL){
            last_node_precursor->left=new_node(data);
        }
        else{
            last_node_precursor->right=new_node(data);
        }
    }
}
void pre_order_traversal_recursive(struct bt *root){
    if(root){
        cout<<root->data<<" ";
        pre_order_traversal_recursive(root->left);
        pre_order_traversal_recursive(root->right);
    }
}
void in_order_traversal_recursive(struct bt *root){
    if(root){
        in_order_traversal_recursive(root->left);
        cout<<root->data<<" ";
        in_order_traversal_recursive(root->right);
    }
}
void post_order_traversal_recursive(struct bt *root){
    if(root){
        post_order_traversal_recursive(root->left);
        post_order_traversal_recursive(root->right);
        cout<<root->data<<" ";
    }
}
void level_order_traversal(struct bt *root){
    struct queue *q=create_queue();
    if(root){
        enqueue(q,root);
    }
    while(q->size!=0){
        struct bt *node=dequeue(q);
        cout<<node->data<<" ";
        if(node->left){
            enqueue(q,node->left);
        }
        else{
            continue;
        }
        if(node->right){
            enqueue(q,node->right);
        }
    }
    del_queue(q);
}
int max_element(struct bt *root){
    struct queue *q=create_queue();
    if(root){
        enqueue(q,root);
    }
    int max=root->data;
    while(q->size!=0){
        struct bt *node=dequeue(q);
        if(node->data>max){
            max=node->data;
        }
        if(node->left){
            enqueue(q,node->left);
        }
        if(node->right){
            enqueue(q,node->right);
        }
    }
    del_queue(q);
    return max;
}
int max_element_using_recursion(struct bt *root){
    int max;
    if(root){
        max=root->data;
        int lm=max_element_using_recursion(root->left);
        int rm=max_element_using_recursion(root->right);
        if(max>lm){
            if(max>rm)
                return max;
            else
                return rm;
        }
        else{
            if(lm>rm)
                return lm;
            else    
                return rm;
        }
    }
    else
        return INT_MIN;
}
int height_of_tree_recursive(struct bt *root){
    int lh,rh;
    if(root){
        lh=height_of_tree_recursive(root->left)+1;
        rh=height_of_tree_recursive(root->right)+1;
        if(lh>rh){
            return lh;
        }
        else{
            return rh;
        }
    }
    else{
        return -1;
    }
}
int height_of_tree(struct bt *root){
    struct queue *q=create_queue();
    int level,i;
    if(root){
        enqueue(q,root);
        level=0;
        i=1;      //no. of nodes at level 1
    }
    while(q->size>0){
        for(int j=1;j<=i && q->size;j++){
            bt *node=dequeue(q);
            if(node->left)
                enqueue(q,node->left);
            if(node->right)
                enqueue(q,node->right);
        }
        level++;
        i=1;
        for(int j=1;j<=level;j++){
            i*=2;
        }
    }
    return (level-1);
}
int deepest_element(struct bt *root){
    struct queue *q=create_queue();
    if(root){
        enqueue(q,root);
    }
    while(q->size>0){   //not empty
        struct bt *node=dequeue(q);
        if(node->left || node->right){
            if(node->left){
                enqueue(q,node->left);
            }
            if(node->right){
                enqueue(q,node->right);
            }
        }
        else if(q->size==0){
            del_queue(q);
            return node->data;
        }
    }
}
int no_of_leaves(struct bt *root){
    int n=0;
    struct queue *q=create_queue();
    if(root){
        enqueue(q,root);
    }
    while(q->size>0){
        struct bt *node=dequeue(q);
        if(node->left || node->right){
            if(node->left){
                enqueue(q,node->left);
            }
            if(node->right){
                enqueue(q,node->right);
            }
        }
        else{
            n++;
        }
    }
    del_queue(q);
    return n;
}
int no_of_leaves_recursive(struct bt *root){
    if(root){
        if(!(root->left) && !(root->right)){
            return 1;
        }
        else{
            int ln=no_of_leaves_recursive(root->left);
            int rn=no_of_leaves_recursive(root->right);
            return (ln+rn);
        }
    }
    else
        return 0;
}
int no_of_full_nodes_recursive(struct bt *root){
    int ln,rn;
    if(root){
        ln=no_of_full_nodes_recursive(root->left);
        rn=no_of_full_nodes_recursive(root->right);
        if(root->left && root->right){
            return (1+ln+rn);
        }
        else{
            return (0+ln+rn);
        }
    }
    else 
        return 0;
}
int no_of_full_nodes(struct bt *root){
    struct queue *q=create_queue();
    int n=0;
    if(root){
        enqueue(q,root);
    }
    while(q->size>0){
        struct bt *node=dequeue(q);
        if(node->left && node->right){
            n++;
        }
        if(node->left)
            enqueue(q,node->left);
        if(node->right)
            enqueue(q,node->right);
    }
    return n;
}
int no_of_half_nodes(struct bt *root){
    struct queue *q=create_queue();
    int n=0;
    if(root){
        enqueue(q,root);
    }
    while(q->size>0){
        struct bt *node=dequeue(q);
        if(node->left){
            if(!(node->right))
                n++;
        }
        else if(node->right){
            if(!(node->left))
                n++;
        }
        if(node->left)
            enqueue(q,node->left);
        if(node->right)
            enqueue(q,node->right);
    }
    return n;
}
int no_of_half_nodes_recursive(struct bt *root){
    if(root){
        int lhn=no_of_half_nodes_recursive(root->left);
        int rhn=no_of_half_nodes_recursive(root->right);
        if((root->left && !(root->right)) || (!(root->left) && root->right)){
            return (1+lhn+rhn);
        }
        else
            return (0+lhn+rhn);
    }
    else
        return 0;
}
void del_tree(struct bt **droot){
    struct bt *root=*droot;
    if(root){
        del_tree(&(root->left));
        del_tree(&(root->right));
        free(root);
        *droot=NULL;
    }
}

int level_with_max_sum(struct bt *root){
    struct queue *q=create_queue();
    int max_sum=0;
    if(root){
        enqueue(q,root);
    }
    int l=0;       //level 0
    int max_sum_level=0;     //Level-0
    int i=1;       //no. of nodes at level 'l'

    while(q->size>0){
        //if(q->size<=i){
            int sum=0;
            for(int j=1;j<=i && q->size;j++){
                bt *node=dequeue(q);
                sum+=node->data;
                if(node->left)
                    enqueue(q,node->left);
                if(node->right)
                    enqueue(q,node->right);
            }
            if(sum>max_sum){
                max_sum_level=l;
                max_sum=sum;
            }
            l++;
            i=1;
            for(int j=1;j<=l;j++){
                i*=2;
            }
        //}
    }
    return max_sum_level;
}
void print_root_2_leave_paths(struct bt *root,int path[],int path_length){
    if(root){
        path[path_length]=root->data;
        path_length++;
        if(!(root->left) && !(root->right)){
            for(int j=0;j<path_length;j++){
                cout<<path[j]<<" ";
            }
            cout<<endl;
        }
        else{
            print_root_2_leave_paths(root->left,path,path_length);
            print_root_2_leave_paths(root->right,path,path_length);
        }
    }
    else
        return;
}
int path_with_sum(struct bt *root,int sum,int path[],int path_length){
    if(root){
        path[path_length]=root->data;
        path_length++;
        if(!(root->left) && !(root->right)){
            int s=0;
            for(int j=0;j<path_length;j++){
                s+=path[j];
            }
            if(s==sum){
                return path_length;
            }
        }
        else{
            path_with_sum(root->left,sum,path,path_length);
            path_with_sum(root->right,sum,path,path_length);
        }
    }
    else
        return -1;
}
int main(){
    struct bt *root_1=NULL;
    struct bt **droot_1=&root_1;
    insert(droot_1,10);
    insert(droot_1,2);
    insert(droot_1,3);
    insert(droot_1,4);
    insert(droot_1,5);
    insert(droot_1,6);
    insert(droot_1,7);
    insert(droot_1,8);
    //insert(droot_1,9);
    pre_order_traversal_recursive(root_1);
    cout<<endl;
    in_order_traversal_recursive(root_1);
    cout<<endl;
    post_order_traversal_recursive(root_1);
    cout<<endl;
    level_order_traversal(root_1);
    cout<<endl;
    cout<<"MAX Element: "<<max_element(root_1)<<endl;
    cout<<"MAX Element using recursion: "<<max_element_using_recursion(root_1)<<endl;
    cout<<"HEIGHT/DEPTH of tree: "<<height_of_tree(root_1)<<endl;   
    cout<<"HEIGHT/DEPTH of tree using recursion: "<<height_of_tree_recursive(root_1)<<endl;
    cout<<"DEEPEST element: "<<deepest_element(root_1)<<endl;
    cout<<"No. of leaves: "<<no_of_leaves(root_1)<<endl;
    cout<<"No. of leaves using recursion: "<<no_of_leaves_recursive(root_1)<<endl;
    cout<<"No. of full nodes: "<<no_of_full_nodes(root_1)<<endl;
    cout<<"No. of full nodes using recursion: "<<no_of_full_nodes_recursive(root_1)<<endl;
    cout<<"No. of half nodes: "<<no_of_half_nodes(root_1)<<endl;
    cout<<"No. of half nodes using recursion: "<<no_of_half_nodes_recursive(root_1)<<endl;   
    cout<<"Level with max. sum: "<<level_with_max_sum(root_1)<<endl;
    int *path=new int[1];
    print_root_2_leave_paths(root_1,path,0);
    int path_length=path_with_sum(root_1,20,path,0);
    for(int j=0;j<path_length;j++){
        cout<<path[j]<<" ";
    }
    cout<<endl;
    //del_tree(droot_1);
    //pre_order_traversal(root_1);
}