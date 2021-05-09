#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "generator.h"
#define MAX_TRIANGLES 3000000
#define MAX_PQR (1048576 + 10)
#define true 1
#define false 0

typedef int bool;
typedef long long int ll;

typedef struct Triangle{
    int p;
    int q;
    int r;
} Triangle;

bool smaller_than(Triangle* a, Triangle* b)
{
    if (a->p < b->p)
        return true;
    else if (a->p == b->p)
    {
        if (a->r < b->r)
            return true;
        else if (a->r == b->r)
        {
            if (a->q < b->q)
                return true;
        }
    }
    return false;
}

Triangle *createTriangle(int p, int q, int r)
{
    Triangle *t = malloc(sizeof(Triangle));
    t->p = p;
    t->q = q;
    t->r = r;
    return t;
}
Triangle* L[MAX_TRIANGLES], *R[MAX_TRIANGLES];
void MERGE(Triangle **arr, int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2)
    {
        if (smaller_than(L[i], R[j]))
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(Triangle **arr, int left, int right)
{
    if (left < right)
    {

        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        MERGE(arr, left, mid, right);
    }
}

Triangle *triangle_list[MAX_TRIANGLES];


// // An AVL tree node
// typedef struct Node
// {
//     int key;
//     struct Node *left;
//     struct Node *right;
//     int height;
// } Node;

// // A utility function to get maximum of two integers
// int max(int a, int b);
 
// // A utility function to get the height of the tree
// int height(struct Node *N)
// {
//     if (N == NULL)
//         return 0;
//     return N->height;
// }
 
// // A utility function to get maximum of two integers
// int max(int a, int b)
// {
//     return (a > b)? a : b;
// }
 
// /* Helper function that allocates a new node with the given key and
//     NULL left and right pointers. */
// struct Node* newNode(int key)
// {
//     struct Node* node = (struct Node*)malloc(sizeof(struct Node));
//     node->key   = key;
//     node->left   = NULL;
//     node->right  = NULL;
//     node->height = 1;  // new node is initially added at leaf
//     return(node);
// }
 
// // A utility function to right rotate subtree rooted with y
// // See the diagram given above.
// struct Node *rightRotate(struct Node *y)
// {
//     struct Node *x = y->left;
//     struct Node *T2 = x->right;
 
//     // Perform rotation
//     x->right = y;
//     y->left = T2;
 
//     // Update heights
//     y->height = max(height(y->left), height(y->right))+1;
//     x->height = max(height(x->left), height(x->right))+1;
 
//     // Return new root
//     return x;
// }
 
// // A utility function to left rotate subtree rooted with x
// // See the diagram given above.
// struct Node *leftRotate(struct Node *x)
// {
//     struct Node *y = x->right;
//     struct Node *T2 = y->left;
 
//     // Perform rotation
//     y->left = x;
//     x->right = T2;
 
//     //  Update heights
//     x->height = max(height(x->left), height(x->right))+1;
//     y->height = max(height(y->left), height(y->right))+1;
 
//     // Return new root
//     return y;
// }
 
// // Get Balance factor of node N
// int getBalance(struct Node *N)
// {
//     if (N == NULL)
//         return 0;
//     return height(N->left) - height(N->right);
// }
 
// // Recursive function to insert a key in the subtree rooted
// // with node and returns the new root of the subtree.
// struct Node* insert(struct Node* node, int key)
// {
//     /* 1.  Perform the normal BST insertion */
//     if (node == NULL)
//         return(newNode(key));
 
//     if (key < node->key)
//         node->left  = insert(node->left, key);
//     else if (key > node->key)
//         node->right = insert(node->right, key);
//     else // Equal keys are not allowed in BST
//         return node;
 
//     /* 2. Update height of this ancestor node */
//     node->height = 1 + max(height(node->left),
//                            height(node->right));
 
//     /* 3. Get the balance factor of this ancestor
//           node to check whether this node became
//           unbalanced */
//     int balance = getBalance(node);
 
//     // If this node becomes unbalanced, then
//     // there are 4 cases
 
//     // Left Left Case
//     if (balance > 1 && key < node->left->key)
//         return rightRotate(node);
 
//     // Right Right Case
//     if (balance < -1 && key > node->right->key)
//         return leftRotate(node);
 
//     // Left Right Case
//     if (balance > 1 && key > node->left->key)
//     {
//         node->left =  leftRotate(node->left);
//         return rightRotate(node);
//     }
 
//     // Right Left Case
//     if (balance < -1 && key < node->right->key)
//     {
//         node->right = rightRotate(node->right);
//         return leftRotate(node);
//     }
 
//     /* return the (unchanged) node pointer */
//     return node;
// }
 
// // A utility function to print preorder traversal
// // of the tree.
// // The function also prints height of every node
// void preOrder(struct Node *root)
// {
//     if(root != NULL)
//     {
//         printf("%d ", root->key);
//         preOrder(root->left);
//         preOrder(root->right);
//     }
// }
// void inOrder(struct Node *root)
// {
//     if(root != NULL)
//     {
//         inOrder(root->left);
//         printf("%d ", root->key);
//         inOrder(root->right);
//     }
// }

int BIT[MAX_PQR]={0}, counts_R[MAX_PQR]={0};
void update(int x, int delta)
{
      for(; x <= MAX_PQR; x += x&-x)
        BIT[x] += delta;
}

int query(int x)
{
     int sum = 0;
     for(; x > 0; x -= x&-x)
        sum += BIT[x];
     return sum;
}



int main() 
{
    // printf("%d\n", MAX_PQR);
    generator.init();
    int t = generator.getT();
    // printf("%d \n", t);
    while (t--) 
    {
        int n, *p, *q, *r, ans = 0;
        generator.getData(&n, &p, &q, &r);
        for(int i = 0; i < n; i++)
        {
            if (q[i] > r[i])
                triangle_list[i] = createTriangle(p[i]+MAX_PQR, r[i]+MAX_PQR, q[i]+MAX_PQR);
            else
                triangle_list[i] = createTriangle(p[i]+MAX_PQR, q[i]+MAX_PQR, r[i]+MAX_PQR);
        }
        mergeSort(triangle_list, 0, n-1);
        // for (int i = 0; i < n; i++)
        // {
        //     printf("%d %d %d\n", triangle_list[i]->p, triangle_list[i]->q, triangle_list[i]->r);
        // }
        int num_of_r_in_bit = 0;
        for (int i = 0; i < n; ++i)
        {  
            // 去看左頂點 q 跨過多少 r

            // printf("q: %d\n", (triangle_list[i]->q)-MAX_PQR);
            ans += num_of_r_in_bit - query(triangle_list[i]->q ) ;
            // printf("ans: %d\n", ans);
            counts_R[triangle_list[i]->r]++;
            update(triangle_list[i]->r, counts_R[triangle_list[i]->r]);
            ++num_of_r_in_bit;
            // for (ll j = 1048579; j <= 1048599;++j)
            // {
            //     printf("%d ", counts_R[j]);
            // }
            // printf("\n");
        }
        printf("%d\n", ans);
        for (int i = 0; i < MAX_PQR; i++)
        {
            BIT[i] = 0;
            counts_R[i] = 0;
        }
    }
    
    return 0;
}
