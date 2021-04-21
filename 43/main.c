#include <stdio.h>
#include <stdlib.h>

#define THREASHOLD 30000

inline int readInt();

typedef struct Node{
    int key;
    int left_index;
    int right_index;
 
} Node;

int N, cnt = 0;
Node **tree;


void inOrder(Node* node, int min, int max){

    int key = node->key;
    if (key > min && key  < max)
        ++cnt;


    if (node->left_index != -2)
    {
        if (key < max)
            inOrder(tree[node->left_index], min, key);
        else
            inOrder(tree[node->left_index], min, max);
    }
    if (node->right_index != -2)
    {
        if (key > min)
            inOrder(tree[node->right_index], key, max);
        else
            inOrder(tree[node->right_index], min, max);
    }
}
Node* tree_2[THREASHOLD];
void inOrder_2(Node* node, int min, int max){

    int key = node->key;
    if (key > min && key  < max)
        ++cnt;


    if (node->left_index != -2)
    {
        if (key < max)
            inOrder_2(tree_2[node->left_index], min, key);
        else
            inOrder_2(tree_2[node->left_index], min, max);
    }
    if (node->right_index != -2)
    {
        if (key > min)
            inOrder_2(tree_2[node->right_index], key, max);
        else
            inOrder_2(tree_2[node->right_index], min, max);
    }
}





int main()
{
    N = readInt();
    tree = malloc(sizeof(Node*)*N);
    Node *node;
    if (N > THREASHOLD)
    {
        for (int i = 0; i < N; ++i)
        {
            node = malloc(sizeof(Node));
            node->key = readInt();
            node->left_index = readInt() -1;
            node->right_index = readInt() -1;
            tree[i] = node;
        }

        inOrder(tree[0], -1, 2000000000);
        printf("%d\n", cnt);
    }
    else
    {
        for (int i = 0; i < N; ++i)
        {
            node = malloc(sizeof(Node));
            node->key = readInt();
            node->left_index = readInt() -1;
            node->right_index = readInt() -1;
            tree_2[i] = node;
        }

        inOrder_2(tree_2[0], -1, 2000000000);
        printf("%d\n", cnt);
    }

    return 0;
}


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