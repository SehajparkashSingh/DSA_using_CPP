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
    int height=0;
    if(root){
        enqueue(q,root);
        enqueue(q,NULL);
    }
    while(q->size>0){
        bt *node=dequeue(q);
        if(node!=NULL){
            if(node->left)
                enqueue(q,node->left);
            if(node->right)
                enqueue(q,node->right);
        }
        else{
            height++;
            if(q->size==0){
                break;
            }
            enqueue(q,NULL);
        }
    }
    return (height-1);
}
int min_depth_of_tree_recursive(struct bt *root){
    if(root){
        if(root->left && root->right){
            int ln=min_depth_of_tree_recursive(root->left);
            int rn=min_depth_of_tree_recursive(root->right);
            return ((ln<rn)?(ln+1):(rn+1));
        }
        else if(root->left){
            int ln=min_depth_of_tree_recursive(root->left);
            return ln+1;
        }
        else if(root->right){
            int rn=min_depth_of_tree_recursive(root->right);
            return rn+1;
        }
        else{     //!(root->left) && !(root->right)
            return 1;
        }
    }
    else 
        return 0;
}
int min_depth_of_tree(struct bt *root){
    queue *q=create_queue();
    int depth=0;
    if(root){
        enqueue(q,root);
        enqueue(q,NULL);
    }
    while(q->size>0){
        bt *node=dequeue(q);
        if(node!=NULL){
            if(!(node->left) && !(node->right)){
                depth++;
                break;
            }
            else{
                if(node->left)
                    enqueue(q,node->left);
                if(node->right)
                    enqueue(q,node->right);
            }
        }
        else{      //node==NULL
            enqueue(q,NULL);
            depth++;
        }  
    }
    return depth;
    
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
        if(!(root->left) && !(root->right)){  //leaf node
            int s=0;
            for(int j=0;j<path_length;j++){
                s+=path[j];
            }
            if(s==sum){
                return path_length;
            }
            else 
                return -1;
        }
        else{
            int l_path_sum=path_with_sum(root->left,sum,path,path_length);
            if(l_path_sum!=-1)
                return l_path_sum;
            
            int r_path_sum=path_with_sum(root->right,sum,path,path_length);
            if(r_path_sum!=-1)
                return r_path_sum;
            else 
                return -1;
        }
    }
    else
        return -1;
}
void mirror_bt(struct bt *root){
    if(root){
        mirror_bt(root->left);
        mirror_bt(root->right);
        bt *temp=root->left;
        root->left=root->right;
        root->right=temp;
    }
    return;
}
bool check_mirror(struct bt *root_1, struct bt *root_2){
    if(root_1 && root_2){
        if(root_1->data==root_2->data){
            bool c1=check_mirror(root_1->left,root_2->right);
            bool c2=check_mirror(root_1->right,root_2->left);
            if(c1 && c2)
                return true;
            else
                return false;
        }
        else 
            return false;
    }
    else if(!(root_1) && !(root_2))
        return true;
    else    
        return false;
}
bt *inorder_preorder_2_binary_tree(int *inorder,int *preorder,int inorder_length){
    struct bt *root=NULL;
    struct bt **droot=&root;
    root=new_node(preorder[0]);
    //int i=0;
    int e1=preorder[0];
    int j=0;
    while(inorder[j]!=e1)   
        j++;
    if(j>0){
        root->left=inorder_preorder_2_binary_tree(inorder,preorder+1,j);
        root->right=inorder_preorder_2_binary_tree(inorder+j+1,preorder+j+1,inorder_length-j-1);
    }
    else if(j==0){
        root->left=NULL;
        root->right=inorder_preorder_2_binary_tree(inorder+j+1,preorder+j+1,inorder_length-j-1);
    }
    else if(j==inorder_length-1){
        root->left=inorder_preorder_2_binary_tree(inorder,preorder+1,j);
        root->right=NULL;
    }
    return root;    
}
int ancestors(bt *root,int data,int anc[],int len){
    if(root){
        if(root->data==data){
            anc[len]=data;
            //len++;
            return 1;
        }
        else{
            anc[len]=root->data;
            len++;
            int l_len=ancestors(root->left,data,anc,len);
            if(l_len==1){
                return len+1;
            }
            else if(l_len>1){
                return l_len;
            }
            int r_len=ancestors(root->right,data,anc,len);
            if(r_len==1){
                return len+1;
            }
            else if(r_len>1){
                return r_len;
            }

            else if(l_len==-1 || r_len==-1){
                return -1;
            }
        }
    }
    else{
        return -1;
    }
}

