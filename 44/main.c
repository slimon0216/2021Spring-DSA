#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX 100000
#define PUSH 0
#define MERGE 1
int sc ;
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
    Node* copy;
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
        list->head = list->tail = node;
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
    printf("deleted element is %d\n", root->value);
    LNode *temp = root;
    root = merge_lheap(root->right, root->left);
    // free(temp);
    return root;
}

int ReadInt();

int operations[MAX * 2 + 2][3];
int target_line[MAX] = {0};
int status[MAX] = {0};  // -2 已經pop, -1 存在但pop不出來, 0 還沒進來, 1 代表頭尾 , 2代表最高, 3代表 1 and 2
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
            disjoint_set_merged[i] = i;
            // disjoint_set_origin[i] = i;
        }
        for (int i = 0; i < num_of_operations; ++i)
        {
            sc = scanf("%s %d %d", &str, &a, &b);
            // printf("%s\n", str);
            if (str[0] == 'p')
                operations[i][0] = PUSH;
            else
                operations[i][0] = MERGE;
            operations[i][1] = a;
            operations[i][2] = b;
        }
        for (int i = 0; i < num_of_packages; i++)
        {    
            target_line[i] = ReadInt();
            // which_list[i] = -2;
        }
        
        int tar_index = 0;
        for(int op_index = 0; op_index < num_of_operations; ++op_index)
        {
            if (operations[op_index][0] == PUSH)
            {
                int target = target_line[tar_index];
                int height = operations[op_index][1];
                // 如果進來的包裹跟 target 一樣就直接 pop，也不用真的 push 進來
                if (height == target)
                {   
                    status[height] = -2;
                    ++tar_index;
                    continue;
                }
                //包裹不一樣 就去檢查在不在裡面
                else if (status[target] == -1)
                {
                    printf("impossible\n");
                    break;
                }
                else if (status[target] == 1)  // 在頭尾 可以 pop
                {
                    // 找到 target 所在的生產線 pid
                    int pid = list_node[target]->prod_id;
                    while (disjoint_set_merged[pid] != pid)
                        pid = disjoint_set_merged[pid];

                    // 把 target 從生產線 pop掉
                    if (prod_lines[pid]->head == prod_lines[pid]->tail)
                        prod_lines[pid]->head = prod_lines[pid]->tail = NULL;
                    else if (prod_lines[pid]->head->value == target)
                    {    
                        prod_lines[pid]->head = prod_lines[pid]->head->next;
                        if (status[prod_lines[pid]->head->value] == 0)
                            status[prod_lines[pid]->head->value] = 1;
                        else if (status[prod_lines[pid]->head->value] == 2)
                            status[prod_lines[pid]->head->value] = 3;
                    }
                    else if (prod_lines[pid]->tail->value == target)
                    {    
                        prod_lines[pid]->tail = prod_lines[pid]->tail->next;
                        if (status[prod_lines[pid]->tail->value] == 0)
                            status[prod_lines[pid]->tail->value] = 1;
                        else if (status[prod_lines[pid]->tail->value] == 2)
                            status[prod_lines[pid]->tail->value] = 3;
                    }
                    status[target] = -2;
                    if (prod_lines[pid]->head != NULL)
                        status[prod_lines[pid]->head->value] = 1;

                    // 去 heap 裡面刪掉
                    LNode* prnt = heap_node[height]->parent;
                    heap_node[height] = pop(heap_node[height]);
                    if (distance(prnt->right) > distance(prnt->left))
                    {
                        LNode *temp = prnt->right;
                        prnt->right = prnt->left;
                        prnt->left = temp;
                    }
                }
                else if (status[target] == 2) //最高 可以 pop
                {
                    // 找到 target 所在的生產線 id
                    int pid = list_node[target]->prod_id;
                    while (disjoint_set_merged[pid] != pid)
                        pid = disjoint_set_merged[pid];

                    // 先去生產線 pop 掉
                    Node *to_delete = heap[pid]->copy;
                    Node *ptr = to_delete->prev;
                    assert(ptr != NULL);
                    to_delete->prev->next = to_delete->next;
                    // to_delete->next->prev = ptr;
                    
                    // heap[pid] = pop(heap[pid]);
                    // status[to_delete->value] = -2;
                    
                }
                else if (status[target] == 3)
                {
                    // 找到 target 所在的生產線 id
                    int pid = list_node[target]->prod_id;
                    while (disjoint_set_merged[pid] != pid)
                        pid = disjoint_set_merged[pid];
                }

                int line_index = operations[op_index][2];
                //push 進去
                if (prod_lines[line_index]->tail != NULL)
                    if (status[prod_lines[line_index]->tail->value] == 1)
                        status[prod_lines[line_index]->tail->value] = 0;
                    else if (status[prod_lines[line_index]->tail->value] == 3)
                        status[prod_lines[line_index]->tail->value] = 2;

                status[height] = 1;
                insert_list(prod_lines[line_index], height, line_index);
                // which_list[height] = line_index;

                // 處理 heap
                if (heap[line_index] != NULL)
                    if (status[heap[line_index]->value] == 2)   //heap 的root只該是 2 or 3
                        status[heap[line_index]->value] = 0;
                    else if (status[heap[line_index]->value] == 3)
                        status[heap[line_index]->value] = 1;

                if (heap[line_index] == NULL)
                {
                    heap[line_index] = create_LNode(height, prod_lines[line_index]->tail);
                }
                else
                    heap[line_index] = insert_lheap(heap[line_index], height, prod_lines[line_index]->tail);
                if (status[heap[line_index]->value] == 1)
                    status[heap[line_index]->value] = 3;
                else if (status[heap[line_index]->value] == 0)
                    status[heap[line_index]->value] = 2;
                
                // push 結束 可以再看看

            }
            else if (operations[op_index][0] == MERGE)
            {
                int broken = operations[op_index][1];
                int destination = operations[op_index][2];
                if (broken == 8)
                {
                    ;
                }
                
                disjoint_set_merged[broken] = destination;

                if (prod_lines[destination]->head == NULL)
                {
                    if (prod_lines[broken]->head != NULL)
                    {
                        prod_lines[destination]->head = prod_lines[broken]->head;
                        prod_lines[destination]->tail = prod_lines[broken]->tail;
                        // status[prod_lines[destination]->head->value] = 1;
                        // status[prod_lines[broken]->tail->value] = 1;
                    }
                }
                else
                {
                    if (prod_lines[broken]->head != NULL)
                    {
                        if (prod_lines[broken]->head != prod_lines[broken]->tail)
                            if (status[prod_lines[broken]->head->value] == 1)
                                status[prod_lines[broken]->head->value] = 0;
                            else if (status[prod_lines[broken]->head->value] == 3)
                                status[prod_lines[broken]->head->value] = 2;

                        if (prod_lines[destination]->head != prod_lines[destination]->tail)
                            if (status[prod_lines[destination]->tail->value] == 1)
                                status[prod_lines[destination]->tail->value] = 0;
                            else if (status[prod_lines[destination]->tail->value] == 3)
                                status[prod_lines[destination]->tail->value] = 2;
                        prod_lines[destination]->tail->next = prod_lines[broken]->head;
                        prod_lines[destination]->tail = prod_lines[broken]->tail;
                                    
                    }
                }
                prod_lines[broken]->head = prod_lines[broken]->tail = NULL;

                if (heap[destination] != NULL || heap[broken] != NULL)
                {
                    if (heap[destination] != NULL )
                        if (status[heap[destination]->value] == 2)
                            status[heap[destination]->value] = 0;
                        else if (status[heap[destination]->value] == 3)
                            status[heap[destination]->value] = 1;
                    if (heap[broken] != NULL )
                        if (status[heap[broken]->value] == 2)
                            status[heap[broken]->value] = 0;
                        else if (status[heap[broken]->value] == 3)
                            status[heap[broken]->value] = 1;
                    heap[destination] = merge_lheap(heap[broken], heap[destination]);
                    if (status[heap[destination]->value] == 0)
                        status[heap[destination]->value] = 2;
                    else if (status[heap[destination]->value] == 1)
                        status[heap[destination]->value] = 3;
                    heap[broken] = NULL;
                }


            }
            // ++op_index;

            // printf("%d ", target);
        }
        for (int i = 0; i < num_of_lines; i++)
        {
            printf("line %d:", i);
            print_list(prod_lines[i], 1);
        }
        for (int i = 0; i < num_of_lines; i++)
            heap[i] = NULL;
        for (int i = 0; i < num_of_packages; ++i)
        {
            heap_node[i] =NULL; 
            list_node[i] = NULL;
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