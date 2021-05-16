#include <stdio.h>
#include <stdlib.h>

#define MAX 100000
#define PUSH 0
#define MERGE 1

typedef struct Node
{
    int value;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct List
{
    Node *head;
    Node *tail;
} List;

Node *createNode(int val)
{
    Node *node = malloc(sizeof(Node));
    node->value = val;
    node->next = node->prev = NULL;
    return node;
}

void insert_list(List *list, int val)
{
    Node *node = createNode(val);
    if (list->head == NULL)
        list->head = list->tail = node;
    else
    {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
}

void print_list(List *l)
{
    Node *node = l->head;
    while (node != NULL)
    {
        printf("%d ", node->value);
        node = node->next;
    }
    printf("\n");
}

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
}

int distance(LNode *node)
{
    if (node == NULL)
        return -1;
    else
        return node->dist;
}
LNode *merge_lheap(LNode *a, LNode *b)
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
    a->right = merge_lheap(a->right, b);
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
    root = merge_lheap(root->right, root->left);
    // free(temp);
    return root;
}
LNode *insert_lheap(LNode *root, int val)
{
    LNode *node = create_LNode();
    node->value = val;
    root = merge_lheap(root, node);
    return root;
}

int ReadInt();

int operations[MAX * 2 + 2][3];
int target_line[MAX] = {0};
int status[MAX] = {0};
List *prod_lines[MAX] = {NULL};
LNode *heap[MAX] = {NULL};
// int freeHeap[MAX] = {0};
// int a[MAX][MAX];

int main()
{

    int T, num_of_packages, num_of_operations, num_of_lines;
    T = ReadInt();
    char str[5];
    int a, b, target;
    // scanf("%d\n%d %d %d", &T, &num_of_packages, &num_of_operations, &num_of_lines);
    // printf("%d %d %d %d", T, num_of_packages, num_of_operations, num_of_lines);
    for (int t = 0; t < T; ++t)
    {
        num_of_packages = ReadInt();
        num_of_operations = ReadInt();
        num_of_lines = ReadInt();
        for (int i = 0; i < num_of_lines; ++i)
        {
            prod_lines[i] = malloc(sizeof(List));
            prod_lines[i]->head = prod_lines[i]->tail = NULL;
            // heap[i] = malloc(sizeof(int) * num_of_packages);
        }
        for (int i = 0; i < num_of_operations; ++i)
        {
            scanf("%s %d %d", &str, &a, &b);
            // printf("%s\n", str);
            if (str[0] == 'p')
                operations[i][0] = PUSH;
            else
                operations[i][0] = MERGE;
            operations[i][1] = a;
            operations[i][2] = b;
        }
        for (int i = 0; i < num_of_packages; i++)
            target_line[i] = ReadInt();
        int op_index = 0;
        int tar_index = 0;
        // for (int i = 0; i < num_of_packages; i++)
        while (op_index < num_of_operations && tar_index < num_of_packages)
        {
            // target = ReadInt();
            target = target_line[tar_index];
            if (status[target] == 1)
            {
                continue;
            }
            if (operations[op_index][0] == PUSH)
            {
                int height = operations[op_index][1];
                int line_index = operations[op_index][2];
                insert_list(prod_lines[line_index], height);

                heap[line_index] = insert_lheap(heap[line_index], height);
            }
            else if (operations[op_index][0] == MERGE)
            {
                int broken = operations[op_index][1];
                int destination = operations[op_index][2];
                if (prod_lines[destination]->head == NULL)
                {
                    if (prod_lines[broken]->head != NULL)
                    {
                        prod_lines[destination]->head = prod_lines[broken]->head;
                        prod_lines[destination]->tail = prod_lines[broken]->tail;
                    }
                }
                else
                {
                    if (prod_lines[broken]->head != NULL)
                    {
                        prod_lines[destination]->tail->next = prod_lines[broken]->head;
                        prod_lines[destination]->tail = prod_lines[broken]->tail;
                    }
                }
                prod_lines[broken]->head = prod_lines[broken]->tail = NULL;
                if (heap[destination] != NULL && heap[broken] != NULL)
                    heap[destination] = merge_lheap(heap[broken], heap[destination]);
            }
            ++op_index;

            // printf("%d ", target);
        }
        for (int i = 0; i < num_of_lines; i++)
        {
            printf("line %d:", i);
            print_list(prod_lines[i]);
        }
        printf("\n");
    }
}

int ReadInt()
{
    int num = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c > ('0' - 1) && c < ('9' + 1))
        num = num * 10 + (c - '0'), c = getchar();
    return num;
}