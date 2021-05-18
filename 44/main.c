#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define NDEBUG
#include <assert.h>

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
// int which_list[MAX] = {0};

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
        assert(list->tail == NULL);
        list->head = list->tail = node;
    }
    else
    {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
    }
}

void print_list(List *l, int mode)
{
    if (mode == 1)
    {
        Node *node = l->head;
        while (node != NULL)
        {
            printf("%d ", node->value);
            node = node->next;
        }
        printf("\n");
    }
    else
    {
        Node *node = l->tail;
        while (node != NULL)
        {
            printf("%d ", node->value);
            node = node->prev;
        }
        printf("\n");
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
    // printf("deleted element is %d\n", root->value);
    LNode *temp = root;
    root = merge_lheap(root->right, root->left);
    free(temp);
    return root;
}

int ReadInt();

int operations[MAX * 2 + 2][3];
int target_line[MAX] = {0};
int status[MAX] = {0}; // -2 已經pop, -1 存在但pop不出來, 0 還沒進來, 1 代表可以pop
List *prod_lines[MAX] = {NULL};
LNode *heap[MAX] = {NULL};
int disjoint_set_merged[MAX] = {0};
// int disjoint_set_origin[MAX] = {0};

int main()
{
    int T, num_of_packages, num_of_operations, num_of_lines;
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
            sc = scanf("%s %d %d", &str, &a, &b);
            operations[i][1] = a;
            operations[i][2] = b;
            if (str[0] == 'p')
                operations[i][0] = PUSH;
            else
                operations[i][0] = MERGE;
        }
        // for (int i = 0; i < num_of_operations; ++i)
        //     printf("%d %d %d\n", operations[i][0], operations[i][1], operations[i][2]);
        for (int i = 0; i < num_of_packages; i++)
            target_line[i] = ReadInt();

        int tar_index = 0;
        int op_index = 0;
        int impossible = false;
        int flag_merge = false;
        while (true)
        {

            int target = target_line[tar_index];

            if (status[target] == -1)
                impossible = true;
            if (impossible)
                break;

            while (status[target] == 1)
            {
                //pop
                status[target] = -2;
                int pid = list_node[target]->prod_id;
                while (disjoint_set_merged[pid] != pid)
                    pid = disjoint_set_merged[pid];

                if (prod_lines[pid]->head == prod_lines[pid]->tail) //只有一個node
                {
                    assert(prod_lines[pid]->head->value == target);
                    assert(heap[pid]->value == target);
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
                        assert(heap[pid]->copy == node);
                        status[heap[pid]->value] = -1;
                        heap[pid] = pop(heap[pid]);
                        status[heap[pid]->value] = 1;
                    }
                    else
                    {
                        //非 root
                        assert((prod_lines[pid]->head->value == target) || (prod_lines[pid]->tail->value == target));

                        // 假裝我有刪掉

                        // int isleft = true;
                        // LNode *prnt = heap_node[target]->parent;
                        // if (prnt->right == heap_node[target])
                        // {
                        //     assert(prnt->left != heap_node[target]);
                        //     isleft == false;
                        // }
                        // LNode *root = pop(heap_node[target]);
                        // heap_node[target] = NULL;

                        // if (root != NULL)
                        // {
                        //     root->parent = prnt;
                        //     if (isleft)
                        //         prnt->left = root;
                        //     else
                        //         prnt->right = root;
                        // }
                        // if (distance(prnt->right) > distance(prnt->left))
                        // {
                        //     LNode *temp = prnt->right;
                        //     prnt->right = prnt->left;
                        //     prnt->left = temp;
                        // }
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

            else if (operations[op_index][0] == MERGE)
            {
                // printf("merge %d %d\n", operations[op_index][1], operations[op_index][2]);

                int broken = operations[op_index][1];
                int destination = operations[op_index][2];

                disjoint_set_merged[broken] = destination;

                if (prod_lines[destination]->head == NULL) //目的地是空的
                {
                    if (prod_lines[broken]->head != NULL)
                    {
                        assert(prod_lines[broken]->tail != NULL);
                        prod_lines[destination]->head = prod_lines[broken]->head;
                        prod_lines[destination]->tail = prod_lines[broken]->tail;
                    }
                }
                else
                {
                    assert(prod_lines[destination]->tail != NULL);
                    if (prod_lines[broken]->head != NULL) // 有 node 要移過去
                    {
                        assert(prod_lines[broken]->tail != NULL);

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
                    // if (heap[broken] != NULL)
                    //     status[heap[broken]->value] = -1;
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
            printf("possible\n");
        }
        else
            printf("impossible\n");

        // for (int i = 0; i < num_of_lines; i++)
        // {
        //     printf("line %d:", i);
        //     print_list(prod_lines[i], 1);
        // }
        for (int i = 0; i < num_of_lines; i++)
        {
            heap[i] = NULL;
            disjoint_set_merged[i] = i;
            target_line[i] = 0;
        }
        for (int i = 0; i < num_of_packages; ++i)
        {
            heap_node[i] = NULL;
            list_node[i] = NULL;
            status[i] = 0;
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