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
 
    // int visited;
} Node;

int N, cnt = 0;
// int adj_list[MAX_LEN][3];
int **adj_list;

Node* buildTree(int index) {
    if (index == -2)
        return NULL;

    Node *node = malloc(sizeof(Node));
    // node->visited = 0;
    node->key = adj_list[index][0];
    node->left = buildTree(adj_list[index][1]-1) ;
    node->right = buildTree(adj_list[index][2]-1);

    return node;
}

void inOrder(Node *node, int min, int max){
    if (node == NULL)
        return;

    // if (node->visited == 0 )
        if (node->key > min && node->key < max)
           {
            //    printf("here is %d, min: %d, max: %d\n", node->key, min, max);
                cnt++;
            }
    // node->visited = 1;
    if (node->key < max)
        inOrder(node->left, min, node->key);
    else
        inOrder(node->left, min, max);
    // printf("%d \n", node->key);
    if (node->key > min)
        inOrder(node->right, node->key, max);
    else
        inOrder(node->right, min, max);
}



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
    // root->visited = 0;
    inOrder(root, -1, 2000000000);



    printf("%d\n", cnt);

    // for (int i = 0; i < N; ++i)
    // {
    //     for ( int j = 0; j < 3; ++j)
    //     {
    //         printf("%d ", adj_list[i][j]);
    //     }
        // printf("%d\n", 1000000000);
    // }


}