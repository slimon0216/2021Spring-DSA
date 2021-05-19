#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100005
#define PUSH 0
#define MERGE 1
int sc;
typedef struct Node
{
    int value, prod_id;
    struct Node *next;
    struct Node *prev;
} Node;
typedef struct LNode
{
    int value, dist;
    struct LNode *right, *left, *parent;
    Node *copy;
} LNode;

typedef struct List
{
    Node *head;
    Node *tail;
} List;

Node *list_node[MAX] = {NULL};
LNode *heap_node[MAX] = {NULL};

inline Node *createNode(int val);

inline void insert_list(List *list, int val, int line_index);

inline LNode *create_LNode(int val, Node *copy);

inline int distance(LNode *node);
inline LNode *merge_lheap(LNode *a, LNode *b);

inline LNode *insert_lheap(LNode *root, int val, Node *copy);
inline LNode *pop(LNode *root);

inline int ReadInt();

int operations[MAX * 2 + 2][3];
int target_line[MAX] = {0};
int status[MAX] = {0}; // -2 已經pop, -1 存在但pop不出來, 0 還沒進來, 1 代表可以pop
List *prod_lines[MAX] = {NULL};
LNode *heap[MAX] = {NULL};
int disjoint_set_merged[MAX] = {0};
int T, num_of_packages, num_of_operations, num_of_lines;

int compression[MAX] = {0};

