#include <stdio.h>
#include <stdlib.h>
typedef struct LNode
{
    int value, dist;
    struct LNode *right, *left, *parent;
} LNode;

LNode *create_LNode()
{
    LNode *node;
    node = (LNode *)malloc(sizeof(LNode));
    node->right = node->left = node->parent = NULL;
    node->dist = node->value = 0;
    return node;
}

int distance(LNode *node)
{
    if (node == NULL)
        return -1;
    else
        return node->dist;
}
LNode *merge(LNode *a, LNode *b)
{
    if (a == NULL)
        return b;
    if (b == NULL)
        return a;
    if (b->value > a->value)
    {
        LNode *temp = b;
        b = a;
        a = temp;
    }
    a->right = merge(a->right, b);
    if (distance(a->right) > distance(a->left))
    {
        LNode *temp = a->right;
        a->right = a->left;
        a->left = temp;
    }
    if (a->right == NULL)
        a->dist = 0;
    else
        a->dist = 1 + (a->right->dist);
    return a;
}
LNode *pop(LNode *root)
{
    printf("deleted element is %d\n", root->value);
    LNode *temp = root;
    root = merge(root->right, root->left);
    free(temp);
    return root;
}
LNode *insert_lheap(LNode *root, int val)
{
    LNode *node = create_LNode();
    node->value = val;
    root = merge(root, node);
    return root;
}

// LNode top()
LNode * lheap[5] = {NULL};
int main()
{
    lheap[1] = NULL;
    lheap[1] = insert_lheap(lheap[1], 12);
    lheap[1] = insert_lheap(lheap[1], 190);
    lheap[1] = insert_lheap(lheap[1], 7);
    lheap[1] = insert_lheap(lheap[1], 8);
    lheap[1] = insert_lheap(lheap[1], 2);
    // printf("%d\n", lheap[1]->value);
    // lheap[1] = pop(lheap[1]);
    // printf("%d\n", lheap[1]->value);
    // lheap[1] = pop(lheap[1]);
    // printf("%d\n", lheap[1]->value);
    // lheap[1] = pop(lheap[1]);
    // printf("%d\n", lheap[1]->value);
    // lheap[1] = pop(lheap[1]);
    // printf("%d\n", lheap[1]->value);

    lheap[2] = NULL;
    lheap[2] = insert_lheap(lheap[2], 33);
    lheap[2] = insert_lheap(lheap[2], 13);
    lheap[2] = insert_lheap(lheap[2], 27);
    lheap[2] = insert_lheap(lheap[2], 1);
    // printf("%d\n", lheap[2]->value);
    // lheap[2] = pop(lheap[2]);

    lheap[3] = merge(lheap[1], lheap[2]);
    printf("%d\n", lheap[3]->value);
    lheap[3] = pop(lheap[3]);
    printf("%d\n", lheap[3]->value);
    lheap[3] = pop(lheap[3]);
    printf("%d\n", lheap[3]->value);
    lheap[3] = pop(lheap[3]);
    printf("%d\n", lheap[3]->value);
    lheap[3] = pop(lheap[3]);
    printf("%d\n", lheap[3]->value);
    lheap[3] = pop(lheap[3]);
    printf("%d\n", lheap[3]->value);
    lheap[3] = pop(lheap[3]);
    printf("%d\n", lheap[3]->value);
    lheap[3] = pop(lheap[3]);
    printf("%d\n", lheap[3]->value);
    lheap[3] = pop(lheap[3]);
}

// void print(LNode *p)
// {
//     if (p != NULL)
//     {
//         print(p->left);
//         printf("\t%d", p->value);
//         print(p->right);
//     }
// }
// void meld()
// {
//     int val;
//     printf("\n1st tree:");
//     root3 = (LNode *)malloc(sizeof(LNode));
//     root3->right = NULL;
//     root3->left = NULL;
//     root3->dist = 0;
//     printf("\nenter 1st value");
//     scanf("%d", &val);
//     root3->value = val;
//     while (1)
//     {
//         printf("\ndo u waana insert_lheap element to 1st tree(0/1)");
//         scanf("%d", &val);
//         if (val)
//         {
//             root3 = insert_lheap(root3);
//         }
//         else
//             break;
//     }

//     printf("\n2nd tree:");
//     root4 = (LNode *)malloc(sizeof(LNode));
//     root4->right = NULL;
//     root4->left = NULL;
//     root4->dist = 0;
//     printf("\nenter 1st value");
//     scanf("%d", &val);
//     root4->value = val;
//     while (1)
//     {
//         printf("\ndo u waana insert_lheap element to 1st tree(0/1)");
//         scanf("%d", &val);
//         if (val)
//         {
//             root4 = insert_lheap(root4);
//         }
//         else
//             break;
//     }
//     printf("\n 1st tree");
//     print(root3);
//     printf("\n 2nd tree");
//     print(root4);
//     root3 = merge(root3, root4);
//     printf("\nroot element is: %d\n", root3->value);
//     print(root3);
// }