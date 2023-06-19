#include <iostream>
#include <queue>
using namespace std;

struct avl{
    int data;
    int height;
    avl *left;
    avl *right;
};
avl *new_node(int data){
    avl *node=new avl;
    node->data=data;
    node->height=0;
    node->left=NULL;
    node->right=NULL;
    return node;
}
int height(avl *root){
    if(root)
        return root->height;
    else    //NULL
        return -1;
}
avl *single_rotate_left(avl *x){
    avl *w=x->left;
    x->left=w->right;
    w->right=x;
    x->height=max(height(x->left),height(x->right))+1;
    w->height=max(height(w->left),height(x))+1;
    return w;
}
avl *single_rotate_right(avl *x){
    avl *w=x->right;
    x->right=w->left;
    w->left=x;
    x->height=max(height(x->left),height(x->right))+1;
    w->height=max(height(x),height(w->right))+1;
    return w;
}
avl *double_rotate_with_left(avl *x){
    x->left=single_rotate_right(x->left);
    return single_rotate_left(x);
}
avl *double_rotate_with_right(avl *x){
    x->right=single_rotate_left(x->right);
    return single_rotate_right(x);
}
avl *insert(avl *root,int data){
    if(!root){
        root=new avl;
        root->data=data;
        root->left=root->right=NULL;
        root->height=0;
    }
    else if(data<root->data){
        root->left=insert(root->left,data);
        if(height(root->left)-height(root->right)==2){
            if(data<root->left->data)
                root=single_rotate_left(root);
            else //data>root->left->data
                root=double_rotate_with_left(root);
        }
    }
    else if(data>root->data){
        root->right=insert(root->right,data);
        if(height(root->right)-height(root->left)==2){
            if(data>root->right->data)
                root=single_rotate_right(root);
            else //data<root->right->data
                root=double_rotate_with_right(root);
        }
    }
    root->height=max(height(root->left),height(root->right))+1;
    return root;
}
void inorder_traversal(avl *root){
    if(root){
        inorder_traversal(root->left);
        cout<<root->data<<" ";
        inorder_traversal(root->right);
    }
}
void level_order_traversal(avl *root){
    queue<avl *> q;
    if(root){
        q.push(root);
    }
    while(!q.empty()){
        cout<<q.front()->data<<" ";
        avl *node=q.front();
        q.pop();
        if(node->left){
            q.push(node->left);
        }
        if(node->right){
            q.push(node->right);
        }
    }
}
int check_if_avl(avl *root){ //(bst *root)
    if(root){
        int left=check_if_avl(root->left);
        if(left==-1)
            return -1;
        int right=check_if_avl(root->right);
        if(right==-1)
            return -1;
        else{
            if(abs(left-right)>1)
                return -1;
            else
                return max(left,right)+1;
        }
    }
    else
        return 0;
}

avl *build_HB0(int height,int *count){ //AVL with maximum no. of nodes
    if(height>=0){
        avl *node=new_node(0);
        node->height=height;
        node->left=build_HB0(height-1,count);
        node->data=*count;
        *count=*count+1;
        node->right=build_HB0(height-1,count);
        return node;
    }
    else{
        return NULL;
    }
}
avl *build_AVL_with_min_nodes(int height,int *count){
    if(height>=0){
        avl *node=new_node(0);
        node->height=height;
        node->left=build_AVL_with_min_nodes(height-1,count);
        node->data=*count;
        *count=*count+1;
        node->right=build_AVL_with_min_nodes(height-2,count);
        return node;
    }
    else
        return NULL;
}
int main(){
    avl *root=NULL;
    root=insert(root,8);
    root=insert(root,5);    
    root=insert(root,15);
    root=insert(root,2);
    root=insert(root,4);
    root=insert(root,19);
    root=insert(root,20);
    root=insert(root,7);
    root=insert(root,6);
    cout<<"Inorder-traversal: ";
    inorder_traversal(root);
    cout<<endl;
    cout<<"Level-order-traversal: ";
    level_order_traversal(root);
    cout<<endl;

    cout<<"Is the tree an AVL tree: "<<(check_if_avl(root)?"YES":"NO")<<endl;
    
    int count=1;
    avl *root_2=build_HB0(3,&count);
    cout<<"Inorder-traversal: ";
    inorder_traversal(root_2);
    cout<<endl;
    cout<<"Level-order-traversal: ";
    level_order_traversal(root_2);
    cout<<endl;

    count=1;
    avl *root_3=build_AVL_with_min_nodes(3,&count);
    cout<<"Inorder-traversal: ";
    inorder_traversal(root_3);
    cout<<endl;
    cout<<"Level-order-traversal: ";
    level_order_traversal(root_3);
    cout<<endl;
}