int main()
{
    T = ReadInt();
    char str[5];
    int a, b, target;
    for (int t = 0; t < T; ++t)
    {
        num_of_packages = ReadInt();
        num_of_operations = ReadInt();
        num_of_lines = ReadInt();
        for (int i = 0; i < num_of_lines; ++i)
        {
            prod_lines[i] = malloc(sizeof(List));
            prod_lines[i]->head = prod_lines[i]->tail = NULL;
            disjoint_set_merged[i] = i;
        }
        for (int i = 0; i < num_of_operations; ++i)
        {
            sc = getchar();
            operations[i][1] = ReadInt();
            operations[i][2] = ReadInt();
            if (sc == 'p')
                operations[i][0] = PUSH;
            else
                operations[i][0] = MERGE;
        }

        for (int i = 0; i < num_of_packages; i++)
            target_line[i] = ReadInt();

        int tar_index = 0;
        int op_index = 0;
        int impossible = false;
        int target;
        while (true)
        {

            target = target_line[tar_index];
            if (status[target] == -1)
                impossible = true;
            if (impossible)
                break;

            while (status[target] == 1)
            {
                //pop
                status[target] = -2;
                int pid = list_node[target]->prod_id;
                int cnt = 0;
                while (disjoint_set_merged[pid] != pid)
                {
                    compression[cnt] = pid;
                    ++cnt;
                    pid = disjoint_set_merged[pid];
                }
                for (int i = 0; i < cnt; ++i)
                    disjoint_set_merged[compression[i]] = pid;

                if (prod_lines[pid]->head == prod_lines[pid]->tail) //只有一個node
                {
                    heap[pid] = NULL;
                    prod_lines[pid]->head = prod_lines[pid]->tail = NULL;
                }
                else
                { // product line 有兩個以上 node
                    Node *node = heap_node[target]->copy;
                    while (status[heap[pid]->value] == -2)
                        heap[pid] = pop(heap[pid]);
                    status[heap[pid]->value] = 1;
                    if (heap[pid]->value == target) //剛好在 root
                    {
                        status[heap[pid]->value] = -1;
                        heap[pid] = pop(heap[pid]);
                        status[heap[pid]->value] = 1;
                    }
                    else
                    {
                        //非 root
                    }
                    //去生產線刪掉
                    if (prod_lines[pid]->head == node) //剛好也是頭
                    {
                        prod_lines[pid]->head = prod_lines[pid]->head->next; //把頭刪掉
                        prod_lines[pid]->head->prev = NULL;
                        status[prod_lines[pid]->head->value] = 1;
                    }
                    else if (prod_lines[pid]->tail == node)
                    {
                        prod_lines[pid]->tail = prod_lines[pid]->tail->prev;
                        prod_lines[pid]->tail->next = NULL;
                        status[prod_lines[pid]->tail->value] = 1;
                    }
                    else
                    {
                        node->prev->next = node->next;
                        node->next->prev = node->prev;
                    }
                    // while (status[heap[line_index]->value] == -2)
                    //     heap[line_index] = pop(heap[line_index]);
                }
                ++tar_index;
                target = target_line[tar_index];
            }

            // int isPush = true;
            if (operations[op_index][0] == PUSH)
            {
                int height = operations[op_index][1];
                // 如果進來的包裹跟 target 一樣就直接 pop，也不用真的 push 進來
                if (height == target)
                {
                    // printf("push %d %d\n", operations[op_index][1], operations[op_index][2]);
                    status[height] = -2;
                    ++tar_index;
                    target = target_line[tar_index];
                }
                else
                {
                    // printf("push %d %d\n", operations[op_index][1], operations[op_index][2]);
                    //push 進去

                    int line_index = operations[op_index][2];
                    if (prod_lines[line_index]->tail != NULL)
                        status[prod_lines[line_index]->tail->value] = -1;

                    insert_list(prod_lines[line_index], height, line_index);
                    status[prod_lines[line_index]->head->value] = 1;

                    // 處理 heap
                    // if (heap[line_index] == NULL)
                    // {
                    //     heap[line_index] = create_LNode(height, prod_lines[line_index]->tail);
                    // }
                    // else

                    if (heap[line_index] != NULL)
                    {
                        while (status[heap[line_index]->value] == -2)
                            heap[line_index] = pop(heap[line_index]);
                        status[heap[line_index]->value] = -1;
                    }
                    heap[line_index] = insert_lheap(heap[line_index], height, prod_lines[line_index]->tail);
                    status[heap[line_index]->value] = 1;

                    status[height] = 1;
                    status[prod_lines[line_index]->head->value] = 1;
                }
            }

            else
            {
                // printf("merge %d %d\n", operations[op_index][1], operations[op_index][2]);

                int broken = operations[op_index][1];
                int destination = operations[op_index][2];

                disjoint_set_merged[broken] = destination;
                int pid = destination;
                int cnt = 0;
                while (disjoint_set_merged[pid] != pid)
                {
                    compression[cnt] = pid;
                    ++cnt;
                    pid = disjoint_set_merged[pid];
                }
                for (int i = 0; i < cnt; ++i)
                    disjoint_set_merged[compression[i]] = pid;

                if (prod_lines[destination]->head == NULL) //目的地是空的
                {
                    if (prod_lines[broken]->head != NULL)
                    {
                        prod_lines[destination]->head = prod_lines[broken]->head;
                        prod_lines[destination]->tail = prod_lines[broken]->tail;
                    }
                }
                else
                {
                    if (prod_lines[broken]->head != NULL) // 有 node 要移過去
                    {
                        status[prod_lines[destination]->tail->value] = -1;
                        status[prod_lines[broken]->head->value] = -1;

                        prod_lines[destination]->tail->next = prod_lines[broken]->head;
                        prod_lines[broken]->head->prev = prod_lines[destination]->tail;
                        prod_lines[destination]->tail = prod_lines[broken]->tail;

                        status[prod_lines[destination]->head->value] = 1;
                        status[prod_lines[destination]->tail->value] = 1;
                    }
                }

                prod_lines[broken]->head = prod_lines[broken]->tail = NULL;

                if (heap[destination] != NULL || heap[broken] != NULL)
                {
                    if (heap[destination] != NULL)
                    {
                        while (status[heap[destination]->value] == -2)
                            heap[destination] = pop(heap[destination]);
                        status[heap[destination]->value] = -1;
                    }
                    if (heap[destination] != NULL)
                    {
                        while (status[heap[destination]->value] == -2)
                            heap[destination] = pop(heap[destination]);
                    }
                    heap[destination] = merge_lheap(heap[broken], heap[destination]);
                    status[heap[destination]->value] = 1;
                    heap[broken] = NULL;
                    status[prod_lines[destination]->head->value] = 1;
                    status[prod_lines[destination]->tail->value] = 1;
                }
            }
            ++op_index;
            if (tar_index >= num_of_packages)
                break;
        }
        if (impossible == 0)
        {
            puts("possible");
        }
        else
            puts("impossible");

        if (num_of_packages > num_of_lines)
        {
            for (int i = 0; i < num_of_lines; i++)
            {
                heap[i] = NULL;
                disjoint_set_merged[i] = i;
                heap_node[i] = NULL;
                list_node[i] = NULL;
                status[i] = 0;
            }
            for (int i = num_of_lines; i < num_of_packages; ++i)
            {
                heap_node[i] = NULL;
                list_node[i] = NULL;
                status[i] = 0;
            }
        }
        else
        {
            for (int i = num_of_packages; i < num_of_lines; i++)
            {
                heap[i] = NULL;
                disjoint_set_merged[i] = i;
            }
            for (int i = 0; i < num_of_packages; ++i)
            {
                heap_node[i] = NULL;
                list_node[i] = NULL;
                status[i] = 0;
                heap[i] = NULL;
                disjoint_set_merged[i] = i;
            }
        }
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

Node *createNode(int val)
{
    Node *node = malloc(sizeof(Node));
    node->value = node->prod_id = val;
    node->next = node->prev = NULL;
    return node;
}

void insert_list(List *list, int val, int line_index)
{
    Node *node = createNode(val);
    node->prod_id = line_index;
    list_node[val] = node;
    if (list->head == NULL)
    {
        list->head = list->tail = node;
    }
    else
    {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
}

LNode *create_LNode(int val, Node *copy)
{
    LNode *node;
    node = (LNode *)malloc(sizeof(LNode));
    node->right = node->left = node->parent = NULL;
    node->copy = copy;
    node->dist = 0;
    node->value = val;
    return node;
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
    if (a->right != NULL)
        a->right->parent = a;
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

LNode *insert_lheap(LNode *root, int val, Node *copy)
{
    LNode *node = create_LNode(val, copy);
    heap_node[val] = node;
    root = merge_lheap(root, node);
    return root;
}

LNode *pop(LNode *root)
{
    LNode *temp = root;
    root = merge_lheap(root->right, root->left);
    return root;
}