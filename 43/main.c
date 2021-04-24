#include <stdio.h>
#include <stdlib.h>

inline int readInt();

typedef struct Node{
    int key;
    int left_index;
    int right_index;

} Node;

unsigned N, cnt = 0;
Node **tree;


void inOrder(int node_index, unsigned min, unsigned max){


    if (tree[node_index]->key > min && tree[node_index]->key  < max)
        cnt++;


    if (tree[node_index]->left_index != -2)
    {
        if (tree[node_index]->key < max)
            inOrder(tree[node_index]->left_index, min, tree[node_index]->key);
        else
            inOrder(tree[node_index]->left_index, min, max);
    }
    if (tree[node_index]->right_index != -2)
    {
        if (tree[node_index]->key > min)
            inOrder(tree[node_index]->right_index, tree[node_index]->key, max);
        else
            inOrder(tree[node_index]->right_index, min, max);
    }
}






int main()
{
    N = readInt();
    tree = malloc(sizeof(Node*)*N);
    Node *node;
    for (unsigned i = 0; i < N; ++i)
    {
        node = malloc(sizeof(Node));
        node->key = readInt();
        node->left_index = readInt() -1;
        node->right_index = readInt() -1;
        tree[i] = node;
    }

    inOrder(0, 0, 2000000000);



    printf("%d\n", cnt);


}


int readInt()
{
    int num = 0;
    char c = getchar();
    while ((c < '0' || c > '9'))
    {
        if (c == '-')
        {   
            c = getchar();
                return -1;
        }
        c = getchar();
    }
    while (c > ('0' - 1) && c < ('9' + 1))
        num = num * 10 + (c - '0'), c = getchar();
    return num;
}