int sum(bt *root){
    if(root){
        return (root->data+sum(root->left)+sum(root->right));
    }
    else{
        return 0;
    }
}
int vertical_sum(bt *root,char position){ //position='c','l','r/R'=>centre,left,right
    if(root){
        if(position=='c'){
            int left_node_sum=vertical_sum(root->left,'l');
            int right_node_sum=vertical_sum(root->right,'r');
            cout<<root->data+left_node_sum+right_node_sum<<" ";
            vertical_sum(root->right,'R');
            return 0;
        }
        else if(position=='l'){
            if(!(root->left) && !(root->right)){
                cout<<root->data<<" ";
                return 0;
            }
            else if(!(root->left) && (root->right)){
                cout<<root->data<<" ";
                return sum(root->right);
            }
            else{        //(root->left)
                int previous_right_node_sum=vertical_sum(root->left,'l');
                cout<<root->data+previous_right_node_sum<<" ";
                if(root->right){
                    int total=sum(root->right);
                    return total;
                }
            }
        }
        else if(position=='r'){
            return sum(root->left);
        }
        else if(position=='R'){
            if(!(root->right) && !(root->left)){
                cout<<root->data<<endl;
                return 0;
            }
            else if(!(root->right) && (root->left)){
                cout<<root->data<<endl;
                return 0;
            }
            else{        //(root->left)
                int previous_left_node_sum=vertical_sum(root->right,'r');
                cout<<root->data+previous_left_node_sum<<" ";
                vertical_sum(root->right,'R');
            }
        }
    }
}

