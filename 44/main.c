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

int ReadInt();

int operations[MAX * 2 + 2][3];
int target_line[MAX] = {0};
int status[MAX] = {0};
List *prod_lines[MAX] = {NULL};
int *heap[MAX] = {NULL};
int freeHeap[MAX] = {0};
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
                if (heap[line_index] == NULL)
                {
                    heap[line_index] = malloc(sizeof(int) * num_of_packages);
                    freeHeap[line_index] = 1;
                }
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
            }
            ++op_index;

            // printf("%d ", target);
        }
        // for (int i = 0; i < num_of_lines; i++)
        // {
        //     printf("line %d:", i);
        //     print_list(prod_lines[i]);
        // }
        // printf("\n");
        for (int i = 0; i < num_of_lines; ++i)
            if (freeHeap[i] = 1)
            {
                free(heap[i]);
                freeHeap[i] = 0;
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