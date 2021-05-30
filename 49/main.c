#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX 100005

#define true 1
#define false 0
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
    return newNode;
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

int queue_isEmpty(Queue *q)
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
int stack_isEmpty(Stack *stack)
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
int readInt();
int table[MAX] = {false};
int ans[50 * MAX] = {0};
int len_ans = 0;
Queue *q[MAX];
int temp;
char buffer[10000];
int main()
{
    setvbuf(stdout, buffer, _IONBF, sizeof(buffer));
    N = readInt();
    Stack *stack = createStack();
    for (int i = 0; i < N + 1; i++)
    {
        q[i] = malloc(sizeof(Queue));
        q[i]->head = q[i]->tail = NULL;
    }
    for (int i = 1; i < N + 1; ++i)
    {
        len = readInt();
        for (int j = 1; j < len + 1; ++j)
        {
            temp = readInt();
            push_back(q[i], temp);
        }
    }

    int i = 1;
    while (i <= N)
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

                    // printf("%d %d\n", top(stack), q[top(stack)]->head->data);
                    //真的去pop
                    pop_front(q[q[top(stack)]->head->data]);
                    pop_front(q[top(stack)]);

                    if (!stack_isEmpty(stack))
                    {
                        table[top(stack)] = false;
                        pop(stack);
                        // flag = true;
                        break;
                    }
                }
                else if (table[q[top(stack)]->head->data] == true)
                {
                    printf("No\n");
                    return 0;
                }
                else
                {
                    table[q[top(stack)]->head->data] = true;
                    push(stack, q[top(stack)]->head->data);
                }
                if (queue_isEmpty(q[top(stack)]) == true)
                    break;
            }
        }
        if (queue_isEmpty(q[i]))
            i++;
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
    // int flag = 0;
    char c = getchar();
    while ((c < '0' || c > '9'))
    {
        // if (c == '-')
        //     flag = 1;
        c = getchar();
    }
    while (c > ('0' - 1) && c < ('9' + 1))
        num = num * 10 + (c - '0'), c = getchar();
    // if (flag == 0)
    return num;
    // else
    //     return num * (-1);
}