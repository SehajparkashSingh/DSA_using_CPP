#include <iostream>
using namespace std;

//A COMPLETE BINARY TREE
struct heap{
    int *array;
    int capacity;
    int count;
    int type;
};
heap *create_heap(int capacity=10,int type=1){
    heap *h=new heap;
    h->capacity=capacity;
    h->count=0;
    h->type=type;
    h->array=new int[h->capacity];
    return h;
}
void reallocate(heap *h){
    h->capacity*=2;
    h->array=(int *)realloc(h->array,sizeof(int)*h->capacity);
}
int parent_index(heap *h,int i){            //O(1)
    if(i<=0 || i>=h->count)
        return -1;
    else
        return (i-1)/2;
}
int left_child_index(heap *h,int i){        //O(1)
    int left=2*i+1;
    if(left>=h->count)
        return -1;
    else
        return left;
}
int right_child_index(heap *h,int i){       //O(1)
    int right=2*i+2;
    if(right>=h->count)
        return -1;
    else
        return right;
}
int get_maximum(heap *h){                   //O(1)
    if(h->count!=0)
        return h->array[0];
    else
        return -1;
}
void percolate_down(heap *h,int i){    //HEAPIFY DOWNWARDS   O(LOG N)
    int left,right;
    left=left_child_index(h,i);
    right=right_child_index(h,i);
    int max_ind=i;
    if(left!=-1 && h->array[left]>h->array[max_ind])
        max_ind=left;
    if(right!=-1 && h->array[right]>h->array[max_ind])
        max_ind=right;
    if(max_ind!=i){
        int temp=h->array[i];
        h->array[i]=h->array[max_ind];
        h->array[max_ind]=temp;
        percolate_down(h,max_ind);
    }
}
void percolate_up(heap *h,int i){      //HEAPIFY UPWARDS     O(LOG N)
    int parent_ind=parent_index(h,i);
    if(parent_ind!=-1){
        if(h->array[i]>h->array[parent_ind]){
            int temp=h->array[i];
            h->array[i]=h->array[parent_ind];
            h->array[parent_ind]=temp;
            percolate_up(h,parent_ind);
        }
    }
}
int del_max(heap *h){                       //log(n)
    if(h->count>0){
        int max=h->array[0];
        h->array[0]=h->array[h->count-1];
        h->count--;
        percolate_down(h,0);                //log(n)
        return max;
    }
    else    
        return -1;
}
void insert(heap *h,int data){              //O(log n)
    if(h->capacity==h->count){
        reallocate(h);
    }
    h->count++;
    int i=h->count-1; //last location
    while(data>h->array[parent_index(h,i)] && i>0){   //PERCOLATE UP   O(log n)
        h->array[i]=h->array[parent_index(h,i)];
        i=parent_index(h,i);
    }
    h->array[i]=data;
}
void build_heap_from_array(heap *h,int a[],int n){      //O(n)
    if(h){
        while(n>h->capacity)
            reallocate(h);
        for(int i=0;i<n;i++)                    //O(n)
            h->array[i]=a[i];
        h->count=n;
        for(int i=parent_index(h,n-1);i>=0;i--){     //'i' starts from last non-leaf node
            percolate_down(h,i);     
        }
    }
}
void del_heap(heap **dh){
    heap *h=*dh;
    if(h){
        free(h->array);
        free(h);
        h=NULL;
    }
    *dh=h;
}
void heapsort(int a[],int n){       // O(nlogn)
    cout<<"ORIGINAL ARRAY: ";
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    cout<<endl;
    heap *h=create_heap(15);
    build_heap_from_array(h,a,n);          //O(n)
    int org_size=h->count;
    for(int i=0;i<n;i++){                  //runs 'n' times 
        int t=h->array[0];      //MAX
        h->array[0]=h->array[h->count-1];
        h->array[h->count-1]=t;
        h->count--;
        percolate_down(h,0);                //O(log n)
    }
    h->count=org_size;
    cout<<"SORTED ARRAY: ";
    for(int i=0;i<h->count;i++){
        cout<<h->array[i]<<" ";
    }
    cout<<endl;
}
int min_element(heap *h){                 //Search in only leaf nodes
    int last_leaf_parent=parent_index(h,h->count-1);
    int first_leaf_index=last_leaf_parent+1;
    int min=INT_MAX;
    for(int i=0;i<h->count;i++){        //O(n)
        if(h->array[i]<min)
            min=h->array[i];
    }
    return min;
}
void level_order_traversal(heap *h){
    int n=h->count;
    for(int i=0;i<n;i++){
        cout<<h->array[i]<<" ";
    }
    cout<<endl;
}
void del_element(heap *h,int data){         //O(n)
    int n=h->count;
    int ind=-1;
    for(int i=0;i<n;i++){                   //O(n)
        if(data==h->array[i]){
            ind=i;
            break;
        }
    }
    if(ind!=-1){
        h->array[ind]=h->array[h->count-1];
        h->count--;
        percolate_down(h,ind);            //O(logn)
        return;
    }
    else 
        return;
}
void del_at_index(heap *h,int ind){         //O(logn)
    if(h){
        if(ind>-1 && ind<h->count){
            h->array[ind]=h->array[h->count-1];
            h->count--;
            percolate_down(h,ind);          //O(logn)
        }
    }
}
void traverse_from_parent_to_child(heap *h,int ind){      //O(n)
    if(ind>-1){
        cout<<h->array[ind]<<" ";
        traverse_from_parent_to_child(h,left_child_index(h,ind));
        traverse_from_parent_to_child(h,right_child_index(h,ind));
    }
}
void elements_less_than_k(heap *h,int ind,int k){      //O(n) 
    if(ind>-1){
        if(h->array[ind]<k){
            traverse_from_parent_to_child(h,ind);
        }
        else{
            elements_less_than_k(h,left_child_index(h,ind),k);
            elements_less_than_k(h,right_child_index(h,ind),k);
        }
    }
}
void elements_greater_than_k(heap *h,int ind,int k){       //O(n)
    if(ind>-1){
        if(h->array[ind]>k){
            cout<<h->array[ind]<<" ";
        }
        elements_greater_than_k(h,left_child_index(h,ind),k);
        elements_greater_than_k(h,right_child_index(h,ind),k);
    }
}
heap *merge_2_heaps(heap *h1,heap *h2){           // O(m(log(n+m)))
    heap *h=create_heap(h1->count+h2->count);
    for(int i=0;i<h1->count;i++){
        h->array[i]=h1->array[i];
        h->count++;
    }
    int ind=h->count;
    for(int j=0,i=ind;i<h->capacity;i++,j++){
        h->array[i]=h2->array[j];
        h->count++;
    }
    int first_non_leaf_index=parent_index(h,h->count-1);
    for(int i=h->count;i>=h1->count;i--){    //O(m)
        percolate_up(h,i);          //log(h1->count+h2->count)= O(log(n+m))
    }
    return h;
}
//CAN ALSO BE USED TO GET 1st 'K' LARGEST ELEMENTS
int kth_largest_element(heap *h,int k){       //kth_smallest for MIN HEAP
    for(int i=1;i<k;i++){                       //O(klogn)
        del_max(h);
    }
    return del_max(h);
}
int main(){
    int n;
    cout<<"ENTER THE SIZE OF ARRAY TO BE SORTED:";
    cin>>n;
    int *arr=new int[n];
    cout<<"ENTER THE "<<n<<" NUMBERS"<<":"<<endl;
    for(int i=0;i<n;i++){
        cin>>arr[i];
    }
    heapsort(arr,n);

    cout<<"ENTER THE SIZE OF HEAP:";
    cin>>n;
    heap *h=create_heap(10);
    cout<<"ENTER THE "<<n<<" NUMBERS TO INSERT INTO HEAP"<<":"<<endl;
    for(int i=0;i<n;i++){
        int data;
        cin>>data;
        insert(h,data);
    }
    cout<<"MIN IN HEAP: "<<min_element(h)<<endl;
    cout<<"LEVEL ORDER TRAVERSAL: ";
    level_order_traversal(h);

    cout<<"ENTER THE ELEMENT TO BE DELETED:";
    cin>>n;
    del_element(h,n);
    cout<<"LEVEL ORDER TRAVERSAL AFTER DELETION: ";
    level_order_traversal(h);

    cout<<"ENTER THE INDEX FROM WHERE TO DELETE:";
    cin>>n;
    del_at_index(h,n);
    cout<<"LEVEL ORDER TRAVERSAL AFTER DELETION: ";
    level_order_traversal(h);

    cout<<"ENTER THE NUMBER UNDER WHICH TO DISPLAY HEAP:";
    cin>>n;
    elements_less_than_k(h,0,n);
    cout<<endl;

    cout<<"ENTER THE NUMBER ABOVE WHICH TO DISPLAY HEAP:";
    cin>>n;
    elements_greater_than_k(h,0,n);
    cout<<endl;

    heap *h2=create_heap(6);
    int a[]={13,14,17,19,11,15};
    build_heap_from_array(h2,a,6);
    cout<<"LEVEL ORDER TRAVERSAL OF HEAP 2: ";
    level_order_traversal(h2);

    heap *h3=merge_2_heaps(h,h2);
    cout<<"LEVEL ORDER TRAVERSAL OF MERGED HEAP 3: ";
    level_order_traversal(h3);

    cout<<"ENTER THE 'K' VALUE FOR 'Kth' LARGEST IN HEAP 3:";
    cin>>n;
    cout<<n<<"th LARGEST :"<<kth_largest_element(h3,n);
    cout<<endl;
}