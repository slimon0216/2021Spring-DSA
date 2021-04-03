#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
int MAX_LEN = 100000;

#define isReverse 0
#define isNotReverse 1

typedef struct Node
{
    struct Node *prev, *next;
    int *array;
    int array_size;
    int tag;
} Node;

typedef struct DList
{
    Node *head;
    Node *tail;
    int list_size;
    int total_element;
} DList;

DList *createDList()
{
    DList *D = (DList *)malloc(sizeof(DList));
    D->head = D->tail = NULL;
    D->total_element = D->list_size = 0;
    return D;
}

void text(char *s)
{
    printf("%s\n", s);
}

Node *createNode()
{
    Node *node = malloc(sizeof(Node));
    node->next = node->prev = NULL;
    node->array_size = 0;
    node->array = malloc(sizeof(int) * MAX_LEN);
    node->tag = isNotReverse;
    return node;
}

// void insert(int val){

// }

void changeTag(Node *node)
{
    if (node->array_size <= 1)
        node->tag = isNotReverse;
    else
        node->tag = (node->tag == isReverse) ? isNotReverse : isReverse;
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

void print(DList *list, int sep)
{

    Node *curNode = list->head;
    if (sep == 1)
    {
        printf("|| ");
        while (curNode != NULL)
        {
            if (curNode->tag == isNotReverse)
                for (int i = 0; i < curNode->array_size; ++i)
                    printf("%d ", curNode->array[i]);
            else
                for (int i = curNode->array_size - 1; i >= 0; --i)
                    printf("%d ", curNode->array[i]);
            printf(" || ");
            curNode = curNode->next;
        }
    }
    else
        while (curNode != NULL)
        {
            if (curNode->tag == isNotReverse)
                for (int i = 0; i < curNode->array_size; ++i)
                    printf("%d ", curNode->array[i]);
            else
                for (int i = curNode->array_size - 1; i >= 0; --i)
                    printf("%d ", curNode->array[i]);
            curNode = curNode->next;
        }
    printf("\n");
}

int n_len_int_seq, q_num_query, len, temp, i, x, l, r, k;
char cmd[10], c;
Node *curNode;

int main()
{

    n_len_int_seq = readInt();
    q_num_query = readInt();
    // MAX_LEN = (int)sqrt;
    int *array = malloc(sizeof(int) * MAX_LEN);
    for (i = 0; i < n_len_int_seq; ++i)
    {
        temp = readInt();
        array[i] = temp;
    }

    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
            continue;

        switch (c)
        {
        case 'I':

            break;
        case 'D':
            text("de");
            i = readInt();
            break;
        case 'R':
            l = readInt();
            r = readInt();

            for (; l < r; ++l, --r)
            {
                temp = array[l - 1];
                array[l - 1] = array[r - 1];
                array[r - 1] = temp;
            }
            break;
        case 'Q':
            text("query");
            l = readInt();
            r = readInt();
            k = readInt();
            break;
        }
    }
    // Node *curNode = list->head;
    // while (curNode != NULL)
    // {
    //     for (int i = 0; i < curNode->array_size; ++i)
    //         printf("%d ", curNode->array[i]);
    //     curNode = curNode->next;
    // }
    // return 0;
    for (int i = 0; i < n_len_int_seq; ++i)
        printf("%d ", array[i]);
}