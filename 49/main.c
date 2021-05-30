#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 100005

typedef struct Node
{
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

Node *createNode(int data)
{
    Node *newNode = malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = newNode->prev = NULL;
}

typedef struct Queue
{
    Node *head;
    Node *tail;
} Queue;

void push_back(Queue *q, int data)
{
    Node *newNode = createNode(data);
    if (q->head == NULL)
        q->head = q->tail = newNode;
    else
    {
        q->tail->next = newNode;
        newNode->prev = q->tail;
        q->tail = newNode;
    }
}

void pop_front(Queue *q)
{
    if (q->head != NULL)
        q->head = q->head->next;
}

bool queue_isEmpty(Queue *q)
{
    if (q->head == NULL)
        return true;
    return false;
}

typedef struct Stack
{
    int array[2 * MAX];
    int size;
} Stack;

Stack *createStack()
{
    Stack *stack = malloc(sizeof(Stack));
    stack->size = -1;
    return stack;
}

void push(Stack *stack, int value)
{
    stack->size++;
    stack->array[stack->size] = value;
}
void pop(Stack *stack)
{
    --stack->size;
}
bool stack_isEmpty(Stack *stack)
{
    return stack->size == -1;
}

int top(Stack *stack)
{
    return stack->array[stack->size];
}
int *adj_list[MAX];
int N;
int len;
inline int readInt();

int temp_table[MAX] = {0};
bool table[MAX] = {0};
int ans[MAX] = {0};
int len_ans = 0;
int main()
{
    N = readInt();
    Stack *stack = createStack();
    Queue **q = malloc(MAX * sizeof(Queue *));
    for (int i = 1; i < N + 1; i++)
    {
        q[i] = malloc(sizeof(Queue *));
        q[i]->head = q[i]->tail = NULL;
    }
    bool stop = false;
    for (int i = 1; i < N + 1; ++i)
    {
        len = readInt();
        for (int j = 1; j < len + 1; ++j)
            push_back(q[i], readInt());
        temp_table[q[i]->head->data]++;
    }
    // printf("sdf");
    for (int i = 1; i < N + 1; ++i)
    {
        if (queue_isEmpty(q[i]) == false)
        {
            push(stack, i);
            table[i] = true;
        }
        while (stack_isEmpty(stack) == false)
        {
            while (queue_isEmpty(q[top(stack)]) == false)
            {
                if (q[q[top(stack)]->head->data]->head->data == top(stack))
                {
                    ans[len_ans++] = top(stack);
                    ans[len_ans++] = q[top(stack)]->head->data;

                    //真的去pop
                    pop_front(q[q[top(stack)]->head->data]);
                    pop_front(q[top(stack)]);
                }
                else if (table[q[top(stack)]->head->data] == true)
                {
                    printf("No");
                    return 0;
                }
                else
                {
                    push(stack, q[top(stack)]->head->data);
                }
            }
            table[top(stack)] = false;
            pop(stack);
        }
    }
    printf("Yes\n");
    for (int i = 0; i < len_ans; i = i + 2)
    {
        printf("%d %d\n", ans[i], ans[i + 1]);
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