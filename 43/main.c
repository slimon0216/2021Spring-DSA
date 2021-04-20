#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100000

int readInt()
{
    int num = 0;
    int flag = 0;
    char c = getchar();
    while ((c < '0' || c > '9'))
    {
        if (c == '-')
            flag = 1;
        c = getchar();
    }
    while (c > ('0' - 1) && c < ('9' + 1))
        num = num * 10 + (c - '0'), c = getchar();
    if (flag == 0)
        return num;
    else
        return num * (-1);
}

typedef struct Node{
    int key;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

int N;
// int adj_list[MAX_LEN][3];
int **adj_list;

Node* buildTree(int index) {
    if (index == -2)
        return NULL;
        
    Node *node = malloc(sizeof(Node));

    node->key = adj_list[index][0];
    node->left = buildTree(adj_list[index][1]-1) ;
    if (node->left != NULL) node->left->parent = node;
    node->right = buildTree(adj_list[index][2]-1);
    if (node->right != NULL) node->right->parent = node;

    return node;
}

void inOrder(Node *node){
    if (node == NULL)
        return;
    inOrder(node->left);
    printf("%d ", node->key);
    inOrder(node->right);
}

int cnt = 0;
int search(Node *node, int key){
    if (node == NULL)
        return 0;
    
    if (node->key == key)
        return 1;

    if (node->key > key)
        return search(node->left, key);
    else
        return search(node->right, key);
}


int main()
{

    N = readInt();
    adj_list = malloc(sizeof(int*)*N);
    for (int i = 0; i < N; ++i)
    {
        adj_list[i] = malloc(sizeof(int) * 3);
        for ( int j = 0; j < 3; ++j)
            adj_list[i][j] = readInt();
    }
    Node *root = buildTree(0);
    // inOrder(root);
    for (int i = 0; i < N; ++i)
    {
        if (search(root, adj_list[i][0]))
            cnt++;
    }
    printf("%d\n", cnt);

    // for (int i = 0; i < N; ++i)
    // {
    //     for ( int j = 0; j < 3; ++j)
    //     {
    //         printf("%d ", adj_list[i][j]);
    //     }
    //     printf("\n");
    // }


}