bool check_isomorphism(bt *root_1,bt *root_2){
    if(root_1 && root_2){
        bool left=check_isomorphism(root_1->left,root_2->left);
        bool right=check_isomorphism(root_1->right,root_2->right);
        if(left && right){
            return true;
        }
        else{
            return false;
        }
    }
    else if(!(root_1) && !(root_2)){
        return true;
    }
    else{
        return false;
    }
}
bool check_isomorphism_with_data(bt *root_1,bt *root_2){
    if(root_1 && root_2){
        if(root_1->data!=root_2->data){
            return false;
        }
        bool left=check_isomorphism_with_data(root_1->left,root_2->left);
        bool right=check_isomorphism_with_data(root_1->right,root_2->right);
        if(left && right){
            return true;
        }
        else{
            return false;
        }
    }
    else if(!(root_1) && !(root_2)){
        return true;
    }
    else{
        return false;
    }
}
bool check_quasi_isomorphism(bt *root_1,bt *root_2){
    if(root_1 && root_2){
        bool left=check_quasi_isomorphism(root_1->left,root_2->left);
        bool right=check_quasi_isomorphism(root_1->right,root_2->right);
        if(!left || !right){
            left=check_quasi_isomorphism(root_1->left,root_2->right);
            right=check_quasi_isomorphism(root_1->right,root_2->left);
        }
        if(left && right)
            return true;
        else 
            return false;        
    }
    else if((!(root_1)&& root_2) || root_1 && !(root_2)){
        return false;
    }
    else if(!(root_1) && !(root_2)){
        return true;
    }
}
bool check_quasi_isomorphism_with_data(bt *root_1,bt *root_2){
    if(root_1 && root_2){
        if(root_1->data !=root_2->data){
            return false;
        }
        bool left=check_quasi_isomorphism_with_data(root_1->left,root_2->left);
        bool right=check_quasi_isomorphism_with_data(root_1->right,root_2->right);
        if(!left || !right){
            left=check_quasi_isomorphism_with_data(root_1->left,root_2->right);
            right=check_quasi_isomorphism_with_data(root_1->right,root_2->left);
        }
        if(left && right)
            return true;
        else 
            return false;        
    }
    else if((!(root_1)&& root_2) || root_1 && !(root_2)){
        return false;
    }
    else if(!(root_1) && !(root_2)){
        return true;
    }
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
    cout<<"PRE-ORDER traversal: ";
    pre_order_traversal_recursive(root_1);
    cout<<endl<<"IN-ORDER traversal: ";
    in_order_traversal_recursive(root_1);
    cout<<endl<<"POST-ORDER traversal: ";
    post_order_traversal_recursive(root_1);
    cout<<endl<<"LEVEL-ORDER traversal: ";
    level_order_traversal(root_1);
    cout<<endl;
    cout<<"MAX Element: "<<max_element(root_1)<<endl;
    cout<<"MAX Element using recursion: "<<max_element_using_recursion(root_1)<<endl;
    cout<<"HEIGHT/DEPTH of tree: "<<height_of_tree(root_1)<<endl;   
    cout<<"HEIGHT/DEPTH of tree using recursion: "<<height_of_tree_recursive(root_1)<<endl;
    cout<<"MIN DEPTH of tree : "<<min_depth_of_tree(root_1)<<endl;
    cout<<"MIN DEPTH of tree using recursion: "<<min_depth_of_tree_recursive(root_1)<<endl;
    cout<<"DEEPEST element: "<<deepest_element(root_1)<<endl;
    cout<<"No. of leaves: "<<no_of_leaves(root_1)<<endl;
    cout<<"No. of leaves using recursion: "<<no_of_leaves_recursive(root_1)<<endl;
    cout<<"No. of full nodes: "<<no_of_full_nodes(root_1)<<endl;
    cout<<"No. of full nodes using recursion: "<<no_of_full_nodes_recursive(root_1)<<endl;
    cout<<"No. of half nodes: "<<no_of_half_nodes(root_1)<<endl;
    cout<<"No. of half nodes using recursion: "<<no_of_half_nodes_recursive(root_1)<<endl;   
    cout<<"Level with max. sum: "<<level_with_max_sum(root_1)<<endl;
    cout<<"SUM of all elements: "<<sum(root_1)<<endl;
    int *path=new int[1];
    cout<<"All possible paths from root node:"<<endl;
    print_root_2_leave_paths(root_1,path,0);
    cout<<endl;
    int path_length=path_with_sum(root_1,24,path,0);
    if(path_length!=-1){
        cout<<"PATH with the given sum: ";
        for(int j=0;j<path_length;j++){
            cout<<path[j]<<" ";
        }
        cout<<endl;
    }
    else{
        cout<<"NO PATH exists with the given sum"<<endl;
    }

    struct bt *root_2=NULL;
    struct bt **droot_2=&root_2;
    insert(droot_2,10);
    insert(droot_2,2);
    insert(droot_2,3);
    insert(droot_2,4);
    insert(droot_2,5);
    insert(droot_2,6);
    insert(droot_2,7);
    insert(droot_2,8);
    mirror_bt(root_2);
    cout<<"LEVEL-ORDER traversal: ";
    level_order_traversal(root_2);
    cout<<endl;
    cout<<"BT_1 and BT_2 are mirrors or not: "<<((check_mirror(root_1,root_2))?("YES"):("NO"))<<endl;
    int inorder[]={1,2,3,4,5,6};
    int preorder[]={4,2,1,3,6,5};
    //struct bt *root_3=inorder_preorder_2_binary_tree(inorder,preorder,6);
    int *anc=new int[1];
    int len=ancestors(root_2,8,anc,0);
    if(len!=-1){
        cout<<"PATH with the given number: ";
        for(int j=0;j<len;j++){
            cout<<anc[j]<<" ";
        }
        cout<<endl;
    }
    else{
        cout<<"NO PATH exists with the given number"<<endl;
    }
    cout<<"VERTICAL SUM OF BINARY TREE: ";
    vertical_sum(root_1,'c');
    cout<<"BT_1 and BT_2 are isomorphic or not: "<<((check_isomorphism(root_1,root_2))?("YES"):("NO"))<<endl;
    cout<<"BT_1 and BT_1 are isomorphic or not: "<<((check_isomorphism(root_1,root_1))?("YES"):("NO"))<<endl;
    cout<<"BT_1 and BT_2 are isomorphic(with data) or not: "<<((check_isomorphism_with_data(root_1,root_2))?("YES"):("NO"))<<endl;
    
    cout<<"BT_1 and BT_2 are quasi-isomorphic or not: "<<((check_quasi_isomorphism(root_1,root_2))?("YES"):("NO"))<<endl;
    cout<<"BT_1 and BT_1 are quasi-isomorphic or not: "<<((check_quasi_isomorphism(root_1,root_1))?("YES"):("NO"))<<endl;    
    cout<<"BT_1 and BT_2 are quasi-isomorphic(with data) or not: "<<((check_quasi_isomorphism_with_data(root_1,root_2))?("YES"):("NO"))<<endl;

    //del_tree(droot_1);
    //pre_order_traversal(root_1);
}