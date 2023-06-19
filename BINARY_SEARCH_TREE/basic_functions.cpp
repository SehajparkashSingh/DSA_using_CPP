#include <iostream>
#include <queue>
using namespace std;

struct bst{
    int data;
    struct bst *left;
    struct bst *right;
};
bst *new_node(int data){
    struct bst *node=new bst;
    node->data=data;
    node->left=NULL;
    node->right=NULL;
    return node;
}
void insert(bst **droot,int data){
    bst *root=*droot;
    if(root==NULL){
        root=new_node(data);
        *droot=root;
    }
    else{
        while(root){
            if(root->data>=data){
                if(root->left==NULL){
                    root->left=new_node(data);
                    break;
                }
                else
                    root=root->left;
            }
            else{         //root->data<data
                if(root->right==NULL){
                    root->right=new_node(data);
                    break;
                }
                else
                    root=root->right;
            }
        }
    }
}
void level_order_traversal(bst *root){
    queue<bst *> q;
    if(root){
        q.push(root);
    }
    while(!q.empty()){
        bst *node=q.front();
        cout<<node->data<<" ";
        q.pop();
        if(node->left)
            q.push(node->left);
        if(node->right)
            q.push(node->right);
    }
}
void inorder_traversal(bst *root){
    if(root){
        inorder_traversal(root->left);
        cout<<root->data<<" ";
        inorder_traversal(root->right);
    }
}
int minimum(bst *root){
    int min=INT_MIN;
    if (root){
        min=root->data;
    }
    while(root->left){
        min=root->left->data;
        root=root->left;
    }
    return min; 
}
int minimum_recursive(bst *root){
    if(!root){
        return INT_MIN;
    }
    if(root->left){
        return (minimum_recursive(root->left));    
    }
    else{
        return root->data;
    }
}
int maximum(bst *root){
    int max=INT_MIN;
    if (root){
        max=root->data;
    }
    while(root->right){
        max=root->right->data;
        root=root->right;
    }
    return max; 
}
int maximum_recursive(bst *root){
    if(!root){
        return INT_MIN;
    }
    if(root->right){
        return (maximum_recursive(root->right));    
    }
    else{
        return root->data;
    }
}
bst *delete_element_recursive(bst *root,int data){
    if(root==NULL){      //Data element does not exist
        return root;
    }
    else if(root->data==data){
        if(!(root->left)){
            bst *temp=root;
            root=root->right;
            //*droot=root;
            delete temp;
            return root;
        }
        else if(!(root->right)){
            bst *temp=root;
            root=root->left;
            //*droot=root;
            delete temp;
            return root;
        }
        else{
            bst *replacement_parent=root;
            bst *replacement_node=replacement_parent->left;
            while(replacement_node->right){
                replacement_parent=replacement_node;
                replacement_node=replacement_parent->right;
            }
                       
            if(replacement_parent==root){
                replacement_node->right=root->right;
                root=replacement_node;
            }

            else{
                bst *duplicate=new_node(replacement_node->data);
                duplicate->left=replacement_node->left;
                
                replacement_node->left=root->left;
                replacement_node->right=root->right;
                root=replacement_node;

                if(duplicate->left){
                    replacement_parent->right=duplicate->left;
                }
                else{
                    replacement_parent->right=NULL;
                }
            }
            return root;
        }
    }
    else{
        if(data<=root->data){
            root->left=delete_element_recursive(root->left,data);
        }
        else{
            root->right=delete_element_recursive(root->right,data);
        }
        return root;
    }
}   
void inorder_predecessor_recursive(bst *root,int data,int *p){
    if(root){
        inorder_predecessor_recursive(root->left,data,p);
        if(root->data==data){
            if(*p==-1){
                cout<<"No predecessor of "<<root->data<<endl;
            }
            else{
                cout<<"Predecessor: "<<*p<<" , Data: "<<root->data<<endl;
            }
            return;
        }
        else{
            *p=root->data;
            inorder_predecessor_recursive(root->right,data,p);
        }

    }
    else
        return;
}
void inorder_successor_recursive(bst *root,int data,int *p){
    if(root){
        if(root->data==data){
            inorder_successor_recursive(root->right,data,p);
            if(*p>root->data)
                cout<<"Data: "<<root->data<<" , Successor: "<<*p<<endl;
            else
                cout<<"No successor of "<<root->data<<endl;
            return;
        }
        else{
            int x=*p;
            *p=root->data;
            inorder_successor_recursive(root->left,data,p);
        
            int t=*p;
            *p=x;
            inorder_successor_recursive(root->right,data,p);
            *p=t;
        }
    }
}
void LCA_recursive(bst *root,int data_1,int data_2){
    if(root){
        if(root->data>data_1 && root->data<data_2){
            cout<<"LCA of "<<data_1<<" & "<<data_2<<" is: "<<root->data<<endl;
            return;
        }
        else if(root->data<data_1){
            LCA_recursive(root->right,data_1,data_2);
        }
        else if(root->data>data_2){
            LCA_recursive(root->left,data_1,data_2);
        }
        else if(root->data==data_1 || root->data==data_2){
            cout<<"LCA of "<<data_1<<" & "<<data_2<<" is: "<<root->data<<endl;
            return;
        }
    }
}
void shortest_path_recursive(bst *root,int data_1,int data_2){
    if(root){
        if(root->data>data_1 && root->data<data_2){
            int path=1;
            bst *temp=root->left;
            while(temp->data!=data_1){
                temp=(temp->data>data_1)?(temp->left):(temp->right);
                path++;
            }
            temp=root->right;
            path++;
            while(temp->data!=data_2){
                temp=(temp->data>data_2)?(temp->left):(temp->right);
                path++;
            }
            cout<<"Shortest path length b/w "<<data_1<<" & "<<data_2<<" is: "<<path<<endl;
            return;
        }
        else if(root->data<data_1){
            shortest_path_recursive(root->right,data_1,data_2);
        }
        else if(root->data>data_2){
            shortest_path_recursive(root->left,data_1,data_2);
        }
        else if(root->data==data_1 || root->data==data_2){
            int d=(root->data==data_1)?(data_2):(data_1);
            bst *temp=(root->data==data_1)?(root->right):(root->left);
            int path=1;
            while(temp->data!=d){
                temp=(temp->data>d)?(temp->left):(temp->right);
                path++;
            }
            cout<<"Shortest path length b/w "<<data_1<<" & "<<data_2<<" is: "<<path<<endl;
            return;
        }
    }
}
bool check_if_bst_recursive(bst *root){
    if(root){
        if(check_if_bst_recursive(root->left) && check_if_bst_recursive(root->right)){
            if(root->left && root->right){
                if(root->left->data<root->right->data && root->data>root->left->data && root->data<root->right->data)
                    return true;
                else
                    return false;

            }
            else if(root->left){
                return (root->data>root->left->data);
            }
            else if(root->right){
                return (root->data<root->right->data);
            }
            else{
                return true;
            }
        }
        else{
            return false;
        }
    }
    else
        return true;
}
bool check_if_bst_inorder(bst *root,int *prev){
    if(root){
        if(!(check_if_bst_inorder(root->left,prev)))
            return true;
        if(root->data<*prev)
            return false;
        *prev=root->data;
        return check_if_bst_inorder(root->right,prev);
    }
    else{
        return true;
    }
}
bst *sorted_array_2_balanced_bst(int *arr,int left_ind,int right_ind){
    if(left_ind<right_ind){
        int mid=(left_ind+right_ind)/2;
        bst *node=new_node(arr[mid]);
        node->left=sorted_array_2_balanced_bst(arr,left_ind,mid-1);
        node->right=sorted_array_2_balanced_bst(arr,mid+1,right_ind);
        return node;
    }
    else if(left_ind==right_ind){
        bst *node=new_node(arr[left_ind]);
        return node;
    }
    else if(left_ind>right_ind){
        return NULL;
    }
}
int kth_smallest_element(bst *root,int k,int *count){
    if(root)
    {   
        int small;
        if(root->left)
            small=kth_smallest_element(root->left,k,count);
            if(*count==k)
                return small;

        *count=*count+1;
        if(*count==k){
            small=root->data;
        }
        else if(root->right)
            small=kth_smallest_element(root->right,k,count);
        return small;
    }    
    else
        return -1;
}
void print_in_range_recursive(bst *root,int d1,int d2){
    if(root){
        if(root->data>=d1){
            print_in_range_recursive(root->left,d1,d2);
        }
        if(root->data>=d1 && root->data<=d2){
            cout<<root->data<<" ";
        }
        if(root->data<=d2){
            print_in_range_recursive(root->right,d1,d2);
        }
    }
}
bst *trim_bst(bst *root,int d1,int d2){
    if(root){
        if(root->data>d1 && root->data<d2){
            root->left=trim_bst(root->left,d1,root->data);
            root->right=trim_bst(root->right,root->data,d2);
            return root;
        }
        else if(root->data<d1){
            return (trim_bst(root->right,d1,d2));
        }
        else if(root->data>d2){
            return (trim_bst(root->left,d1,d2));
        }
        else if(root->data==d1){
            root->left=NULL;
            root->right=trim_bst(root->right,root->data,d2);
            return root;
        }
        else if(root->data==d2){
            root->left=trim_bst(root->left,d1,root->data);
            root->right=NULL;
            return root;
        }
        else{
            return NULL;
        }
    }
    else 
        return NULL; 
}
int count_BSTs(int n){
    if(n<=1){
        return 1;
    }
    else{
        int sum=0;
        int left,right;
        for(int root=1;root<=n;root++){
            left=count_BSTs(root-1);
            right=count_BSTs(n-root);
            sum+=left*right;
        }
        return sum;
    }
}
int main(){
    bst *root_1=NULL;
    bst **droot_1=&root_1;
    insert(droot_1,4);
    insert(droot_1,2);
    insert(droot_1,3);
    insert(droot_1,1);
    insert(droot_1,5);
    insert(droot_1,8);
    insert(droot_1,7);
    cout<<"Level-order traversal: ";
    level_order_traversal(root_1);
    cout<<endl;
    cout<<"In-order traversal: ";
    inorder_traversal(root_1);
    cout<<endl;
    cout<<"Minimum element: "<<minimum(root_1)<<endl;
    cout<<"Minimum element using recursion: "<<minimum_recursive(root_1)<<endl;
    cout<<"Maximum element: "<<maximum(root_1)<<endl;
    cout<<"Maximum element using recursion: "<<maximum_recursive(root_1)<<endl;
    //root_1=delete_element_recursive(root_1,4);
    cout<<"Level-order traversal: ";
    level_order_traversal(root_1);
    cout<<endl;
    int p=-1;
    inorder_predecessor_recursive(root_1,5,&p);
    p=-1;
    inorder_successor_recursive(root_1,2,&p);
    
    LCA_recursive(root_1,1,3);
    shortest_path_recursive(root_1,3,4);
    
    cout<<"Is the tree a BST: "<<((check_if_bst_recursive(root_1))?("YES"):("NO"))<<endl;
    int prev=INT_MIN;
    cout<<"Is the tree a BST: "<<((check_if_bst_inorder(root_1,&prev))?("YES"):("NO"))<<endl;
    
    int arr[]={5,7,10,16,19,21,28,45};
    bst *root_3=sorted_array_2_balanced_bst(arr,0,7); //Balanced BST
    cout<<"In-order traversal: ";
    inorder_traversal(root_3);
    cout<<endl;
    cout<<"Level-order traversal: ";
    level_order_traversal(root_3);
    cout<<endl;
    int k=6,count=0;
    cout<<k<<"th smallest element: "<<kth_smallest_element(root_3,k,&count)<<endl;
    print_in_range_recursive(root_3,20,50);
    cout<<endl;

    root_3=trim_bst(root_3,1,30);
    cout<<"In-order traversal: ";
    inorder_traversal(root_3);
    cout<<endl;
    cout<<"Level-order traversal: ";
    level_order_traversal(root_3);
    cout<<endl;
   
    int n=3;
    cout<<"No. of BSTs possible with "<<n<<" keys: "<<count_BSTs(n)<<endl;
} 